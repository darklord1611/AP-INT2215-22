#include "GameOverState.h"

const string GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::s_gameOverToMain() 
{
    theGame::Instance()->getStateMachine()->changeState(new MainMenuState());
}

void GameOverState::s_restartPlay() 
{
    theGame::Instance()->getStateMachine()->changeState(new PlayState());
}


void GameOverState::update() 
{
    for(int i = 0; i < m_gameObjects.size();i++) 
    {
        m_gameObjects[i]->update();
    }
}

void GameOverState::render() 
{
    for(int i = 0; i < m_gameObjects.size();i++) 
    {
        m_gameObjects[i]->draw();
    }
}

bool GameOverState::onEnter() 
{
    StateParser stateParser;
    stateParser.parseState("src/test.xml", s_gameOverID, &m_gameObjects, &m_textureIDList);
    m_callbacks.push_back(0);
    m_callbacks.push_back(s_gameOverToMain);
    m_callbacks.push_back(s_restartPlay);
    // set the callbacks for menu items
    setCallbacks(m_callbacks);
    cout << "entering PauseState" << endl;
    return true;
}

bool GameOverState::onExit() 
{
    for(int i = 0; i < m_textureIDList.size();i++) 
    {
        _TextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
    }
    cout << "leaving GameOverState" << endl;
    return true;
}

void GameOverState::setCallbacks(const vector<Callback> &callbacks) 
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
