#pragma once
#include "Framework/Common/Singleton.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Player.h"

class CollisionManager : public Sample::Singleton<CollisionManager> {
    friend class Sample::Singleton<CollisionManager>;
private:
public:
    void CollisionEnemyAndBullet(EnemyArray& enemies, BulletArray& bullets);
    void CollisionPlayerAndBullet(Player& player, BulletArray& bullets);
    void CollisionPlayerAndEnemy(Player& player, EnemyArray& enemies);
};

#define CollisionManagerInstance CollisionManager::GetInstance()