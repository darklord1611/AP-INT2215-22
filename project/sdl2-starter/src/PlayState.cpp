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
    for(int i = 0; i < m_gameObjects.size();i++) 
    {
        m_gameObjects[i]->draw();
    }
}


bool PlayState::onEnter() 
{
    if(!_TextureManager::Instance()->load("assets/helicopter.png", "helicopter", theGame::Instance()->getRenderer())) 
    {
        return false;
    }
    GameObject* player = new Player(new LoaderParams(100, 100, 128, 55, "helicopter"));
    m_gameObjects.push_back(player);
    cout << "entering PlayState" << endl;
    return true;
}

bool PlayState::onExit() 
{
    for(int i = 0; i < m_gameObjects.size();i++) 
    {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();
    _TextureManager::Instance()->clearFromTextureMap("helicopter");
    cout << "exiting PlayState" << endl;
    return true;
}