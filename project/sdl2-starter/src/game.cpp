#include "Game.h"
#include "TextureManager.h"

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
            SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
        }
    }
    m_go = new GameObject();
    m_player = new Player();
    m_enemy = new Enemy();

    m_go->load(100, 100, 40, 40, "queen", "assets/Chess_qdd40.png");
    m_player->load(300, 300, 40, 40, "queen_player", "assets/Chess_qdd40.png");
    m_enemy->load(0, 0, 40, 40, "queen_enemy", "assets/Chess_qdd40.png");

    m_gameObjects.push_back(m_go);
    m_gameObjects.push_back(m_player);
    m_gameObjects.push_back(m_enemy);

    isRunning = true;
    return true;
}



void Game::render() 
{
    SDL_RenderClear(g_renderer);
    for(vector<GameObject*>::size_type i = 0; i < m_gameObjects.size();i++) 
    {
        m_gameObjects[i]->draw(g_renderer);
    }
    SDL_RenderPresent(g_renderer);
}

void Game::update() 
{
    for(vector<GameObject*>::size_type i = 0; i < m_gameObjects.size();i++) 
    {
        m_gameObjects[i]->update();
    }
}

void Game::clean()
{
    cout << "cleaning game\n";
    SDL_DestroyWindow(g_window);
    SDL_DestroyRenderer(g_renderer);
    SDL_Quit();
}

void Game::handleEvents() 
{
    SDL_Event event;
    if(SDL_PollEvent(&event)) 
    {
        switch(event.type) 
        {
            case SDL_QUIT:
                isRunning = false;
                break;
            default:
                break;
        }
    }
}