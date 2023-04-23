#include "ShotGlider.h"
#include "BulletHandler.h"
#include "Game.h"

ShotGlider::ShotGlider() : Glider()
{
    m_score = 20;
    m_bulletFiringSpeed = 50;
    m_moveSpeed = 3;
}

void ShotGlider::load(unique_ptr<LoaderParams> const &pParams) 
{
    ShooterObject::load(move(pParams));
    m_velocity.setY(-m_moveSpeed);
}

void ShotGlider::update()
{
    if(!m_bDying)
    {
        scroll(theGame::Instance()->getScrollSpeed() - 0.5);
        if(m_position.getY() + m_height >= theGame::Instance()->getGameHeight())
        {
            m_velocity.setY(-m_moveSpeed);
        }
        else if(m_position.getY() <= 0)
        {
            m_velocity.setY(m_moveSpeed);
        }
        if(m_bulletCounter == m_bulletFiringSpeed)
        {
            TheBulletHandler::Instance()->addEnemyBullet(m_position.getX(), m_position.getY() + 15, 16, 16, "bullet2", 1, Vector2D(-10, 0));
            m_bulletCounter = 0;
        }
        m_bulletCounter++;
    }
    else
    {
        m_velocity.setX(0);
        m_velocity.setY(5);
        scroll(theGame::Instance()->getScrollSpeed());
        doDyingAnimation();
    }
    ShooterObject::update();
}