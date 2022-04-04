#include "GameScene.h"
#include "Player.h"
#include "Include/Input/InputManager.h"
#include "BulletManager.h"
#include "EnemyManager.h"
#include "PlayerMoveAction.h"
#include "Random.h"
#include "StraightMoveAction.h"
#include "CollisionManager.h"
#include "GameManager.h"

GameScene::GameScene(GameSceneData& sceneData)
    : SceneBase(sceneData)
    , player_(nullptr) {
    GameManagerInstance.Reset();
    EnemyManagerInstance.Reset();
    BulletManagerInstance.Reset();
}

GameScene::~GameScene() {
}

void GameScene::Initialize() {
    stage_.Initialize(0);
    auto playerMove = MoveAction::Create<PlayerMoveAction>(player_.Transform())->SetInput(InputManagerInstance.GetInput(1));
    player_.SetMove(playerMove);
    player_.SetInput(InputManagerInstance.GetInput(1));
    player_.Initialize();
    player_.Transform()->SetPosition(50, 300);
}

void GameScene::Update() {
    if (GameManagerInstance.EnemyDeadCount() >= 10) {
        GameManagerInstance.IsGameClear(true);
    }
    if (player_.HP() <= 0) {
        GameManagerInstance.IsGameOver(true);
    }
    if (GameManagerInstance.IsGameClear()) {
        SceneManagerInstance.ChangeScene(SceneName::GameClear);
    }
    if (GameManagerInstance.IsGameOver()) {
        SceneManagerInstance.ChangeScene(SceneName::GameOver);
    }

    if (sceneData_.input_->IsPush("test_1")) {
        SceneManagerInstance.ChangeScene(SceneName::Title);
    }

    stage_.Update();
    player_.Update();

    if (stage_.Scroll() % 180 == 0) {
        auto enemy = std::make_shared<Enemy>(RandomUtilities::GetInstance().Random(1, 15), nullptr);
        enemy->SetMove(std::make_shared<StraightMoveAction>(enemy->Transform())->SetSpeed(1.0f, 0));
        enemy->Initialize();
        float x = RandomUtilities::GetInstance().Random(3200) * 0.01f;
        enemy->Start(x, 0.0f);
        EnemyManagerInstance.Add(enemy);
    }

    EnemyManagerInstance.Update();

    BulletManagerInstance.Update();

    auto& enemies = EnemyManagerInstance.GetEnemyArray();
    auto& bullets = BulletManagerInstance.GetBulletArray();

    CollisionManagerInstance.CollisionEnemyAndBullet(enemies, bullets);
    CollisionManagerInstance.CollisionPlayerAndBullet(player_, bullets);
    CollisionManagerInstance.CollisionPlayerAndEnemy(player_, enemies);


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
