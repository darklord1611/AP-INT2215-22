#ifndef __Enemy__
#define __Enemy__

#include "ShooterObject.h"

// Enemy base class
class Enemy: public ShooterObject 
{
protected:
    int m_health;
    Enemy() : ShooterObject() {}
    virtual ~Enemy() {}
public:
    virtual string type() { return "Enemy"; }
};

#endif