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