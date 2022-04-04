#include "GameOverScene.h"
#include "Include/Render/RenderManager.h"
#include "Include/Render/RenderClearCommand.h"
#include "Include/Render/SpriteRenderCommand.h"
#include "Include/Common/Math.h"
#include "Include/Resource/ResourceManager.h"

#include "Include/Input/GLInput.h"

GameOverScene::GameOverScene(GameSceneData& sceneData)
    : SceneBase<GameSceneData>(sceneData) {
    input_ = sceneData.input_;
}

GameOverScene::~GameOverScene() {
}

void GameOverScene::Initialize() {
    //描画用スプライト
    auto pack = ResourceManagerInstance.GetPack("GameOver");
    sprite_ = pack->Get<Sprite>()->Get("GameOver");
}

void GameOverScene::Update() {
    if (input_->IsPress("Enter")) {
        SceneManagerInstance.ChangeScene(SceneName::Title);
    }
}

void GameOverScene::Render(sip::RenderCommandTaskPtr& render_task) {
    render_task->Push(sip::RenderClearCommand::Create(0, 0, 0, 1, 0, 0), 0);
    render_task->Push(sip::SpriteRenderCommand::Create(sprite_, sip::Vector3(0.0f, 0.0f, 0.0f)), 0);
}
