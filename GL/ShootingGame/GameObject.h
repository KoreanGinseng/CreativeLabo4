#pragma once
#include "Framework/Common/Common.h"

class __declspec(novtable) GameObject {
protected:

    float posX_;
    
    float posY_;

    float radius_;

public:

    virtual ~GameObject() = default;

    virtual void Initialize() = 0;

    virtual void Update() = 0;
    
    virtual void Render() = 0;

    virtual void PosX(const float x) { posX_ = x; }

    virtual void PosY(const float y) { posY_ = y; }
    
    virtual void Radius(const float r) { radius_ = r; }

    virtual float PosX() const noexcept { return posX_; }

    virtual float PosY() const noexcept { return posY_; }

    virtual float Radius() const noexcept { return radius_; }
};

using GameObjectPtr = std::shared_ptr<GameObject>;