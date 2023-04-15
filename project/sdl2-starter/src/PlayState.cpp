#include "PlayState.h"
#include "BulletHandler.h"
#include "GameOverState.h"
#include "InputHandler.h"
#include "PauseState.h"
#include "TextureManager.h"
#include "Enemy.h"
#include "StateParser.h"

const static int s_buffer = 4;
const string PlayState::s_playID = "PLAY";


bool PlayState::RectRect(SDL_Rect* A, SDL_Rect* B)
{
    int aHBuf = A->h / s_buffer;
    int aWBuf = A->w / s_buffer;
    
    int bHBuf = B->h / s_buffer;
    int bWBuf = B->w / s_buffer;
    
    // if the bottom of A is less than the top of B - no collision
    if((A->y + A->h) - aHBuf <= B->y + bHBuf)  { return false; }
    
    // if the top of A is more than the bottom of B = no collision
    if(A->y + aHBuf >= (B->y + B->h) - bHBuf)  { return false; }
    
    // if the right of A is less than the left of B - no collision
    if((A->x + A->w) - aWBuf <= B->x +  bWBuf) { return false; }
    
    // if the left of A is more than the right of B - no collision
    if(A->x + aWBuf >= (B->x + B->w) - bWBuf)  { return false; }
    
    // otherwise there has been a collision
    return true;
}

void PlayState::update() 
{
    if(_InputHandler::Instance()->isQuit()) 
    {
        saveGame();
        theGame::Instance()->quit();
    }
    if(_InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)) 
    {
        theGame::Instance()->getStateMachine()->pushState(new PauseState()); 
    }
    if(theGame::Instance()->getPlayerLives() == 0)
    {
        theGame::Instance()->getStateMachine()->changeState(new GameOverState());
    }
    TheBulletHandler::Instance()->updateBullets();
    for(int i = 0; i < m_gameObjects.size();i++) 
    {
        if(m_gameObjects[i]->type() == "Player") 
        {
            Player* player = dynamic_cast<Player*>(m_gameObjects[i]);
            if(player->isSafe() == false)
            {
                if(checkPlayerEnemyBulletCollision(player)) 
                {
                    theGame::Instance()->setPlayerLives(theGame::Instance()->getPlayerLives() - 1);
                }
                if(checkPlayerEnemyCollision(player, m_gameObjects)) 
                {
                    theGame::Instance()->setPlayerLives(theGame::Instance()->getPlayerLives() - 1);
                }
            }
        }
        if(m_gameObjects[i]->type() == "Enemy") 
        {
            checkEnemyPlayerBulletCollision(m_gameObjects);
        }
        m_gameObjects[i]->update();
    }
    
}

void PlayState::render() 
{
    for(int i = 0; i < m_gameObjects.size();i++) 
    {
        m_gameObjects[i]->draw();
    }
    TheBulletHandler::Instance()->drawBullets();

    for(int i = 0; i < theGame::Instance()->getPlayerLives(); i++)
    {
        _TextureManager::Instance()->drawFrame("lives", i * 30, 0, 32, 30, 0, 0, theGame::Instance()->getRenderer());
    }

    _TextureManager::Instance()->draw("highscore",theGame::Instance()->getGameWidth() - 100, 0, 100, 25, theGame::Instance()->getRenderer());
    _TextureManager::Instance()->draw("current_score",theGame::Instance()->getGameWidth() - 100, 25, 100, 25, theGame::Instance()->getRenderer());
}


bool PlayState::onEnter() 
{
    StateParser stateParser;
    if(theGame::Instance()->resumeGame() == true) 
    {
        stateParser.parseState("assets/pause.xml", s_playID, &m_gameObjects, &m_textureIDList);
    } else 
    {
        stateParser.parseState("src/test.xml", s_playID, &m_gameObjects, &m_textureIDList);
    }
    _TextureManager::Instance()->load("assets/bullet1.png", "bullet1", theGame::Instance()->getRenderer());
    _TextureManager::Instance()->load("assets/bullet2.png", "bullet2", theGame::Instance()->getRenderer());
    _TextureManager::Instance()->load("assets/bullet3.png", "bullet3", theGame::Instance()->getRenderer());
    _TextureManager::Instance()->load("assets/lives.png", "lives", theGame::Instance()->getRenderer());
    _TextureManager::Instance()->load("assets/smallexplosion.png", "smallexplosion", theGame::Instance()->getRenderer());
    _TextureManager::Instance()->load("assets/largeexplosion.png", "largeexplosion", theGame::Instance()->getRenderer());
    _TextureManager::Instance()->load("assets/explosion.png", "explosion", theGame::Instance()->getRenderer());
    theGame::Instance()->loadHighScore();
    theGame::Instance()->setScore(0);
    theGame::Instance()->upgradeCurrentScore(0);
    theGame::Instance()->setPlayerLives(3);
    cout << "entering PlayState" << endl;
    return true;
}

