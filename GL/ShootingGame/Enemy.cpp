#include "Enemy.h"
#include "Include/Resource/ResourceManager.h"
#include "Include/Render/SpriteRenderCommand.h"

Enemy::Enemy(int type, MoveActionPtr move)
    : Character(move)
    , type_(type)
    , isEnd_(false) {
}

Enemy::~Enemy() {
}

void Enemy::Initialize() {
    using Sprite = Sample::Sprite;
    auto pack = ResourceManagerInstance.GetPack("Enemies");
    sprite_ = pack->Get<Sprite>()->Get("Enemy" + std::to_string(type_));
    radius_ = sprite_->Texture()->Width() * 0.25f * 0.5f;
}

void Enemy::Start(float x, float y) {
    transform_->SetPosition(x, y - sprite_->Texture()->Height());
}

void Enemy::Update() {
    Character::Move();
}

void Enemy::Render(sip::RenderCommandTaskPtr& render_task) {
    render_task->Push(sip::SpriteRenderCommand::Create(sprite_, sip::Vector3(transform_->GetPositionX(), transform_->GetPositionY(), 0.0f)), 0);
}
