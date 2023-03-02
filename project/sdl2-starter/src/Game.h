#ifndef __Game__
#define __Game__
#include<SDL2/SDL.h>
#include<SDL2_image/SDL_image.h>
#include<iostream>
using namespace std;
class Game
{
public:
    Game() {};
    ~ Game() {};
    bool init(const char* title, int xpos, int ypos, int width, int height, int flags); 
    void render();
    void update() {};
    void handleEvents();
    void clean();
    bool running() { return isRunning; }
private:
    SDL_Window* g_window;
    SDL_Renderer* g_renderer;
    SDL_Texture* g_texture; // the new SDL_Texture variable 
    SDL_Rect m_sourceRectangle; // the first rectangle 
    SDL_Rect m_destinationRectangle; // another rectangle
    bool isRunning;
};
#endif /* defined(__Game__) */
