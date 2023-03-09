#include "SDLGameObject.h"
#include "TextureManager.h"
#include "Game.h"

SDLGameObject::SDLGameObject() : GameObject() 
{

}
void SDLGameObject::load(const LoaderParams* pParams) 
{
    m_x = pParams->getX(); 
    m_y = pParams->getY(); 
    m_width = pParams->getWidth(); 
    m_height = pParams->getHeight();
    m_textureID = pParams->getTextureID();
    m_currentRow = 1; 
    m_currentFrame = 1;
}

void SDLGameObject::draw() 
{
    _TextureManager::Instance()->drawFrame(m_textureID, m_x, m_y, m_width, m_height, m_currentRow, m_currentFrame,theGame::Instance()->getRenderer());
}

void SDLGameObject::update() 
{

}

void SDLGameObject::clean() 
{

}



