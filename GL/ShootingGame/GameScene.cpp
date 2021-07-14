#include "GameScene.h"
#include "Player.h"
#include "Include/Input/InputManager.h"
#include "BulletManager.h"
#include "EnemyManager.h"
#include "GoStraightEnemy.h"

GameScene::GameScene(GameSceneData& sceneData)
    : SceneBase(sceneData) {
}

GameScene::~GameScene() {
}

void GameScene::Initialize() {
    stage_.Initialize(0);
    auto player = std::make_shared<Player>();
    player_.SetInput(InputManagerInstance.GetInput(1));
    player_.Initialize();
}

void GameScene::Update() {
    if (sceneData_.input_->IsPush("test_1")) {
        std::cout << "Push2\n";
        SceneManagerInstance.ChangeScene(SceneName::Title);
    }
    stage_.Update();
    player_.Update();

    if (stage_.Scroll() % 120 == 0) {
        auto enemy = std::make_shared<GoStraightEnemy>(0.0f, 1.0f);
        enemy->Initialize();
        enemy->Start(100.0f, 0.0f);
        EnemyManagerInstance.Add(enemy);
    }

    EnemyManagerInstance.Update();

    BulletManagerInstance.Update();

    auto& enemies = EnemyManagerInstance.GetEnemyArray();
    auto& bullets = BulletManagerInstance.GetBulletArray();

    for (auto& enemy : enemies) {
        for (auto& bullet : bullets) {
            if (enemy->GetCircle().CollisionCircle(bullet->GetCircle())) {
                if (bullet->IsEnd()) {
                    continue;
                }
                enemy->Damage(1);
                if (enemy->HP() <= 0) {
                    enemy->IsEnd(true);
                }
                bullet->IsEnd(true);
            }
        }
    }

    EnemyManagerInstance.Refresh();

    BulletManagerInstance.Refresh();
}

void GameScene::Render(sip::RenderCommandTaskPtr& render_task) {
    render_task->Push(sip::RenderClearCommand::Create(0, 0, 1, 1, 0, 0), 0);
    stage_.Render(render_task);

    EnemyManagerInstance.Render(render_task);

    player_.Render(render_task);

    BulletManagerInstance.Render(render_task);
}
