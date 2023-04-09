#ifndef __InputHandler__
#define __InputHandler__

#include<SDL2/SDL.h>
#include"Vector2D.h"
#include<vector>
#include<iostream>

using namespace std;

enum mouse_buttons 
{
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

class InputHandler 
{
private:
    static InputHandler* instance;
    InputHandler();
    ~InputHandler();
    //Pointer to the array returned by SDL_GetKeyboardState with "int* numkeys" arg
	const Uint8* m_keystates = NULL;
    vector<bool> m_mouseButtonStates;
    Vector2D* m_mousePosition;
    // handle mouse events
    void onMouseMove(SDL_Event &event);
    void onMouseButtonDown(SDL_Event &event);
    void onMouseButtonUp(SDL_Event &event);
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
    Vector2D* getMousePosition();
    bool getMouseButtonState(int buttonNumber);
    bool isKeyDown(SDL_Scancode key);
    void update(); 
    void clean();
    void reset();
};
typedef InputHandler _InputHandler;

#endif // define __InputHandler__