#ifndef __Game__
#define __Game__
#include<SDL2/SDL.h>
#include<SDL2_image/SDL_image.h>
#include<iostream>
#include "Player.h"

using namespace std;

class Game
{
public:
    Game() {};
    ~ Game() {};
    bool init(const char* title, int xpos, int ypos, int width, int height, int flags); 
    void render();
    void update();
    void handleEvents();
    void clean();
    bool running() { return isRunning; }
private:
    SDL_Window* g_window;
    SDL_Renderer* g_renderer;
    bool isRunning;
    GameObject m_go; 
    Player m_player;
};

#endif /* defined(__Game__) */
