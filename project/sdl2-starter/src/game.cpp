#include "Game.h"

Game* Game::instance = 0;

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags) 
{
    m_gameHeight = height;
    m_gameWidth = width;
    if (SDL_Init(SDL_INIT_EVERYTHING) > 0) 
    {
        cout << "SDL_Init failed with error: " << SDL_GetError() << endl;
        return false;
    }
    g_window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if(g_window != 0) 
    {
        g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_PRESENTVSYNC);
        if(g_renderer != 0) 
        {
            SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 0);
        }
    }
    if(_TextureManager::Instance()->load("assets/animate-alpha.png", "animate", g_renderer) == false) 
    {
        cout << SDL_GetError() << endl;
        return false;
    }
    _GameObjectFactory::Instance()->registerType("MenuButton", new MenuButtonCreator());
    _GameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
    _GameObjectFactory::Instance()->registerType("Enemy", new EnemyCreator());
    _GameObjectFactory::Instance()->registerType("AnimatedGraphic", new AnimatedGraphicCreator());
    g_gameStateMachine = new GameStateMachine();
	g_gameStateMachine->pushState(new MainMenuState());
    return true;
}



void Game::render() 
{
    SDL_RenderClear(g_renderer);
    for(vector<GameObject*>::size_type i = 0; i < m_gameObjects.size();i++) 
    {
        m_gameObjects[i]->draw();
    }
    g_gameStateMachine->render();

    SDL_RenderPresent(g_renderer);
}

void Game::update() 
{
    for(vector<GameObject*>::size_type i = 0; i < m_gameObjects.size();i++) 
    {
        m_gameObjects[i]->update();
    }
    g_gameStateMachine->update();
}

void Game::clean()
{
    cout << "cleaning game\n";
    _InputHandler::Instance()->clean();
    SDL_DestroyWindow(g_window);
    SDL_DestroyRenderer(g_renderer);
    SDL_Quit();
}

void Game::handleEvents() 
{
    _InputHandler::Instance()->update();
    if(_InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN)) 
    {
        theGame::Instance()->getStateMachine()->changeState(new PlayState());
    }  
}

void Game::quit() 
{
    isRunning = false;
}