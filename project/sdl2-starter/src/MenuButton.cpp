#include "MenuButton.h"

MenuButton::MenuButton(const LoaderParams* pParams) : SDLGameObject(pParams) 
{
    m_currentFrame = MOUSE_OUT;
}

void MenuButton::draw() 
{
    SDLGameObject::draw();
}

void MenuButton::update() 
{
    Vector2D* pMousePos = _InputHandler::Instance()->getMousePosition();
    if((pMousePos->getX() < m_position.getX() + m_width) && (pMousePos->getX() > m_position.getX()) &&
    (pMousePos->getY() > m_position.getY()) && (pMousePos->getY() < m_position.getY() + m_height)) 
    {
        m_currentFrame = MOUSE_OVER;
        if(_InputHandler::Instance()->getMouseButtonState(LEFT)) 
        {
            m_currentFrame = CLICKED;
        }
    } else m_currentFrame = MOUSE_OUT;
}

void MenuButton::clean() 
{
    SDLGameObject::clean();
}