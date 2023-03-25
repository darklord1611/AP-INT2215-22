#pragma once
#include "Vector2D.h"
#include "GameObject.h"
#include "GameObjectFactory.h"

class SDLGameObject : public GameObject 
{
protected:
    Vector2D m_position;
    Vector2D m_velocity;
    // Vector2D m_acceleration;
    int m_width; 
    int m_height;
    int m_currentRow;
    int m_numFrames;
    int m_callbackID;
    int m_currentFrame;
    string m_textureID;

public:
    SDLGameObject();
    Vector2D& getPosition() { return m_position; }
    int getWidth() { return m_width; }
    int getHeight() { return m_height; }
    virtual void load(const LoaderParams* pParams);
    virtual void draw(); 
    virtual void update(); 
    virtual void clean(); 
};