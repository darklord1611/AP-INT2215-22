#include "MainMenuState.h"
#include "Game.h"
#include "StateParser.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "PlayState.h"
#include "MenuButton.h"

const string MainMenuState::s_menuID = "MENU";

void MainMenuState::update() 
{
    if(_InputHandler()::Instance()->isQuit()) theGame::Instance()->quit();
    for(int i = 0; i < m_gameObjects.size();i++) 
    {
        m_gameObjects[i]->update();
    }
}

void MainMenuState::render() 
{
    for(int i = 0; i < m_gameObjects.size();i++) 
    {
        m_gameObjects[i]->draw();
    }
}

bool MainMenuState::onEnter() 
{
    StateParser stateParser;
    stateParser.parseState("src/test.xml", s_menuID, &m_gameObjects, &m_textureIDList);
    m_callbacks.push_back(0);
    m_callbacks.push_back(s_menuToPlay);
    m_callbacks.push_back(s_exitFromMenu);
    // set the callbacks for menu items
    setCallbacks(m_callbacks);
    cout << "entering MenuState" << endl;
    return true;
}

bool MainMenuState::onExit() 
{
    for(int i = 0; i < m_gameObjects.size();i++) 
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
    cout << "exiting MenuState" << endl;
    return true;
}


void MainMenuState::s_menuToPlay() 
{ 
     theGame::Instance()->getStateMachine()->changeState(new PlayState()); // segmentation fault
}

void MainMenuState::s_exitFromMenu() 
{
    theGame::Instance()->quit();
}


void MainMenuState::setCallbacks(const vector<Callback> &callbacks) 
{
    for(int i = 0; i < m_gameObjects.size();i++) 
    {
        if(dynamic_cast<MenuButton*>(m_gameObjects[i]) != nullptr) 
        {
            // if they are of type MenuButton then assign a callback
		    // based on the id passed in from the file
            MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
            pButton->setCallback(callbacks[pButton->getCallbackID()]);
        }
    }
}