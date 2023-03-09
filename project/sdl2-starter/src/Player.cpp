#include "Player.h"

Player::Player() : SDLGameObject() 
{

}

void Player::load(const LoaderParams* pParams) 
{
    SDLGameObject::load(pParams);
}
void Player::draw() 
{ 
    SDLGameObject::draw(); 
}

void Player::update() 
{
    m_x -= 1;
    m_currentFrame = int(((SDL_GetTicks() / 100) % 6));
}
void Player::clean() 
{
}