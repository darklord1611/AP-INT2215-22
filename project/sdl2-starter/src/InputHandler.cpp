#include "InputHandler.h"
#include "Game.h"

InputHandler* InputHandler::instance = 0;

InputHandler::InputHandler()
{
    for(int i = 0; i < 3; i++) 
    {
        m_mouseButtonStates.push_back(false);
    }
    m_mousePosition = new Vector2D(0,0);
}
InputHandler::~InputHandler() 
{
    // delete m_keystates;
    delete m_mousePosition;
    m_mouseButtonStates.clear();
}

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
            case SDL_MOUSEMOTION:
                onMouseMove(event);
                break;
            case SDL_MOUSEBUTTONDOWN:
                onMouseButtonDown(event);
                break;
            case SDL_MOUSEBUTTONUP:
                onMouseButtonUp(event);
                break;
            default:
                break;
        }
    }
}

void InputHandler::clean() 
{
    InputHandler::~InputHandler();
}

// mouse events functions

Vector2D* InputHandler::getMousePosition() 
{
    return m_mousePosition;
}

void InputHandler::onMouseMove(SDL_Event &event) 
{
    m_mousePosition->setX((double)event.motion.x);
    m_mousePosition->setY((double)event.motion.y);
}

void InputHandler::onMouseButtonUp(SDL_Event &event) 
{
    if(event.button.button == SDL_BUTTON_LEFT) 
    {
        m_mouseButtonStates[LEFT] = false;
    }
    if(event.button.button == SDL_BUTTON_MIDDLE) 
    {
        m_mouseButtonStates[MIDDLE] = false;
    }
    if(event.button.button == SDL_BUTTON_RIGHT) 
    {
        m_mouseButtonStates[RIGHT] = false;
    }
}

void InputHandler::onMouseButtonDown(SDL_Event &event) 
{
    if(event.button.button == SDL_BUTTON_LEFT) 
    {
        m_mouseButtonStates[LEFT] = true;
    }
    if(event.button.button == SDL_BUTTON_MIDDLE) 
    {
        m_mouseButtonStates[MIDDLE] = true;
    }
    if(event.button.button == SDL_BUTTON_RIGHT) 
    {
        m_mouseButtonStates[RIGHT] = true;
    }
}

bool InputHandler::getMouseButtonState(int buttonNumber) 
{
    return m_mouseButtonStates[buttonNumber];
}

// keyboard events functions

bool InputHandler::isKeyDown(SDL_Scancode key) 
{
    if (m_keystates != 0)
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
	m_keystates = SDL_GetKeyboardState(0);
}

void InputHandler::onKeyUp()
{
	m_keystates = SDL_GetKeyboardState(0);
}

void InputHandler::reset() 
{
    m_mouseButtonStates[LEFT] = false;
    m_mouseButtonStates[MIDDLE] = false;
    m_mouseButtonStates[RIGHT] = false;
}