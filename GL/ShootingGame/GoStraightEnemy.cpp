#include "GoStraightEnemy.h"

GoStraightEnemy::GoStraightEnemy(float x, float y)
    : Enemy(1) 
    , speedX_(x)
    , speedY_(y) {
}

GoStraightEnemy::~GoStraightEnemy() {
}

void GoStraightEnemy::Update() {
    posX_ += speedX_;
    posY_ += speedY_;
}
