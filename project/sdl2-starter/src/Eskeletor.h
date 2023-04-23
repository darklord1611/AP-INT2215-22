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
    void split();
};

class EskeletorCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new Eskeletor();
    }
};


#endif
