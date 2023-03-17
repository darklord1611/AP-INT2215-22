#ifndef __MenuState__
#define __MenuState__

#include "GameState.h"
#include "GameObject.h"
#include "Game.h"
class MenuState : public GameState 
{
private:
    vector<GameObject*> m_gameObjects;
    static const string s_menuID;
public:
    virtual void update(); 
    virtual void render(); 
    virtual bool onEnter(); 
    virtual bool onExit(); 
    virtual string getStateID() const { return s_menuID; }
};

#endif // define __MenuState__

