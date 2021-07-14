#include "Stage.h"
#include "FrameWorkManager.h"
#include "Include/Render/SpriteRenderCommand.h"
#include "Include/Resource/ResourceManager.h"

Stage::Stage() 
    : stageNo_(0)
    , backGroundSprite_(nullptr)
    , scroll_(0) {
}

Stage::~Stage() {
}

void Stage::Initialize(int stageNo) {
    switch (stageNo) {
    case 0:
    {
      auto pack = ResourceManagerInstance.GetPack("Stage1");
      backGroundSprite_ = pack->Get<Sprite>()->Get("Stage1");
    } break;
    case 1:
        break;
    case 2:
        break;
    default:
        break;
    }
    stageNo_ = stageNo;
}

void Stage::Update() {
    scroll_++;
}

void Stage::Render(sip::RenderCommandTaskPtr& render_task) {
    if (!backGroundSprite_) {
        return;
    }
    const int h = backGroundSprite_->Texture()->Height();
    const int w = backGroundSprite_->Texture()->Width();
    int sch = FrameWorkManagerInstance.GetWindowHeight();
    for (float y = (scroll_ % h) - h; y < sch; y += h) {
        render_task->Push(sip::SpriteRenderCommand::Create(backGroundSprite_, sip::Vector3(0.0f, y, 0.0f)), 0);
    }
}
