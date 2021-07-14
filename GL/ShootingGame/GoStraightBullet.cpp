#include "GoStraightBullet.h"

GoStraightBullet::GoStraightBullet(float speedX, float speedY)
    : Bullet(0)
    , speedX_(speedX)
    , speedY_(speedY) {
}

GoStraightBullet::~GoStraightBullet() {
}

void GoStraightBullet::Fire(float x, float y) {
    posX_ = x;
    posY_ = y;
}

void GoStraightBullet::Update() {
    posX_ += speedX_;
    posY_ += -speedY_;
}
