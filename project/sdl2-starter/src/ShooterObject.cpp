#include "ShooterObject.h"
#include "TextureManager.h"
#include "Game.h"

ShooterObject::ShooterObject() : GameObject() 
{
    m_bulletFiringSpeed = 0;
    m_bulletCounter = 0;
    m_moveSpeed = 0;
    m_dyingTime = 0;
    m_dyingCounter = 0;
    
}

void ShooterObject::load(unique_ptr<LoaderParams> const &pParams)
{
    m_position = Vector2D(pParams->getX(), pParams->getY());
    m_velocity = Vector2D(0,0);
    m_width = pParams->getWidth(); 
    m_height = pParams->getHeight();
    m_textureID = pParams->getTextureID();
    m_numFrames = pParams->getNumFrames();
}

void ShooterObject::draw() 
{
        _TextureManager::Instance()->drawFrame(m_textureID, (int) m_position.getX(), (int) m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, theGame::Instance()->getRenderer());
}

void ShooterObject::update() 
{
    // m_velocity += m_acceleration;
    m_position += m_velocity;
    m_currentFrame = int(((SDL_GetTicks() / 100) % m_numFrames));
}

void ShooterObject::doDyingAnimation()
{
    m_currentFrame = int(((SDL_GetTicks() / 100) % m_numFrames));
    
    if(m_dyingCounter == m_dyingTime)
    {
        m_bDead = true;
    }
    m_dyingCounter++;
}




