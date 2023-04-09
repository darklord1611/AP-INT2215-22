#ifndef __ShotGlider__
#define __ShotGlider__

#include "Glider.h"

class ShotGlider : public Glider
{
public:
    ShotGlider();
    virtual ~ShotGlider() {}
    virtual void load(unique_ptr<LoaderParams> const &pParams);
    virtual void update();
};

class ShotGliderCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new ShotGlider();
    }
};

#endif 