#include "MenuState.h"


const string MenuState::s_menuID = "MENU";

void MenuState::update() 
{
    for(int i = 0; i < m_gameObjects.size();i++) 
    {
        m_gameObjects[i]->update();
    }
}

void MenuState::render() 
{
    for(int i = 0; i < m_gameObjects.size();i++) 
    {
        m_gameObjects[i]->draw();
    }
}

bool MenuState::onEnter() 
{
    if(!_TextureManager::Instance()->load("assets/button.png", "playbutton", theGame::Instance()->getRenderer())) 
    {
        cout << SDL_GetError() << endl;
        return false;
    }
    if(!_TextureManager::Instance()->load("assets/exit.png", "exitbutton", theGame::Instance()->getRenderer())) 
    {
        cout << SDL_GetError() << endl;
        return false; 
    }
    GameObject* button1 = new MenuButton(new LoaderParams(100, 100, 400, 100, "playbutton"));
    GameObject* button2 = new MenuButton(new LoaderParams(100, 300, 400, 100, "exitbutton"));
    m_gameObjects.push_back(button1); 
    m_gameObjects.push_back(button2);
    cout << "entering menuState" << endl;
    return true;
}

bool MenuState::onExit() 
{
    cout << "exiting MenuState" << endl;
    return true;
}