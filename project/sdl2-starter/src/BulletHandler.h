#ifndef __BulletHandler__
#define __BulletHandler__

#include <iostream>
#include <vector>
#include "Bullet.h"
#include "Game.h"

class BulletHandler
{
private:
    BulletHandler();
    ~BulletHandler() {}
    BulletHandler(const BulletHandler&);
    BulletHandler& operator=(const BulletHandler&);
    static BulletHandler* instance;
    // in play bullets
    vector<PlayerBullet*> m_playerBullets;
    vector<EnemyBullet*> m_enemyBullets;
public:
    
    static BulletHandler* Instance()
    {
        if(instance == 0)
        {
            instance = new BulletHandler();
            return instance;
        }
        return instance;
    }
    
    void addPlayerBullet(int x, int y, int width, int height, string textureID, int numFrames, Vector2D heading);
    void addEnemyBullet(int x, int y, int width, int height, string textureID, int numFrames, Vector2D heading);
    
    void updateBullets();
    void drawBullets();
    void clearBullets();
    
    const std::vector<PlayerBullet*> getPlayerBullets() { return m_playerBullets; }
    const std::vector<EnemyBullet*> getEnemyBullets() { return m_enemyBullets; }
};

typedef BulletHandler TheBulletHandler;
#endif