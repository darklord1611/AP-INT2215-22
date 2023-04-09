#ifndef __Enemy__
#define __Enemy__

#include "ShooterObject.h"

// Enemy base class
class Enemy: public ShooterObject 
{
protected:
    int m_score;
    int m_health;
    Enemy() : ShooterObject() {}
    virtual ~Enemy() {}
public:
    int getHealth() { return m_health; }
    int getScore() { return m_score; }
    virtual string type() { return "Enemy"; }
};

#endif