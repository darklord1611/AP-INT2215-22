#include "Enemy.h"

void Enemy::load(int x, int y, int width, int height, string textureID, string fileName) 
{ 
    GameObject::load(x, y, width, height, textureID, fileName); 
}

void Enemy::draw(SDL_Renderer* g_renderer) 
{ 
    GameObject::draw(g_renderer); 
}

void Enemy::update() 
{
    m_y += 1;
    m_x += 1;
}