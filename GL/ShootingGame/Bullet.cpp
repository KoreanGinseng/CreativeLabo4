#include "Bullet.h"
#include "Include/Render/SpriteRenderCommand.h"
#include "Include/Resource/ResourceManager.h"

Bullet::Bullet(int type) 
    : Character()
    , type_(type)
    , isEnemy_(false)
    , isEnd_(false)
    , move_() {
}

Bullet::~Bullet() {
}

void Bullet::Initialize() {
    using Sprite = Sample::Sprite;
    auto pack = ResourceManagerInstance.GetPack("Bullet");
    sprite_ = pack->Get<Sprite>()->Get("Bullet8");
    radius_ = sprite_->Texture()->Width() * 0.25f * 0.5f;
}

void Bullet::Render(sip::RenderCommandTaskPtr& render_task) {
    render_task->Push(sip::SpriteRenderCommand::Create(sprite_, sip::Vector3(posX_, posY_, 0.0f)), 0);
}
