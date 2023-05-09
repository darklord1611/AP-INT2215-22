#include "ShotGlider.h"
#include "BulletHandler.h"
#include "TextureManager.h"
#include "Game.h"

ShotGlider::ShotGlider() : Glider()
{
    isInvisible = false;
    m_invisibleCounter = 0;
    m_invisibleTime = 400;
    m_score = 20;
    m_bulletFiringSpeed = 100;
    m_moveSpeed = 3;
}

void ShotGlider::load(unique_ptr<LoaderParams> const &pParams) 
{
    ShooterObject::load(move(pParams));
    m_velocity.setY(-m_moveSpeed);
}
void ShotGlider::draw() 
{
    _TextureManager::Instance()->drawFrame(m_textureID, (int) m_position.getX(), (int) m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, theGame::Instance()->getRenderer(), m_alpha);
}
void ShotGlider::update()
{
    if(!m_bDying)
    {
        if(specialEffect) isInvisible = true;
        scroll(theGame::Instance()->getScrollSpeed());
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
            isInvisible = false;
        }
        handleAnimation();
        m_bulletCounter++;
    }
    else
    {
        isInvisible = false;
        m_velocity.setX(0);
        m_velocity.setY(5);
        scroll(theGame::Instance()->getScrollSpeed());
        doDyingAnimation();
    }
    ShooterObject::update();
}


void ShotGlider::handleAnimation() 
{
    if(isInvisible) 
    {
        if(m_invisibleCounter == m_invisibleTime) 
        {
            isInvisible = false;
            m_alpha = 255;
            m_invisibleCounter = 0;
        } else 
        {
            if(m_alpha > 0) 
            {
                m_alpha--;
            }
        }
        m_invisibleCounter++;
    }
}