bool PlayState::onExit() 
{
    for(int i = 0; i < m_textureIDList.size();i++) 
    {
        _TextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
    }
    for(int i = 0; i < m_gameObjects.size();i++) 
    {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();
    _InputHandler::Instance()->reset();
    theGame::Instance()->compareScore();
    TheBulletHandler::Instance()->clearBullets();
    cout << "exiting PlayState" << endl;
    return true;
}

bool PlayState::checkPlayerEnemyBulletCollision(Player* pPlayer)
{
    SDL_Rect* pRect1 = new SDL_Rect();
    pRect1->x = pPlayer->getPosition().getX();
    pRect1->y = pPlayer->getPosition().getY();
    pRect1->w = pPlayer->getWidth();
    pRect1->h = pPlayer->getHeight();
    
    for(int i = 0; i < TheBulletHandler::Instance()->getEnemyBullets().size(); i++)
    {
        EnemyBullet* pEnemyBullet = TheBulletHandler::Instance()->getEnemyBullets()[i];
        
        SDL_Rect* pRect2 = new SDL_Rect();
        pRect2->x = pEnemyBullet->getPosition().getX();
        pRect2->y = pEnemyBullet->getPosition().getY();
        
        pRect2->w = pEnemyBullet->getWidth();
        pRect2->h = pEnemyBullet->getHeight();
        
        if(RectRect(pRect1, pRect2))
        {
            if(!pPlayer->dying() && !pEnemyBullet->dying())
            {
                pEnemyBullet->collision();
                pPlayer->collision();
                return true;
            }
        }
        delete pRect2;
    }
    delete pRect1;
    return false;
}

void PlayState::checkEnemyPlayerBulletCollision(const vector<GameObject*> &objects)
{
    for(int i = 0; i < objects.size(); i++)
    {
        GameObject* pObject = objects[i];
        
        for(int j = 0; j < TheBulletHandler::Instance()->getPlayerBullets().size(); j++)
        {
            if(pObject->type() != string("Enemy") || !pObject->updating())
            {
                continue;
            }
            
            SDL_Rect* pRect1 = new SDL_Rect();
            pRect1->x = pObject->getPosition().getX();
            pRect1->y = pObject->getPosition().getY();
            pRect1->w = pObject->getWidth();
            pRect1->h = pObject->getHeight();
            
            PlayerBullet* pPlayerBullet = TheBulletHandler::Instance()->getPlayerBullets()[j];
            
            SDL_Rect* pRect2 = new SDL_Rect();
            pRect2->x = pPlayerBullet->getPosition().getX();
            pRect2->y = pPlayerBullet->getPosition().getY();
            pRect2->w = pPlayerBullet->getWidth();
            pRect2->h = pPlayerBullet->getHeight();
            
            if(RectRect(pRect1, pRect2))
            {
                if(!pObject->dying() && !pPlayerBullet->dying())
                {
                    pPlayerBullet->collision();
                    pObject->collision();
                    if(dynamic_cast<Enemy*>(pObject)->getHealth() == 0) 
                    {
                        theGame::Instance()->upgradeCurrentScore(dynamic_cast<Enemy*>(pObject)->getScore());
                    }
                }
            }
            delete pRect1;
            delete pRect2;
        }
    }
}

bool PlayState::checkPlayerEnemyCollision(Player* pPlayer, const vector<GameObject*> &objects)
{
    SDL_Rect* pRect1 = new SDL_Rect();
    pRect1->x = pPlayer->getPosition().getX();
    pRect1->y = pPlayer->getPosition().getY();
    pRect1->w = pPlayer->getWidth();
    pRect1->h = pPlayer->getHeight();
    for(int i = 0; i < objects.size(); i++)
    {
        if(objects[i]->type() != "Enemy" || !objects[i]->updating())
        {
            continue;
        }
        SDL_Rect* pRect2 = new SDL_Rect();
        pRect2->x = objects[i]->getPosition().getX();
        pRect2->y = objects[i]->getPosition().getY();
        pRect2->w = objects[i]->getWidth();
        pRect2->h = objects[i]->getHeight();
        
        if(RectRect(pRect1, pRect2))
        {
            if(!objects[i]->dead() && !objects[i]->dying())
            {
                pPlayer->collision();
                return true;
            }
        }
        delete pRect2;
    }
    delete pRect1;
    return false;
}


void PlayState::saveGame() 
{
    TiXmlDocument doc;
    TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "", "");
    doc.LinkEndChild(decl);
    

    // create root element
    TiXmlElement* root = new TiXmlElement("STATES");
    doc.LinkEndChild(root);

    // create play element
    TiXmlElement* play = new TiXmlElement("PLAY");
    root->LinkEndChild(play);

    // create texture element
    TiXmlElement* textures = new TiXmlElement("TEXTURES");
    play->LinkEndChild(textures);

    // save textures
    TiXmlElement* texture1 = new TiXmlElement("texture");
    texture1->SetAttribute("filename", "assets/clouds.png");
    texture1->SetAttribute("ID", "background");
    textures->LinkEndChild(texture1);


    TiXmlElement* texture2 = new TiXmlElement("texture");
    texture2->SetAttribute("filename", "assets/helicopter.png");
    texture2->SetAttribute("ID", "player");
    textures->LinkEndChild(texture2);

    TiXmlElement* texture3 = new TiXmlElement("texture");
    texture3->SetAttribute("filename", "assets/glider.png");
    texture3->SetAttribute("ID", "glider");
    textures->LinkEndChild(texture3);

    TiXmlElement* texture4 = new TiXmlElement("texture");
    texture4->SetAttribute("filename", "assets/shotglider.png");
    texture4->SetAttribute("ID", "shotglider");
    textures->LinkEndChild(texture4);

    TiXmlElement* texture5 = new TiXmlElement("texture");
    texture5->SetAttribute("filename", "assets/eskeletor.png");
    texture5->SetAttribute("ID", "eskeletor");
    textures->LinkEndChild(texture5);

    TiXmlElement* texture6 = new TiXmlElement("texture");
    texture6->SetAttribute("filename", "assets/turret.png");
    texture6->SetAttribute("ID", "turret");
    textures->LinkEndChild(texture6);

    // create object element
    TiXmlElement* object = new TiXmlElement("OBJECTS");
    play->LinkEndChild(object);

    // save background
    TiXmlElement* background = new TiXmlElement("object");
    background->SetAttribute("type", "Background");
    background->SetAttribute("x", "0");
    background->SetAttribute("y", "0");
    background->SetAttribute("width", "800");
    background->SetAttribute("height", "600");
    background->SetAttribute("textureID", "background");
    background->SetAttribute("numFrames", "1");
    background->SetAttribute("animSpeed", "0.5");
    object->LinkEndChild(background);

    // save player
    TiXmlElement* player = new TiXmlElement("object");
    player->SetAttribute("type", "Player");
    player->SetAttribute("x", m_gameObjects[1]->getPosition().getX());
    player->SetAttribute("y", m_gameObjects[1]->getPosition().getY());
    player->SetAttribute("width", m_gameObjects[1]->getWidth());
    player->SetAttribute("height", m_gameObjects[1]->getHeight());
    player->SetAttribute("textureID", m_gameObjects[1]->getTextureID());
    player->SetAttribute("numFrames", "4");
    object->LinkEndChild(player);

    // save enemy
    int size = m_gameObjects.size();
    TiXmlElement** objects = new TiXmlElement*[size];
    for(int i = 2; i < size; i++) 
    {
        objects[i] = new TiXmlElement("object");
        objects[i]->SetAttribute("type", getEnemyType(m_gameObjects[i]));
        objects[i]->SetAttribute("x", m_gameObjects[i]->getPosition().getX());
        objects[i]->SetAttribute("y", m_gameObjects[i]->getPosition().getY());
        objects[i]->SetAttribute("width", m_gameObjects[i]->getWidth());
        objects[i]->SetAttribute("height", m_gameObjects[i]->getHeight());
        objects[i]->SetAttribute("textureID", m_gameObjects[i]->getTextureID());
        objects[i]->SetAttribute("numFrames", 1);
        object->LinkEndChild(objects[i]);
    }
    // Save the file
    bool success = doc.SaveFile("assets/pause.xml");
    if(success) 
    {
        cout << "XML file saved successfully." << endl;
    }
    else 
    {
        cerr << "Failed to save XML file." << endl;
    }

    for(int i = 2; i < size; i++) 
    {
        delete objects[i];
    }
    delete[] objects;
    delete texture1;
    delete texture2;
    delete texture3;
    delete texture4;
    delete texture5;
    delete texture6;
    delete textures;
    delete background;
    delete player;
    delete play;
    delete root;
    delete decl;
}


string PlayState::getEnemyType(GameObject* object) 
{
    Enemy* enemy = dynamic_cast<Enemy*>(object);
    if(enemy->getScore() == 10) return "Glider";
    if(enemy->getScore() == 20) return "ShotGlider";
    if(enemy->getScore() == 30) return "Eskeletor";
    return "Turret";
}