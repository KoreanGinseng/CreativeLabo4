#pragma once
#include "Framework/Common/Common.h"
#include "Include/Render/RenderManager.h"
#include "Circle.h"
#include "Transform.h"

class __declspec(novtable) GameObject {
protected:

    TransformPtr transform_;

    float radius_;

public:

    GameObject()
        : transform_(Transform::Create())
        , radius_(0.0f) {
    }

    virtual ~GameObject() = default;

    virtual void Initialize() = 0;

    virtual void Update() = 0;
    
    virtual void Render(sip::RenderCommandTaskPtr& render_task) = 0;

    virtual TransformPtr Transform() { return transform_; }
    
    virtual void Radius(const float r) { radius_ = r; }

    virtual float Radius() const noexcept { return radius_; }

    virtual Circle GetCircle() const noexcept { return Circle(transform_->GetPositionX(), transform_->GetPositionY(), radius_); }
};

using GameObjectPtr = std::shared_ptr<GameObject>;