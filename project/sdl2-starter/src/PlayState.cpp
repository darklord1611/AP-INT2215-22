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
}

void PlayState::render() 
{
    // for(int i = 0; i < TheGame::Instance()->getPlayerLives(); i++)
    // {
    //     _TextureManager::Instance()->drawFrame("lives", i * 30, 0, 32, 30, 0, 0, TheGame::Instance()->getRenderer(), 0.0, 255);
    // }
    TheBulletHandler::Instance()->drawBullets();
}


bool PlayState::onEnter() 
{
    StateParser stateParser; 
    stateParser.parseState("src/test.xml", s_playID, &m_gameObjects, &m_textureIDList);
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
