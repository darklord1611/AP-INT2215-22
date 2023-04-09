#ifndef __Bullet__
#define __Bullet__

#include "ShooterObject.h"

class PlayerBullet : public ShooterObject
{
private:
    Vector2D m_heading;
public:
    PlayerBullet() : ShooterObject() 
    {
        m_dyingTime = 5;
    }
    virtual ~PlayerBullet() {}
    virtual string type() { return "PlayerBullet"; }
    virtual void loadBullet(unique_ptr<LoaderParams> const &pParams, Vector2D heading)
    {
        ShooterObject::load(move(pParams));
        m_heading = heading;
    }
    virtual void load(unique_ptr<LoaderParams> const &pParams) {}
    virtual void draw() { ShooterObject::draw(); }
    virtual void collision()
    {
        m_textureID = "smallexplosion";
        m_currentFrame = 0;
        m_numFrames = 2;
        m_width = 20;
        m_height = 20;
        m_bDying = true;
    }
    virtual void update()
    {
        if(!m_bDying)
        {
            m_velocity.setX(m_heading.getX());
            m_velocity.setY(m_heading.getY());
            ShooterObject::update();
        }
        else
        {
            m_velocity.setX(0);
            m_velocity.setY(0);
            doDyingAnimation();
        }
    }
    virtual void clean() { ShooterObject::clean(); }
};

class EnemyBullet : public PlayerBullet
{
public:
    EnemyBullet() : PlayerBullet() {}
    virtual ~EnemyBullet() {}
    virtual string type() { return "EnemyBullet"; }
};

#endif