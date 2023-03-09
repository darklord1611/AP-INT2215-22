#ifndef __Game__
#define __Game__
#include<SDL2/SDL.h>
#include<SDL2_image/SDL_image.h>
#include<iostream>
#include<vector>

#include "Player.h"
#include "Enemy.h"

using namespace std;

class Game
{
private:
    Game() {};
    static Game* instance;
    SDL_Window* g_window;
    SDL_Renderer* g_renderer;
    bool isRunning;
    vector<GameObject*> m_gameObjects;
public:
    static Game* Instance() 
        {
            if(instance == 0) 
            {
                instance = new Game();
            }
            return instance;
        }
    bool init(const char* title, int xpos, int ypos, int width, int height, int flags); 
    void render();
    void update();
    void handleEvents();
    void clean();
    bool running() { return isRunning; }
    SDL_Renderer* getRenderer() { return g_renderer; }
};
typedef Game theGame;

#endif /* defined(__Game__) */
