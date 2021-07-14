#pragma once
#include "Enemy.h"
class GoStraightEnemy : public Enemy {
private:

    float speedX_;
    float speedY_;

public:

    GoStraightEnemy(float x, float y);
    virtual ~GoStraightEnemy();

    virtual void Update() override;

};

