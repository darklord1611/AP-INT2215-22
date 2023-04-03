
#ifndef __PlayState__
#define __PlayState__

#include "CollisionManager.h"
#include "GameObject.h"
#include <vector>

class PlayState : public GameState 
{
private:
    static const string s_playID;
    CollisionManager m_collisionManager;
    vector<GameObject*> m_gameObjects;
public:
    virtual void update();
    virtual void render();
    virtual bool onEnter();
    virtual bool onExit();
    virtual string getStateID() const { return s_playID; }
    virtual ~PlayState() {}
};

#endif // define __PlayState__
