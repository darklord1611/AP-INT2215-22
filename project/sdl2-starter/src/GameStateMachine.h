#ifndef __GameStateMachine__
#define __GameStateMachine__

#include "GameState.h"
#include<vector>

class GameStateMachine 
{
private:
    vector<GameState*> m_gameStates;
public:
    void pushState(GameState* pState);
    void changeState(GameState* pState);
    void popState();
    void update();
    void render();
    // void clean();
};

#endif // define __GameStateMachine__