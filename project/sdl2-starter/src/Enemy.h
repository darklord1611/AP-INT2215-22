#ifndef __Enemy__
#define __Enemy__

#include "ShooterObject.h"

// Enemy base class
class Enemy: public ShooterObject 
{
protected:
    int m_score;
    bool specialEffect = false;
    bool deathEffect = false;
    int m_health;
    Enemy() : ShooterObject() {}
    virtual ~Enemy() {}
public:
    void setEffect(int effect) 
    { 
        if(effect >= 5) 
        {
            specialEffect = true;
            deathEffect = true;
        } else if(effect >= 3) 
        {
            specialEffect = true;
        }
    }
    int getHealth() { return m_health; }
    int getScore() { return m_score; }
    virtual string type() { return "Enemy"; }
};

#endif