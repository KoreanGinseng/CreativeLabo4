#include "Bullet.h"
#include "Include/Render/SpriteRenderCommand.h"
#include "Include/Resource/ResourceManager.h"

Bullet::Bullet(int type)
    : Character(nullptr)
    , type_(type)
    , isEnemy_(false)
    , isEnd_(false)
    , move_()
    , targetPositions_() {
}

Bullet::~Bullet() {
}

void Bullet::Initialize() {
    using Sprite = Sample::Sprite;
    auto pack = ResourceManagerInstance.GetPack("Bullet");
    sprite_ = pack->Get<Sprite>()->Get("Bullet8");
    radius_ = sprite_->Texture()->Width() * 0.25f * 0.5f;
}

void Bullet::Fire(float x, float y) {
    transform_->SetPosition(x, y);
}

void Bullet::Update() {
    Character::Move();
}

void Bullet::Render(sip::RenderCommandTaskPtr& render_task) {
    render_task->Push(sip::SpriteRenderCommand::Create(sprite_, sip::Vector3(transform_->GetPositionX(), transform_->GetPositionY(), 0.0f)), 0);
}
