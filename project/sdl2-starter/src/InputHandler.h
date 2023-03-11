#pragma once

#ifndef __InputHandler__
#define __InputHandler__
#include<SDL2/SDL.h>
#include "Game.h"

class InputHandler 
{
private:
    static InputHandler* instance;
    InputHandler() {}
    ~InputHandler() {}
    //Pointer to the array returned by SDL_GetKeyboardState with "int* numkeys" arg
	const Uint8* m_keystates;

	//handle keyboard events
	void onKeyDown();
	void onKeyUp();
public:
    static InputHandler* Instance() 
    {
        if(instance == 0) 
        {
            instance = new InputHandler();
        }
        return instance;
    }
    bool isKeyDown(SDL_Scancode key);
    void update(); 
    void clean();
};
typedef InputHandler _InputHandler;

#endif // define __InputHandler__