#include "GameClearScene.h"
#include "Include/Render/RenderManager.h"
#include "Include/Render/RenderClearCommand.h"
#include "Include/Render/SpriteRenderCommand.h"
#include "Include/Common/Math.h"
#include "Include/Resource/ResourceManager.h"

#include "Include/Input/GLInput.h"

GameClearScene::GameClearScene(GameSceneData& sceneData)
    : SceneBase<GameSceneData>(sceneData) {
    input_ = sceneData.input_;
}

GameClearScene::~GameClearScene() {
}

void GameClearScene::Initialize() {
    //描画用スプライト
    auto pack = ResourceManagerInstance.GetPack("GameClear");
    sprite_ = pack->Get<Sprite>()->Get("GameClear");
}

void GameClearScene::Update() {
    if (input_->IsPress("Enter")) {
        SceneManagerInstance.ChangeScene(SceneName::Title);
    }
}

void GameClearScene::Render(sip::RenderCommandTaskPtr& render_task) {
    render_task->Push(sip::RenderClearCommand::Create(1, 1, 1, 1, 0, 0), 0);
    render_task->Push(sip::SpriteRenderCommand::Create(sprite_, sip::Vector3(0.0f, 0.0f, 0.0f)), 0);
}
