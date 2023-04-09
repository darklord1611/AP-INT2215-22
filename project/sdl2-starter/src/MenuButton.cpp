#include "MenuButton.h"
#include "InputHandler.h"

MenuButton::MenuButton() : ShooterObject() 
{
    
}

void MenuButton::load(unique_ptr<LoaderParams> const &pParams)
{
    ShooterObject::load(move(pParams));
    m_currentFrame = MOUSE_OUT;
    m_callbackID = pParams->getCallBackID();
}

void MenuButton::draw() 
{
    ShooterObject::draw();
}

void MenuButton::update() 
{
    Vector2D* pMousePos = _InputHandler::Instance()->getMousePosition();
    if((pMousePos->getX() < m_position.getX() + m_width) && (pMousePos->getX() > m_position.getX()) &&
    (pMousePos->getY() > m_position.getY()) && (pMousePos->getY() < m_position.getY() + m_height)) 
    {
        if(_InputHandler::Instance()->getMouseButtonState(LEFT) && m_bReleased) 
        {
            m_currentFrame = CLICKED;
            m_callback();
            m_bReleased = false;
        } 
        else if(!_InputHandler::Instance()->getMouseButtonState(LEFT)) 
        {
            m_bReleased = true;
            m_currentFrame = MOUSE_OVER;
        }
    } else m_currentFrame = MOUSE_OUT;
}

void MenuButton::clean() 
{
    ShooterObject::clean();
}