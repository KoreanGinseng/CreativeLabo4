#pragma once
#include "Character.h"
#include "Include/Common/Math.h"

class Bullet : public Character {
protected:

    int  type_;
    bool isEnemy_;
    bool isEnd_;

    sip::Vector3 move_;

public:

    Bullet(int type);
    virtual ~Bullet();

    virtual void Initialize() override;

    virtual void Fire(float x, float y) = 0;

    virtual void Render(sip::RenderCommandTaskPtr& render_task) override;

    int Type() const { return type_; }
    void Type(int type) { type_ = type; }
    bool IsEnemy() const { return isEnemy_; }
    void IsEnemy(bool b) { isEnemy_ = b; if (b) sprite_->XFlip(true); }
    bool IsEnd() const { return isEnd_; }
    void IsEnd(bool b) { isEnd_ = b; }
};

using BulletPtr   = std::shared_ptr<Bullet>;
using BulletArray = std::vector<BulletPtr>;

