#include "GameScene.h"

GameScene::GameScene(GameSceneData& sceneData)
    : SceneBase(sceneData) {
}

GameScene::~GameScene() {
}

void GameScene::Initialize() {
}

void GameScene::Update() {
    if (sceneData_.input_->IsPush("test_1")) {
        SceneManagerInstance.ChangeScene(SceneName::Title);
    }
}

void GameScene::Render(sip::RenderCommandTaskPtr& render_task) {
    render_task->Push(sip::RenderClearCommand::Create(0, 0, 1, 1, 0, 0), 0);
}
