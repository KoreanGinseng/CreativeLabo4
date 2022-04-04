#pragma once
#include "Character.h"

class Enemy : public Character {
private:

    int  type_;
    bool isEnd_;

public:

    Enemy(int type, MoveActionPtr move);
    virtual ~Enemy();

    virtual void Initialize() override;
    virtual void Start(float x, float y);
    virtual void Update() override;
    virtual void Render(sip::RenderCommandTaskPtr& render_task) override;

    bool IsEnd() const { return isEnd_; }
    void IsEnd(bool b) { isEnd_ = b; }
    int Type() const { return type_; }
    void Type(int type) { type_ = type; }
};

using EnemyPtr   = std::shared_ptr<Enemy>;
using EnemyArray = std::vector<EnemyPtr>;

