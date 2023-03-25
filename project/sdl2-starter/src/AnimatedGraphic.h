
#ifndef __AnimatedGraphic__
#define __AnimatedGraphic__

#include "Game.h"

class AnimatedGraphic : public SDLGameObject
{
public:
    AnimatedGraphic();
    virtual void load(const LoaderParams* pParams);
    virtual void update();
    virtual void draw();
    virtual void clean();
};

#endif // define __AnimatedGraphic__