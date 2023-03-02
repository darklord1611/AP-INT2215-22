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
    SDL_Surface* g_temp_surface = IMG_Load("assets/queen.png");
    if(g_temp_surface == nullptr) 
    {
        cout << SDL_GetError() << endl;
        return false;
    }
    g_texture = SDL_CreateTextureFromSurface(g_renderer, g_temp_surface);
    if(g_texture == NULL) 
    {
        cout << SDL_GetError() << endl;
        return false;
    }
    SDL_FreeSurface(g_temp_surface);
    SDL_QueryTexture(g_texture, NULL, NULL, &m_sourceRectangle.w, &m_sourceRectangle.h);
    m_destinationRectangle.x = m_sourceRectangle.x = 0; 
    m_destinationRectangle.y = m_sourceRectangle.y = 0; 
    m_destinationRectangle.w = m_sourceRectangle.w; 
    m_destinationRectangle.h = m_sourceRectangle.h;
    isRunning = true;
    return true;
}



void Game::render() 
{
    SDL_RenderClear(g_renderer);
    SDL_RenderCopy(g_renderer, g_texture, &m_sourceRectangle, &m_destinationRectangle);
    SDL_RenderPresent(g_renderer);
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