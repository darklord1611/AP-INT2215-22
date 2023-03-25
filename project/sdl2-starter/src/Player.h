
#ifndef __Player__
#define __Player__

#include "SDLGameObject.h"

class Player: public SDLGameObject 
{
public:
    Player();
    virtual void load(const LoaderParams* pParams);
    virtual void draw(); 
    virtual void update(); 
    virtual void clean();
};

class PlayerCreator : public BaseCreator 
{
    GameObject* createGameObject() const
    {
        return new Player();
    }
};

#endif // define __Player__