#ifndef __CollisionManager__
#define __CollisionManager__

#include <iostream>
#include <vector>
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Collision.h"
#include "BulletHandler.h"

class CollisionManager
{
public:
    void checkPlayerEnemyBulletCollision(Player* pPlayer);
    void checkPlayerEnemyCollision(Player* pPlayer, const std::vector<GameObject*> &objects);
    void checkEnemyPlayerBulletCollision(const std::vector<GameObject*>& objects);
};
