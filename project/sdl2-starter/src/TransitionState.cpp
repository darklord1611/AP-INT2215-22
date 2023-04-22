#include "TransitionState.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "InputHandler.h"
#include "TextureManager.h"
#include "StateParser.h"
#include "Game.h"
#include "MenuButton.h"

const string TransitionState::s_transitionID = "TRANSITION";

void TransitionState::s_gameOverToMain() 
{
    theGame::Instance()->getStateMachine()->changeState(new MainMenuState());
}

void TransitionState::s_nextLevel() 
{
    theGame::Instance()->getStateMachine()->changeState(new PlayState());
}


void TransitionState::update() 
{
    if(_InputHandler::Instance()->isQuit()) theGame::Instance()->quit();
    for(int i = 0; i < m_gameObjects.size();i++) 
    {
        m_gameObjects[i]->update();
    }
}

void TransitionState::render() 
{
    for(int i = 0; i < m_gameObjects.size();i++) 
    {
        m_gameObjects[i]->draw();
    }
}

bool TransitionState::onEnter() 
{
    StateParser stateParser;
    stateParser.parseState("assets/states.xml", s_transitionID, &m_gameObjects, &m_textureIDList);
    m_callbacks.push_back(0);
    m_callbacks.push_back(s_gameOverToMain);
    m_callbacks.push_back(s_nextLevel);
    // set the callbacks for menu items
    setCallbacks(m_callbacks);
    cout << "transition to next level" << endl;
    return true;
}

bool TransitionState::onExit() 
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
    cout << "leaving transition state" << endl;
    return true;
}

void TransitionState::setCallbacks(const vector<Callback> &callbacks) 
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