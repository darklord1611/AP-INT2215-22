
#ifndef __PlayState__
#define __PlayState__

#include "Player.h"
#include "Game.h"
#include "GameState.h"
#include "GameObject.h"

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
    void checkPlayerEnemyBulletCollision(Player* pPlayer);
    void checkPlayerEnemyCollision(Player* pPlayer, const std::vector<GameObject*> &objects);
    void checkEnemyPlayerBulletCollision(const std::vector<GameObject*> &objects);
    bool Collided(SDL_Rect* A, SDL_Rect* B);
    void saveGame();
    string getEnemyType(GameObject* object);
    bool isLevelComplete(const vector<GameObject*> &objects);
    virtual ~PlayState() {}
    void initPlay();
};

#endif // define __PlayState__
