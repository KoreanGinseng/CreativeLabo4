#include "CollisionManager.h"
#include "GameManager.h"

void CollisionManager::CollisionEnemyAndBullet(EnemyArray& enemies, BulletArray& bullets) {
    for (auto& enemy : enemies) {
        for (auto& bullet : bullets) {
            if (bullet->IsEnd()) {
                continue;
            }
            if (!enemy->GetCircle().CollisionCircle(bullet->GetCircle())) {
                continue;
            }
            enemy->Damage(1);
            if (enemy->HP() <= 0) {
                GameManagerInstance.AddEnemyDeadCount();
                enemy->IsEnd(true);
            }
            bullet->IsEnd(true);
        }
    }
}

void CollisionManager::CollisionPlayerAndBullet(Player& player, BulletArray& bullets) {
    for (auto& bullet : bullets) {
        if (bullet->IsEnd()) {
            continue;
        }
        if (!player.GetCircle().CollisionCircle(bullet->GetCircle())) {
            continue;
        }
        player.Damage(1);
        bullet->IsEnd(true);
    }
}

void CollisionManager::CollisionPlayerAndEnemy(Player& player, EnemyArray& enemies) {
    for (auto& enemy : enemies) {
        if (enemy->IsEnd()) {
            continue;
        }
        if (!player.GetCircle().CollisionCircle(enemy->GetCircle())) {
            continue;
        }
        player.Damage(1);
        enemy->Damage(1);
        if (enemy->HP() <= 0) {
            enemy->IsEnd(true);
        }
    }
}
