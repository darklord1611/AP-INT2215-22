#include<iostream>
#include "Game.h" // our Game object

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char* argv[]) 
{
    Uint32 frameStart, frameTime;
    theGame::Instance()->init("SDL Create Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL); 
    while(theGame::Instance()->running()) 
    {
        frameStart = SDL_GetTicks();

        theGame::Instance()->handleEvents();
        theGame::Instance()->update();
        theGame::Instance()->render();

        frameTime = SDL_GetTicks() - frameStart;
        
        if(frameTime< DELAY_TIME) 
        { 
            SDL_Delay((int)(DELAY_TIME - frameTime)); 
        }
    } 
    theGame::Instance()->clean(); 
    return 0;
}