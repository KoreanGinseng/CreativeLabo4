#pragma once
#include "Bullet.h"
#include "Include/Common/Math.h"

class GoStraightBullet : public Bullet {
private:
    
    float        speedX_;
    float        speedY_;

public:

    GoStraightBullet(float speedX, float speedY);

    virtual ~GoStraightBullet();

    virtual void Fire(float x, float y) override;

    virtual void Update() override;
};

