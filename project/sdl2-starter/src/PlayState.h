
#ifndef __PlayState__
#define __PlayState__

#include "GameState.h"

class PlayState : public GameState 
{
private:
    static const string s_playID;
public:
    virtual void update();
    virtual void render();
    virtual bool onEnter();
    virtual bool onExit();
}

#endif // define __PlayState__
