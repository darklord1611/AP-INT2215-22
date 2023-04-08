#ifndef __RoofTurret__
#define __RoofTurret__

#include "Game.h"

class RoofTurret : public Enemy
{
public:
    RoofTurret();
    virtual ~RoofTurret() {}
    virtual void draw();
    virtual void collision();
    virtual void update();
};


class RoofTurretCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new RoofTurret();
    }
};

#endif 