#include "TitleScene.h"
#include "Include/Render/RenderManager.h"
#include "Include/Render/ContextGuard.h"
#include "Include/Render/RenderClearCommand.h"
#include "Include/Render/SpriteRenderCommand.h"
#include "Include/Common/Math.h"
#include "Include/Resource/ResourceManager.h"

#include "Include/Input/GLInput.h"

TitleScene::TitleScene(GameSceneData& sceneData) 
    : SceneBase(sceneData) {
    input_ = sceneData.input_;
}

TitleScene::~TitleScene() {
}

void TitleScene::Initialize() {
    //描画用スプライト
    auto pack = ResourceManagerInstance.GetPack("Title");
    sprite_ = pack->Get<Sprite>()->Get("Title");
}

void TitleScene::Update() {
    
    if (input_->IsPush("test_1")) {
        std::cout << "Push\n";
        SceneManagerInstance.ChangeScene(SceneName::Game);
    }

}

void TitleScene::Render(sip::RenderCommandTaskPtr& render_task) {
    render_task->Push(sip::RenderClearCommand::Create(0, 0, 1, 1, 0, 0), 0);
    render_task->Push(sip::SpriteRenderCommand::Create(sprite_, sip::Vector3(0.0f, 0.0f, 0.0f)), 0);
}
