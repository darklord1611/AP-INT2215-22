#include "RoofTurret.h"


RoofTurret::RoofTurret() 
{
    m_score = 150;
    m_dyingTime = 1000;
    m_health = 15;
    m_bulletFiringSpeed = 50;
}

void RoofTurret::collision() 
{
    m_health -= 1;
    if(m_health == 0)
    {
        m_textureID = "largeexplosion";
        m_currentFrame = 0;
        m_numFrames = 9;
        m_width = 60;
        m_height = 60;
        m_bDying = true;
    }
}



void RoofTurret::draw() 
{
    _TextureManager::Instance()->drawFrame(m_textureID, (int) m_position.getX(), (int) m_position.getY(),
    m_width, m_height, m_currentRow, m_currentFrame, theGame::Instance()->getRenderer(), 255, SDL_FLIP_VERTICAL);

}

void RoofTurret::update() 
{
    if(!m_bDying)
        {
            scroll(theGame::Instance()->getScrollSpeed());
        
            if(m_bulletCounter == m_bulletFiringSpeed)
            {
                TheBulletHandler::Instance()->addEnemyBullet(m_position.getX(), m_position.getY() + 20, 16, 16, "bullet2", 1, Vector2D(-3, 3));
                TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() + 20, m_position.getY() + 20, 16, 16, "bullet2", 1, Vector2D(0, 3));
                TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() + 40, m_position.getY() + 20, 16, 16, "bullet2", 1, Vector2D(3, 3));
                m_bulletCounter = 0;
            }
            
            m_bulletCounter++;
        }
        else
        {
            scroll(theGame::Instance()->getScrollSpeed());
            doDyingAnimation();
        }
}

