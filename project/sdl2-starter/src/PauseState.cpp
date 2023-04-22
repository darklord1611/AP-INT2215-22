#include "PauseState.h"
#include "Game.h"
#include "MainMenuState.h"
#include "StateParser.h"
#include "InputHandler.h"
#include "TextureManager.h"
#include "MenuButton.h"

const string PauseState::s_pauseID = "PAUSE";

void PauseState::s_pauseToMain() 
{
    theGame::Instance()->getStateMachine()->changeState(new MainMenuState());
}

void PauseState::s_resumePlay() 
{
    theGame::Instance()->getStateMachine()->popState();
}

void PauseState::update() 
{
    if(_InputHandler::Instance()->isQuit()) theGame::Instance()->quit();
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
    StateParser stateParser;
    stateParser.parseState("assets/states.xml", s_pauseID, &m_gameObjects, &m_textureIDList);
    m_callbacks.push_back(0);
    m_callbacks.push_back(s_pauseToMain);
    m_callbacks.push_back(s_resumePlay);
    // set the callbacks for menu items
    setCallbacks(m_callbacks);
    cout << "entering PauseState" << endl; 
    return true;
}


bool PauseState::onExit() 
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->clean();
        delete m_gameObjects[i];
    }
    m_gameObjects.clear();
    
    for(int i = 0; i < m_textureIDList.size();i++) 
    {
        _TextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
    }
    _InputHandler::Instance()->reset();
    cout << "exiting PauseState" << endl;
    return true;
}


void PauseState::setCallbacks(const vector<Callback> &callbacks) 
{
    for(int i = 0; i < m_gameObjects.size();i++) 
    {
        if(dynamic_cast<MenuButton*>(m_gameObjects[i]) != nullptr) 
        {
            MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
            pButton->setCallback(callbacks[pButton->getCallbackID()]);
        }
    }
}