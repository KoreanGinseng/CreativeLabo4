#include "BulletManager.h"
#include "FrameWorkManager.h"

BulletManager::BulletManager() {
}

BulletManager::~BulletManager() {
}

void BulletManager::Add(const BulletPtr& bullet) {
    bullets_.push_back(bullet);
}

void BulletManager::Update() {
    for (auto& bullet : bullets_) {
        bullet->Update();
        bool isHorizoutal = (bullet->PosX() + bullet->Sprite()->Texture()->Width()) < 0 ||
            bullet->PosX() > FrameWorkManagerInstance.GetWindowWidth();
        bool isVertical = (bullet->PosY() + bullet->Sprite()->Texture()->Height()) < 0 ||
            bullet->PosY() > FrameWorkManagerInstance.GetWindowHeight();
        if (isHorizoutal || isVertical) {
            bullet->IsEnd(true);
        }
    }
}

void BulletManager::Refresh() {
    for (auto it = bullets_.begin(); it != bullets_.end();) {
        if ((*it)->IsEnd()) {
            it = bullets_.erase(it);
        }
        else {
            ++it;
        }
    }
}

void BulletManager::Render(sip::RenderCommandTaskPtr& render_task) {
    for (auto& bullet : bullets_) {
        bullet->Render(render_task);
    }
}
