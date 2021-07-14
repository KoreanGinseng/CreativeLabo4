#include "Circle.h"

Circle::Circle() 
    : x_(0.0f)
    , y_(0.0f)
    , r_(0.0f) {
}

Circle::Circle(float r)
    : x_(0.0f)
    , y_(0.0f)
    , r_(r) {
}

Circle::Circle(float x, float y, float r) 
    : x_(x)
    , y_(y)
    , r_(r) {
}

Circle::~Circle() {
}

bool Circle::CollisionPoint(float x, float y) const {
    float distanceX = std::fabsf(x_ - x);
    float distanceY = std::fabsf(y_ - y);
    float distance  = std::powf(distanceX, 2) + std::powf(distanceY, 2);
    return distance <= std::powf(r_, 2);
}

bool Circle::CollisionCircle(float x, float y, float r) const {
    float distanceX = std::fabsf(x_ - x);
    float distanceY = std::fabsf(y_ - y);
    float distance  = std::powf(distanceX, 2) + std::powf(distanceY, 2);
    return distance <= std::powf(r_, 2) + std::powf(r, 2);
}

bool Circle::CollisionCircle(Circle circle) const {
    return CollisionCircle(circle.x(), circle.y(), circle.r());
}
