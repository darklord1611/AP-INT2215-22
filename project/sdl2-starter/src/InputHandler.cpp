#include "InputHandler.h"

InputHandler* InputHandler::instance = 0;
void InputHandler::update() 
{
    SDL_Event event;
    while(SDL_PollEvent(&event)) 
    { 
        switch(event.type) 
        {
            case SDL_QUIT:
                theGame::Instance()->quit();
                break;
            case SDL_KEYDOWN:
                onKeyDown();
                break;
            case SDL_KEYUP:
                onKeyUp();
                break;
        }
    }
}

void InputHandler::clean() 
{
    
}

bool InputHandler::isKeyDown(SDL_Scancode key) 
{
    if (m_keystates != NULL)
	{
		if (m_keystates[key] == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

void InputHandler::onKeyDown()
{
	m_keystates = SDL_GetKeyboardState(NULL);
}

void InputHandler::onKeyUp()
{
	m_keystates = SDL_GetKeyboardState(NULL);
}
