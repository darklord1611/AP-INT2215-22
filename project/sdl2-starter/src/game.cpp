#include "Game.h"

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
    m_go.load(100, 100, 128, 82, "queen");
    m_player.load(300, 300, 128, 82, "queen");
    isRunning = true;
    return true;
}



void Game::render() 
{
    SDL_RenderClear(g_renderer);

    m_go.draw(g_renderer); 
    m_player.draw(g_renderer);

    SDL_RenderPresent(g_renderer);
}

void Game::update() 
{
    m_go.update(); 
    m_player.update();
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