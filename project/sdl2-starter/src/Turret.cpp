#include "Turret.h"
#include "SoundManager.h"
#include "Game.h"
#include "BulletHandler.h"

Turret::Turret() 
{
    m_score = 40;
    m_dyingTime = 1000;
    m_health = 15;
    m_bulletFiringSpeed = 40;
}

void Turret::collision() 
{
    m_health -= 1;
    if(m_health == 0)
    {
        for (int i = 0; i < 360; i += 20) 
        {
            double angle = i * (M_PI / 180);
            double x = 5 * cos(angle);
            double y = 5 * sin(angle);
            TheBulletHandler::Instance()->addEnemyBullet(m_position.getX(), m_position.getY(), 16, 16, "bullet1", 1, Vector2D(x, y));
        }
        if(!m_bPlayedDeathSound) 
        {
            TheSoundManager::Instance()->playSound("explode", 0);
            m_textureID = "largeexplosion";
            m_currentFrame = 0;
            m_numFrames = 9;
            m_width = 60;
            m_height = 60;
            m_bDying = true;
        }
    }
}

void Turret::update() 
{
    if(!m_bDying)
    {
        scroll(theGame::Instance()->getScrollSpeed());

        if(m_bulletCounter == m_bulletFiringSpeed)
        {
            if(specialEffect == true) 
            {
                TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() + 10, m_position.getY() + 20, 16, 16, "bullet2", 1, Vector2D(-2, -4));
                TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() + 30, m_position.getY() + 20, 16, 16, "bullet2", 1, Vector2D(2, -4));
            }
            TheBulletHandler::Instance()->addEnemyBullet(m_position.getX(), m_position.getY(), 16, 16, "bullet2", 1, Vector2D(-4, -4));
            TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() + 20, m_position.getY(), 16, 16, "bullet2", 1, Vector2D(0, -4));
            TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() + 40, m_position.getY(), 16, 16, "bullet2", 1, Vector2D(4, -4));
            m_bulletCounter = 0;
        }
        
        m_bulletCounter++;
    }
    else
    {
        m_velocity.setY(5);
        scroll(theGame::Instance()->getScrollSpeed());
        doDyingAnimation();
    }
    ShooterObject::update();
}