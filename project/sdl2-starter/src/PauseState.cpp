#include "PauseState.h"

const string PauseState::s_pauseID = "PAUSE";

void PauseState::s_pauseToMain() 
{
    theGame::Instance()->getStateMachine()->changeState(new MenuState());
}

void PauseState::s_resumePlay() 
{
    theGame::Instance()->getStateMachine()->popState();
}

void PauseState::update() 
{
    for(int i = 0; i < m_gameObjects.size();i++) 
    {
        m_gameObjects[i]->update();
    }
}

void PauseState::render() 
{
    for(int i = 0; i < m_gameObjects.size();i++) 
    {
        m_gameObjects[i]->draw();
    }
}

bool PauseState::onEnter() 
{
    if(!_TextureManager::Instance()->load("assets/resume.png", "resumebutton", theGame::Instance()->getRenderer())) 
    { 
        return false; 
    }

    if(!_TextureManager::Instance()->load("assets/main.png", "mainbutton", theGame::Instance()->getRenderer())) 
    { 
        return false; 
    }
    GameObject* button1 = MenuButton::load(new LoaderParams(200, 100, 200, 80, 3, 0, 0 "mainbutton"), s_pauseToMain); 
    GameObject* button2 = new MenuButton::load(new LoaderParams(200, 300, 200, 80, 3, 0, 0, "resumebutton"), s_resumePlay);
    m_gameObjects.push_back(button1); 
    m_gameObjects.push_back(button2);
    cout << "entering PauseState" << endl; 
    return true;
}


bool PauseState::onExit() 
{
    for(int i = 0; i < m_gameObjects.size();i++) 
    {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();
    _TextureManager::Instance()->clearFromTextureMap("mainbutton");
    _TextureManager::Instance()->clearFromTextureMap("resumebutton");
    cout << "exiting PauseState" << endl;
    return true;
}