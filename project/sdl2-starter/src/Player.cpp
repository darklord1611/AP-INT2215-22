#include "Player.h"

void Player::load(int x, int y, int width, int height, string textureID, string fileName) 
{ 
    GameObject::load(x, y, width, height, textureID, fileName); 
}

void Player::draw(SDL_Renderer* g_renderer) 
{ 
    GameObject::draw(g_renderer); 
}

void Player::update() 
{
    m_x -= 1;
}