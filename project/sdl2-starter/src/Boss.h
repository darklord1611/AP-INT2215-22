#ifndef __Boss__
#define __Boss__

#include "Enemy.h"
#include "GameObjectFactory.h"

class Boss : public Enemy 
{
private:
    bool m_entered;
public:
    virtual ~Boss() {}
    Boss();
    virtual void load(unique_ptr<LoaderParams> const &pParams);
    virtual void collision();
    virtual void update();
};

class BossCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new Boss();
    }
};

#endif 