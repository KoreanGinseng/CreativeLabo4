#pragma once
#include "Character.h"

class Enemy : public Character {
private:

    int  type_;
    bool isEnd_;

public:

    Enemy(int type);
    virtual ~Enemy();

    virtual void Initialize() override;
    virtual void Start(float x, float y);
    virtual void Render(sip::RenderCommandTaskPtr& render_task) override;

    bool IsEnd() const { return isEnd_; }
    void IsEnd(bool b) { isEnd_ = b; }
};

using EnemyPtr   = std::shared_ptr<Enemy>;
using EnemyArray = std::vector<EnemyPtr>;

