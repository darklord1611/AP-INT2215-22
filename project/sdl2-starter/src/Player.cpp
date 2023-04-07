#include "Player.h"
#include "InputHandler.h"
#include "BulletHandler.h"
#include "Game.h"

Player::Player() : ShooterObject() 
{
    m_invulnerable = false;
    m_invulnerableTime = 200;
    m_invulnerableCounter = 0;
}

void Player::load(unique_ptr<LoaderParams> const &pParams)
{
    // inherited load function
    ShooterObject::load(move(pParams));
    
    // can set up the players inherited values here
    
    // set up bullets
    m_bulletFiringSpeed = 13;
    m_moveSpeed = 3;
    
    // we want to be able to fire instantly
    m_bulletCounter = m_bulletFiringSpeed;
    
    // time it takes for death explosion
    m_dyingTime = 50;

}

void Player::draw() 
{ 
    _TextureManager::Instance()->drawFrame(m_textureID, (int) m_position.getX(), (int) m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, theGame::Instance()->getRenderer(), m_alpha, SDL_FLIP_HORIZONTAL);
}

void Player::update() 
{
    if(!m_bDying)
        {
            // reset velocity
            m_velocity.setX(0);
            m_velocity.setY(0);
            // get input
            handleInput();
            // do normal position += velocity update
            ShooterObject::update();
            // update the animation
            handleAnimation();
        }
        else // if the player is doing the death animation
        {
            m_currentFrame = int(((SDL_GetTicks() / (100)) % m_numFrames));
            // if the death animation has completed
            ressurect();
            // if(m_dyingCounter == m_dyingTime)
            // {
            //     // ressurect the player
            //     ressurect();
            // }
            // m_dyingCounter++;
        }
}

void Player::handleAnimation() 
{
    // if the player is invulnerable we can flash its alpha to let people know
    if(m_invulnerable)
    {
        // invulnerability is finished, set values back
        if(m_invulnerableCounter == m_invulnerableTime)
        {
            m_invulnerable = false;
            m_invulnerableCounter = 0;
            m_alpha = 255;
        }
        else // otherwise, flash the alpha on and off
        {
            if(m_alpha == 255)
            {
                m_alpha = 0;
            }
            else
            {
                m_alpha = 255;
            }
        }
        // increment our counter
        m_invulnerableCounter++;
    }
    m_currentFrame = int(((SDL_GetTicks() / (100)) % m_numFrames));
}

void Player::ressurect() 
{
    m_position.setX(10);
    m_position.setY(200);
    m_bDying = false;
    
    m_textureID = "player";
    
    m_currentFrame = 0;
    m_numFrames = 5;
    m_width = 128;
    m_height = 55;
    
    m_dyingCounter = 0;
    m_invulnerable = true;

}
void Player::handleInput()
{
    if(!m_bDead)
    {
        // handle keys
        if(_InputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP) && m_position.getY() > 0)
        {
            m_velocity.setY(-m_moveSpeed);
        }
        else if(_InputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN) && (m_position.getY() + m_height) < theGame::Instance()->getGameHeight() - 10)
        {
            m_velocity.setY(m_moveSpeed);
        }
        
        if(_InputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT) && m_position.getX() > 0)
        {
            m_velocity.setX(-m_moveSpeed);
        }
        else if(_InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT) && (m_position.getX() + m_width) < theGame::Instance()->getGameWidth())
        {
            m_velocity.setX(m_moveSpeed);
        }
        
        if(_InputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE))
        {
            if(m_bulletCounter == m_bulletFiringSpeed)
            {
                TheBulletHandler::Instance()->addPlayerBullet(m_position.getX() + 90, m_position.getY() + 12, 11, 11, "bullet1", 1, Vector2D(10,0));
                m_bulletCounter = 0;
            }
            
            m_bulletCounter++;
        }
        else
        {
            m_bulletCounter = m_bulletFiringSpeed;
        }
    }
}



void Player::clean() 
{
    ShooterObject::clean();
}

void Player::collision()
{
        m_textureID = "largeexplosion";
        m_currentFrame = 0;
        m_numFrames = 9;
        m_width = 60;
        m_height = 60;
        m_bDying = true;
}
