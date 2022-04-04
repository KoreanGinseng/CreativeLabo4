#pragma once
#include "Framework/Common/Singleton.h"
#include "Enemy.h"

class EnemyManager : public Sample::Singleton<EnemyManager> {
    friend class Sample::Singleton<EnemyManager>;
private:

    EnemyArray enemies_;

public:
    
    EnemyManager();

    ~EnemyManager();

    void Add(const EnemyPtr& enemy);

    void Update();

    void Refresh();

    void Render(sip::RenderCommandTaskPtr& render_task);

    EnemyArray& GetEnemyArray() { return enemies_; }

    void Reset() { enemies_.clear(); }

};

#define EnemyManagerInstance EnemyManager::GetInstance()