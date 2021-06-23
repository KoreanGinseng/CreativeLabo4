#include "TitleScene.h"
#include "Include/Render/RenderClearCommand.h"
#include "Include/Render/SpriteRenderCommand.h"
#include "Include/Common/Math.h"

TitleScene::TitleScene(GameSceneData& sceneData) 
    : SceneBase(sceneData) {
}

TitleScene::~TitleScene() {
}

void TitleScene::Initialize() {

    //画像読み込み
    texture_ = std::make_shared<Sample::Texture>("title.png");

    //描画用スプライト生成
    sprite_ = std::make_shared<Sample::Sprite>();
    sprite_->Create(texture_, GraphicsControllerInstance.SpriteShader());
}

void TitleScene::Update() {
}

void TitleScene::Render(sip::RenderCommandTask& render_task) {
    render_task.Push(sip::RenderClearCommand::Create(0, 0, 1, 1, 0, 0), 0);
    render_task.Push(sip::SpriteRenderCommand::Create(sprite_, Vector3(0.0f, 0.0f, 0.0f)), 0);
}
