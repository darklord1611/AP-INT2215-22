#ifndef __SmallEskeletor__
#define __SmallEskeletor__

#include "Enemy.h"
#include "GameObjectFactory.h"

class SmallEskeletor : public Enemy
{
public:
    virtual ~SmallEskeletor() {}
    SmallEskeletor();
    virtual void load(unique_ptr<LoaderParams> const &pParams);
    virtual void collision();
    virtual void update();
};

class SmallEskeletorCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new SmallEskeletor();
    }
};

#endif