#include "PauseState.h"

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
    stateParser.parseState("src/test.xml", s_pauseID, &m_gameObjects, &m_textureIDList);
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
    for(int i = 0; i < m_textureIDList.size();i++) 
    {
        _TextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
    }
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