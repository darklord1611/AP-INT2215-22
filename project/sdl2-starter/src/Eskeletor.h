#ifndef __Eskeletor__
#define __Eskeletor__

#include "Enemy.h"
#include "GameObjectFactory.h"

class Eskeletor : public Enemy
{
public:
    virtual ~Eskeletor() {}
    Eskeletor();
    virtual void collision();
    virtual void update();
};

class EskeletorCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new Eskeletor();
    }
};


#endif
