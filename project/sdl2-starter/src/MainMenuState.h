#ifndef __MainMenuState__
#define __MainMenuState__

#include "MenuState.h"
#include "GameObject.h"
#include "Game.h"

class MainMenuState : public MenuState 
{
private:
    virtual void setCallbacks(const vector<Callback> &callbacks);
    // callback functions
    static void s_menuToPlay();
    static void s_exitFromMenu();
    
    vector<GameObject*> m_gameObjects;
    static const string s_menuID;
public:
    virtual void update(); 
    virtual void render(); 
    virtual bool onEnter(); 
    virtual bool onExit(); 
    virtual string getStateID() const { return s_menuID; }
    virtual ~MainMenuState() {}
};

#endif // define __MainMenuState__

