
#ifndef __PauseState__
#define __PauseState__

#include "Game.h"

class PauseState : public MenuState
{
private:
    virtual void setCallbacks(const vector<Callback> &callbacks);
    // callback functions
    static void s_pauseToMain();
    static void s_resumePlay();
    
    static const string s_pauseID;
    vector<GameObject*> m_gameObjects;
public:
    virtual void update();
    virtual void render();
    virtual bool onEnter();
    virtual bool onExit();

    virtual string getStateID() const { return s_pauseID; }
};

#endif // define __PauseState__