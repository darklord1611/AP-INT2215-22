
#ifndef __AnimatedGraphic__
#define __AnimatedGraphic__

#include "Game.h"

class AnimatedGraphic : public SDLGameObject
{
private:
    int m_animSpeed;
public:
    AnimatedGraphic(const LoaderParams* pParams, int animSpeed);
    virtual void update();
    virtual void draw();
    virtual void clean();
};

#endif // define __AnimatedGraphic__