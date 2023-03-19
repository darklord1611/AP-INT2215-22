#include "GameOverState.h"

const string GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::s_gameOverToMain() 
{
    theGame::Instance()->getStateMachine()->changeState(new MenuState());
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
    if(!_TextureManager::Instance()->load("assets/gameover.png", "gameover", theGame::Instance()->getRenderer())) 
    {
        return false;
    }
    if(!_TextureManager::Instance()->load("assets/main.png", "mainbutton", theGame::Instance()->getRenderer())) 
    {
        return false;
    }
    if(!_TextureManager::Instance()->load("assets/restart.png", "restartbutton", theGame::Instance()->getRenderer())) 
    {
        return false;
    }
    GameObject* gameOverText = new AnimatedGraphic(new LoaderParams(200, 100, 190, 30, 2, "gameover"), 2);
    GameObject* button1 = new MenuButton(new LoaderParams(200, 200, 200, 80, 3, "mainbutton"), s_gameOverToMain); 
    GameObject* button2 = new MenuButton(new LoaderParams(200, 300, 200, 80, 3, "restartbutton"), s_restartPlay);
    m_gameObjects.push_back(gameOverText);
    m_gameObjects.push_back(button1);
    m_gameObjects.push_back(button2);
    cout << "entering PauseState" << endl;
    return true;
}

bool GameOverState::onExit() 
{
    for(int i = 0; i < m_gameObjects.size();i++) 
    {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();
    _TextureManager::Instance()->clearFromTextureMap("gameover");
    _TextureManager::Instance()->clearFromTextureMap("mainbutton");
    _TextureManager::Instance()->clearFromTextureMap("restartbutton");
    return true;
}
