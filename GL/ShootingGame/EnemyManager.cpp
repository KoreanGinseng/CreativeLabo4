#include "EnemyManager.h"

EnemyManager::EnemyManager() 
    : enemies_() {
}

EnemyManager::~EnemyManager() {
}

void EnemyManager::Add(const EnemyPtr& enemy) {
    enemies_.push_back(enemy);
}

void EnemyManager::Update() {
    for (auto& enemy : enemies_) {
        enemy->Update();
        bool isHorizoutal = (enemy->Transform()->GetPositionX() + enemy->Sprite()->Texture()->Width()) < 0 ||
            enemy->Transform()->GetPositionX() > FrameWorkManagerInstance.GetWindowWidth();
        bool isVertical = (enemy->Transform()->GetPositionY() + enemy->Sprite()->Texture()->Height()) < 0 ||
            enemy->Transform()->GetPositionY() > FrameWorkManagerInstance.GetWindowHeight();
        if (isHorizoutal || isVertical) {
            enemy->IsEnd(true);
        }
    }
}

void EnemyManager::Refresh() {
    for (auto it = enemies_.begin(); it != enemies_.end();) {
        if ((*it)->IsEnd()) {
            it = enemies_.erase(it);
        }
        else {
            ++it;
        }
    }
}

void EnemyManager::Render(sip::RenderCommandTaskPtr& render_task) {
    for (auto& enemy : enemies_) {
        enemy->Render(render_task);
    }
}
