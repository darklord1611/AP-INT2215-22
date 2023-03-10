#include "InputHandler.h"

void InputHandler::update() 
{
    SDL_Event event;
    while(SDL_PollEvent(&event)) 
    { 
        if(event.type == SDL_QUIT) 
        { 
            theGame::Instance()->quit(); 
        } 
    }
}

void InputHandler::clean() 
{
    
}