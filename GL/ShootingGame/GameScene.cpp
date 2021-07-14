#include "GameScene.h"
#include "Player.h"
#include "Include/Input/InputManager.h"

GameScene::GameScene(GameSceneData& sceneData)
    : SceneBase(sceneData) {
}

GameScene::~GameScene() {
}

void GameScene::Initialize() {
    stage_.Initialize(0);
    auto player = std::make_shared<Player>();
    player->SetInput(InputManagerInstance.GetInput(1));
    objects_.push_back(std::move(player));

    for (auto& it : objects_) {
        it->Initialize();
    }
}

void GameScene::Update() {
    if (sceneData_.input_->IsPush("test_1")) {
        std::cout << "Push2\n";
        SceneManagerInstance.ChangeScene(SceneName::Title);
    }
    stage_.Update();
    for (auto& it : objects_) {
        it->Update();
    }
}

void GameScene::Render(sip::RenderCommandTaskPtr& render_task) {
    render_task->Push(sip::RenderClearCommand::Create(0, 0, 1, 1, 0, 0), 0);
    stage_.Render(render_task);

    for (auto& it : objects_) {
        it->Render(render_task);
    }
}
