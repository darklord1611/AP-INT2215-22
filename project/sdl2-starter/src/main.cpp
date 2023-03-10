#include<iostream>
#include "Game.h" // our Game object


int main(int argc, char* argv[]) 
{
    theGame::Instance()->init("SDL Create Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_OPENGL); 
    while(theGame::Instance()->running()) 
    {

        theGame::Instance()->handleEvents();

        theGame::Instance()->update();

        theGame::Instance()->render(); 
    } 
    theGame::Instance()->clean(); 
    return 0;
}