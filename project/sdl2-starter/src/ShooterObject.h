#pragma once
#include "Vector2D.h"
#include "GameObject.h"
#include "GameObjectFactory.h"

class ShooterObject : public GameObject 
{
protected:
    ShooterObject();
    void doDyingAnimation();
    
    int m_bulletFiringSpeed;
    int m_bulletCounter;
    int m_moveSpeed;
    
    // how long the death animation takes, along with a counter
    int m_dyingTime;
    int m_dyingCounter;

public:
    virtual ~ShooterObject() {}
    virtual void clean() {}
    virtual void collision() {}
    virtual void load(unique_ptr<LoaderParams> const &pParams);
    virtual void loadBullet(unique_ptr<LoaderParams> const &pParams, Vector2D heading) {}
    virtual void draw(); 
    virtual void update(); 
    virtual string type() { return "SDLGameObject"; }
};