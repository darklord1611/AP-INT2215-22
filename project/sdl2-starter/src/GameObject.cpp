#include "GameObject.h"
#include "TextureManager.h"

void GameObject::load(int x, int y, int width, int height, string textureID) 
{
    m_x = x;
    m_y = y;
    m_width = width; 
    m_height = height; 
    m_textureID = textureID;
}

void GameObject::draw(SDL_Renderer* g_renderer) 
{
    TextureManager::Instance()->(m_textureID, m_x, m_y,m_width, m_height, g_renderer);
}

void GameObject::update() 
{
    m_x += 1;
}