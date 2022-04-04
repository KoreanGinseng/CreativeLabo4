#pragma once
#include "MoveAction.h"
#include <cmath>

class StraightMoveAction : public MoveAction {
private:

    float speedX_;
    float speedY_;
    float rotate_;

public:

    StraightMoveAction() : MoveAction(nullptr), speedX_(0.0f), speedY_(1.0f), rotate_(0) {}
    StraightMoveAction(TransformPtr transform) : MoveAction(transform), speedX_(0.0f), speedY_(1.0f), rotate_(0) {}

    virtual ~StraightMoveAction() {}

    MoveActionPtr SetSpeed(float speed, float rotate) { rotate_ = rotate; speedX_ = std::sinf(rotate_) * speed; speedY_ = std::cosf(rotate_) * speed; return shared_from_this(); }

    virtual void Exec() override;
};

