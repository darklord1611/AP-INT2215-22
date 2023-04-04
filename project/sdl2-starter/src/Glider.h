#ifndef __Glider__
#define __Glider__

#include <iostream>
#include "GameObjectFactory.h"
#include "BulletHandler.h"
#include <math.h>
#include "Enemy.h"

class Glider : public Enemy
{
private:
    int m_maxHeight;
    int m_minHeight;
    int m_gap;
public:
    Glider() : Enemy()
    {
        m_dyingTime = 25;
        m_health = 1;
        m_moveSpeed = 3;
        m_gap = 60;
    }
    virtual ~Glider() {}
    virtual void load(unique_ptr<LoaderParams> const &pParams)
    {
        ShooterObject::load(move(pParams));

        m_velocity.setX(-m_moveSpeed);
        m_velocity.setY(m_moveSpeed / 2);
        
        m_maxHeight = m_position.getY() + m_gap;
        m_minHeight = m_position.getY() - m_gap;
    }
    virtual void collision()
    {
        m_health -= 1;
        if(m_health == 0)
        {
                m_textureID = "explosion";
                m_currentFrame = 0;
                m_numFrames = 9;
                m_width = 40;
                m_height = 40;
                m_bDying = true;
        }
    }
    virtual void update()
    {
        if(!m_bDying)
        {
            if(m_position.getY() >= m_maxHeight)
            {
                m_velocity.setY(-m_moveSpeed);
            }
            else if(m_position.getY() <= m_minHeight)
            {
                m_velocity.setY(m_moveSpeed);
            }
        }
        else
        {
            m_velocity.setX(0);
            m_velocity.setY(0);
            doDyingAnimation();
        }
        ShooterObject::update();
    }
};

class GliderCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new Glider();
    }
};

#endif 