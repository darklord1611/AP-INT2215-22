#include "Player.h"

void Player::load(int x, int y, int width, int height, string textureID) 
{ 
    GameObject::load(x, y, width, height, textureID); 
}

void Player::draw(SDL_Renderer* g_renderer) 
{ 
    GameObject::draw(g_renderer); 
}

void Player::update() 
{
    m_x -= 1;
}