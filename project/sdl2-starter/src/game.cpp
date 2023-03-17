#include "Game.h"

Game* Game::instance = 0;

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags) 
{
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
    g_gameStateMachine = new GameStateMachine();
    g_gameStateMachine->changeState(new MenuState());
    // m_gameObjects.push_back(new Player(new LoaderParams(50, 50, 128, 82,"animate")));
    // m_gameObjects.push_back(new Enemy(new LoaderParams(100, 100, 128, 82,"animate")));
    isRunning = true;
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
        g_gameStateMachine->changeState(new PlayState());
    }
}

void Game::quit() 
{
    isRunning = false;
}