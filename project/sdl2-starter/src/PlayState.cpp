#include "PlayState.h"

const string PlayState::s_playID = "PLAY";

void PlayState::update() 
{
    if(_InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)) 
    {
        theGame::Instance()->getStateMachine()->pushState(new PauseState()); 
    }
    for(int i = 0; i < m_gameObjects.size();i++) 
    {
        m_gameObjects[i]->update();
    }
    if(checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[0]), dynamic_cast<SDLGameObject*>(m_gameObjects[1]))) 
    {
        cout << "collision detected " << endl;
        theGame::Instance()->getStateMachine()->pushState(new GameOverState()); 
    }
}

void PlayState::render() 
{
    for(int i = 0; i < m_gameObjects.size();i++) 
    {
        m_gameObjects[i]->draw();
    }
}


bool PlayState::onEnter() 
{
    StateParser stateParser;
    stateParser.parseState("test.xml", s_playID, &m_gameObjects, &m_textureIDList);
    cout << "entering PlayState" << endl;
    return true;
}

bool PlayState::onExit() 
{
    for(int i = 0; i < m_textureIDList.size();i++) 
    {
        _TextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
    }
    cout << "exiting PlayState" << endl;
    return true;
}


bool PlayState::checkCollision(SDLGameObject* p1, SDLGameObject* p2) 
{
    int topA, bottomA, leftA, rightA;
    int topB, bottomB, leftB, rightB;

    leftA = p1->getPosition().getX();
    rightA = p1->getPosition().getX() + p1->getWidth();
    topA = p1->getPosition().getY();
    bottomA = p1->getPosition().getY() + p1->getHeight();
    
    leftB = p2->getPosition().getX();
    rightB = p2->getPosition().getX() + p2->getWidth();
    topB = p2->getPosition().getY();
    bottomB = p2->getPosition().getY() + p2->getHeight();

    if(leftA >= rightB || rightA <= leftB || topA >= bottomB || bottomA <= topB) 
    {
        return false;
    }
    return true;
}