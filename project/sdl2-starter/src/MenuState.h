#ifndef __MenuState__
#define __MenuState__

#include "GameState.h"

class MenuState : public GameState 
{
private:
    static const string s_menuID;
public:
    virtual void update(); 
    virtual void render(); 
    virtual bool onEnter(); 
    virtual bool onExit(); 
    virtual string getStateID() const { return s_menuID; }
}

#endif // define __MenuState__

