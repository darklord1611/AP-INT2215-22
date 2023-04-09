
#ifndef __AnimatedGraphic__
#define __AnimatedGraphic__

#include "ShooterObject.h"
#include "GameObjectFactory.h"

class AnimatedGraphic : public ShooterObject
{
private:
    int m_animSpeed;
public:
    AnimatedGraphic();
    virtual void load(unique_ptr<LoaderParams> const &pParams);
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