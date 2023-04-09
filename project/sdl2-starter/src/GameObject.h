
#ifndef __GameObject__
#define __GameObject__

#include "LoaderParams.h"
#include "Vector2D.h"
#include<memory>
#include<string>
#include<iostream>

using namespace std;

class GameObject 
{
protected:
    // movement variables
    Vector2D m_position;
    Vector2D m_velocity;
    
    // size variables
    int m_width;
    int m_height;
    
    // animation variables
    int m_currentRow;
    int m_currentFrame;
    int m_numFrames;
    string m_textureID;
    
    // common boolean variables
    bool m_bUpdating;
    bool m_bDead;
    bool m_bDying;
    
    // blending
    int m_alpha;

    GameObject() : m_position(0,0), m_velocity(0,0), m_width(0), m_height(0),
    m_currentRow(0), m_currentFrame(0), m_numFrames(0), m_bUpdating(true), m_bDead(false), m_bDying(false), m_alpha(255)
    { }
public:
    virtual ~GameObject() {}
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void clean() = 0;
    virtual void load(unique_ptr<LoaderParams> const &pParams) = 0;
    virtual void loadBullet(unique_ptr<LoaderParams> const &pParams, Vector2D heading) = 0;
    virtual void collision() = 0;
    virtual string type() = 0;

    void scroll(double scrollSpeed)
    {
        if(type() != "Player") // player is never scrolled
        {
            m_position.setX(m_position.getX() - scrollSpeed);
        }
    }
    // getter functions for some variable
    Vector2D& getPosition() { return m_position; }
    Vector2D& getVelocity() { return m_velocity; }
    
    int getWidth() { return m_width; }
    int getHeight() { return m_height; }
    
    // is the object currently being updated?
    bool updating() { return m_bUpdating; }
    
    // is the object dead?
    bool dead() { return m_bDead; }
    
    // is the object doing a death animation?
    bool dying() { return m_bDying; }
    
    // set whether to update the object or not
    void setUpdating(bool updating) { m_bUpdating = updating; }

};

#endif // define __GameObject__
