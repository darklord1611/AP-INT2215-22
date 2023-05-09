#include "SmallEskeletor.h"
#include "SoundManager.h"
#include "Game.h"

SmallEskeletor::SmallEskeletor() : Enemy() 
{
    m_score = 0;
    m_dyingTime = 50;
    m_health = 1;
    m_moveSpeed = 2;
    m_bulletFiringSpeed = 0;
}
void SmallEskeletor::load(unique_ptr<LoaderParams> const &pParams) 
{
    ShooterObject::load(move(pParams));
    m_velocity.setX(-m_moveSpeed);
}

void SmallEskeletor::collision() 
{
    m_health -= 1;
    if(m_health == 0) 
    {
        if(!m_bPlayedDeathSound) 
        {
            TheSoundManager::Instance()->playSound("explode", 0);
            m_textureID = "explosion";
            m_currentFrame = 0;
            m_numFrames = 9;
            m_width = 40;
            m_height = 40;
            m_bDying = true;
        }
    }
}

void SmallEskeletor::update() 
{
    if(!m_bDying)
    {
    }
    else
    {
        m_velocity.setY(5);
        scroll(theGame::Instance()->getScrollSpeed());
        doDyingAnimation();
    }
    ShooterObject::update();
}