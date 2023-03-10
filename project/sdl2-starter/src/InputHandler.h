#include "SDL.h"
#include "Game.h"

class InputHandler 
{
private:
    static InputHandler* instance;
    InputHandler() {}
    ~InputHandler() {}

public:
    static InputHandler* Instance() 
    {
        if(instance == 0) 
        {
            instance = new InputHandler();
        }
        return instance;
    }
    void update(); 
    void clean();
};
typedef InputHandler _InputHandler;