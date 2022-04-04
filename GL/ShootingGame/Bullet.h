#pragma once
#include "Character.h"
#include "Include/Common/Math.h"

class Bullet : public Character {
protected:

    int  type_;
    bool isEnemy_;
    bool isEnd_;

    sip::Vector3              move_;
    std::vector<sip::Vector3> targetPositions_;

public:

    Bullet(int type);
    virtual ~Bullet();


    virtual void Initialize() override;

    virtual void Fire(float x, float y);

    virtual void Update() override;

    virtual void Render(sip::RenderCommandTaskPtr& render_task) override;

    int Type() const { return type_; }
    void Type(int type) { type_ = type; }
    bool IsEnemy() const { return isEnemy_; }
    void IsEnemy(bool b) { isEnemy_ = b; sprite_->XFlip(b); }
    bool IsEnd() const { return isEnd_; }
    void IsEnd(bool b) { isEnd_ = b; }
    const sip::Vector3& Move() { return move_; }
    const std::vector<sip::Vector3>& TargetPositions() const { return targetPositions_; }
    std::vector<sip::Vector3>* TargetPositionsPointer() { return &targetPositions_; }
};

using BulletPtr   = std::shared_ptr<Bullet>;
using BulletArray = std::vector<BulletPtr>;

