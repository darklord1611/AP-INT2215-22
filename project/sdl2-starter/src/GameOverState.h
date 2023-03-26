#ifndef __GameOverState__
#define __GameOverState__

#include "Game.h"

class GameOverState : public MenuState 
{
private:
    virtual void setCallbacks(const vector<Callback> &callbacks);
    // callback functions
    static void s_gameOverToMain();
    static void s_restartPlay();

    static const string s_gameOverID;
    vector<GameObject*> m_gameObjects;
public:
    virtual void update(); 
    virtual void render(); 
    virtual bool onEnter(); 
    virtual bool onExit(); 
    virtual string getStateID() const {return s_gameOverID;}
};

#endif // define __GameOverState__