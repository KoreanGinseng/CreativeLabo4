#pragma once
#include <cmath>

class Circle {
private:
    float x_;
    float y_;
    float r_;

public:
    Circle();
    Circle(float r);
    Circle(float x, float y, float r);
    ~Circle();

    bool CollisionPoint(float x, float y) const;
    bool CollisionCircle(float x, float y, float r) const;
    bool CollisionCircle(Circle circle) const;

    float x() const { return x_; }
    float y() const { return y_; }
    float r() const { return r_; }

    void x(float v) { x_ = v; }
    void y(float v) { y_ = v; }
    void r(float v) { r_ = v; }
};

