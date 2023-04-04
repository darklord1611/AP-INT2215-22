
#ifndef __PlayState__
#define __PlayState__

#include "Game.h"

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
    bool checkPlayerEnemyBulletCollision(Player* pPlayer);
    bool checkPlayerEnemyCollision(Player* pPlayer, const std::vector<GameObject*> &objects);
    void checkEnemyPlayerBulletCollision(const std::vector<GameObject*> &objects);
    bool RectRect(SDL_Rect* A, SDL_Rect* B);
    virtual ~PlayState() {}
};

#endif // define __PlayState__
