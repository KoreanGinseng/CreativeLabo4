#pragma once
#include <memory>
#include "Include/Common/Math.h"
#include "Transform.h"

class MoveAction : public std::enable_shared_from_this<MoveAction> {
private:
    TransformPtr transform_;

protected:
    TransformPtr Transform() { return transform_; }

public:
    explicit MoveAction(TransformPtr transform) : transform_(transform) {}
    virtual void Exec() = 0;

    template<class T>
    static std::shared_ptr<T> Create(TransformPtr transform) {
        if (!std::is_base_of<MoveAction, T>::value) {
            return std::make_shared<T>();
        }
        auto re = std::make_shared<T>(transform);
        return re;
    }
};

using MoveActionPtr = std::shared_ptr<MoveAction>;