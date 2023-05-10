#include "Boss.h"
#include "Game.h"
#include "BulletHandler.h"
#include "SoundManager.h"

Boss::Boss() : Enemy() 
{
    m_score = 100;
    m_health = 120;
    m_dyingTime = 100;
    m_bulletFiringSpeed = 50;
    m_moveSpeed = 2;
    m_entered = false;
}

void Boss::load(unique_ptr<LoaderParams> const &pParams) 
{
    ShooterObject::load(move(pParams));
    m_velocity.setY(-m_moveSpeed);
}

void Boss::collision()
{
    if(m_entered)
    {
        m_health -= 1;
        if(m_health == 0)
        {
            m_position.setX(m_position.getX() + 30);
            m_position.setY(m_position.getY() + 70);
            TheSoundManager::Instance()->playSound("explode", 0);
            m_textureID = "bossexplosion";
            m_currentFrame = 0;
            m_numFrames = 9;
            m_width = 180;
            m_height = 180;
            m_bDying = true;
        }
    }
}


void Boss::update()
{
    if(!m_entered)
    {
        scroll(theGame::Instance()->getScrollSpeed());
        if(m_position.getX() < (theGame::Instance()->getGameWidth() - (m_width + 20)))
        {
            m_entered = true;
        } else 
        {
            if(m_health < 120) m_health++;
        }
    }
    else
    {
        if(!m_bDying)
        {
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
                TheBulletHandler::Instance()->addEnemyBullet(m_position.getX(), m_position.getY() + 25, 16, 16, "bullet2", 1, Vector2D(-10, 0));
                
                TheBulletHandler::Instance()->addEnemyBullet(m_position.getX(), m_position.getY() + 200, 16, 16, "bullet2", 1, Vector2D(-10, 0));
                TheBulletHandler::Instance()->addEnemyBullet(m_position.getX(), m_position.getY() + 215, 16, 16, "bullet2", 1, Vector2D(-10, 0));
                
                m_bulletCounter = 0;
            }
            
            m_bulletCounter++;
            
            ShooterObject::update();
        }
        else
        {
            scroll(theGame::Instance()->getScrollSpeed());
            doDyingAnimation();
        }
    }
}

