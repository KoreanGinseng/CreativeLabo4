#pragma once
#include "Framework/Common/Singleton.h"
#include "Bullet.h"

class BulletManager : public Sample::Singleton<BulletManager> {
    friend class Sample::Singleton<BulletManager>;
private:

    BulletArray bullets_;

public:

    BulletManager();
    ~BulletManager();

    void Add(const BulletPtr& bullet);

    void Update();

    void Refresh();

    void Render(sip::RenderCommandTaskPtr& render_task);

    BulletArray& GetBulletArray() { return bullets_; }

    void Reset() { bullets_.clear(); }
};

#define BulletManagerInstance BulletManager::GetInstance()