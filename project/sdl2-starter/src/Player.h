
#ifndef __Player__
#define __Player__

#include "SDLGameObject.h"


class Player: public SDLGameObject 
{
private:
    void handleInput();

    Vector2D* target;
public:
    Player(const LoaderParams* pParams);
    virtual void draw(); 
    virtual void update(); 
    virtual void clean();
};
#endif // define __Player__