
#ifndef __AnimatedGraphic__
#define __AnimatedGraphic__

#include "Game.h"

class AnimatedGraphic : public SDLGameObject
{
private:
    int m_animSpeed;
public:
    AnimatedGraphic();
    virtual void load(const LoaderParams* pParams);
    virtual void update();
    virtual void draw();
    virtual void clean();
};


class AnimatedGraphicCreator : public BaseCreator 
{
    GameObject* createGameObject() const 
    {
        return new AnimatedGraphic();
    }
};
#endif // define __AnimatedGraphic__