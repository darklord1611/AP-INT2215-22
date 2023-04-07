#include "PlayState.h"

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
}


bool PlayState::onEnter() 
{
    StateParser stateParser; 
    stateParser.parseState("src/test.xml", s_playID, &m_gameObjects, &m_textureIDList);
    _TextureManager::Instance()->load("assets/bullet1.png", "bullet1", theGame::Instance()->getRenderer());
    _TextureManager::Instance()->load("assets/bullet2.png", "bullet2", theGame::Instance()->getRenderer());
    _TextureManager::Instance()->load("assets/bullet3.png", "bullet3", theGame::Instance()->getRenderer());
    _TextureManager::Instance()->load("assets/lives.png", "lives", theGame::Instance()->getRenderer());
    _TextureManager::Instance()->load("assets/smallexplosion.png", "smallexplosion", theGame::Instance()->getRenderer());
    _TextureManager::Instance()->load("assets/largeexplosion.png", "largeexplosion", theGame::Instance()->getRenderer());
    _TextureManager::Instance()->load("assets/explosion.png", "explosion", theGame::Instance()->getRenderer());
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


