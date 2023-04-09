#include "Eskeletor.h"
#include "SoundManager.h"
#include "BulletHandler.h"
#include "Game.h"
#include<cstdlib>

Eskeletor::Eskeletor() : Enemy() 
{
    m_score = 30;
    m_dyingTime = 50;
    m_health = 3;
    m_moveSpeed = 3;
    m_bulletFiringSpeed = 50;
}

void Eskeletor::collision()
{
    m_health -= 1;
    if(m_health == 0)
    {
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

void Eskeletor::update()
{
    if(!m_bDying)
    {
        scroll(theGame::Instance()->getScrollSpeed() - 0.5);
        if(m_bulletCounter == m_bulletFiringSpeed)
        {
            TheBulletHandler::Instance()->addEnemyBullet(m_position.getX(), m_position.getY(), 16, 16, "bullet1", 1, Vector2D(-1 * (rand() % 5 + 1), rand() % 10 - 5));
            TheBulletHandler::Instance()->addEnemyBullet(m_position.getX(), m_position.getY(), 16, 16, "bullet1", 1, Vector2D(-1 * (rand() % 5 + 1), rand() % 10 - 5));
            TheBulletHandler::Instance()->addEnemyBullet(m_position.getX(), m_position.getY(), 16, 16, "bullet1", 1, Vector2D(-1 * (rand() % 5 + 1), rand() % 10 - 5));
            m_bulletCounter = 0;
        }
        m_bulletCounter++;
        
    }
    else
    {
        m_velocity.setY(0);
        scroll(theGame::Instance()->getScrollSpeed());
        doDyingAnimation();
    }
    ShooterObject::update();
}
