#ifndef __TransitionState__
#define __TransitionState__

#include "MenuState.h"
#include "GameObject.h"

class TransitionState : public MenuState 
{
private:
    virtual void setCallbacks(const vector<Callback> &callbacks);
    // callback functions
    static void s_gameOverToMain();
    static void s_nextLevel();

    static const string s_transitionID;
    vector<GameObject*> m_gameObjects;
public:
    virtual void update(); 
    virtual void render(); 
    virtual bool onEnter(); 
    virtual bool onExit(); 
    virtual string getStateID() const {return s_transitionID;}
    virtual ~TransitionState() {}
};

#endif // define __TransitionState__