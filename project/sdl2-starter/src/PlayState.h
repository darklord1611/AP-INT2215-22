
#ifndef __PlayState__
#define __PlayState__

#include "Game.h"
class Level;

class PlayState : public GameState 
{
private:
    static const string s_playID;
    vector<GameObject*> m_gameObjects;
public:
    virtual void update();
    virtual void render();
    virtual bool onEnter();
    virtual bool onExit();
    virtual string getStateID() const { return s_playID; }
    bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);
    virtual ~PlayState() {}
};

#endif // define __PlayState__
