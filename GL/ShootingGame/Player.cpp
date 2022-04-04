#include "Player.h"
#include "Include/Resource/ResourceManager.h"
#include "Include/Render/SpriteRenderCommand.h"
#include "BulletManager.h"
#include "StraightMoveAction.h"

Player::Player(MoveActionPtr action)
    : Character(action) {
}

Player::~Player() {
}

void Player::Initialize() {
    using Sprite = Sample::Sprite;
    auto pack = ResourceManagerInstance.GetPack("Player1");
    hp_ = 3;
    sprite_ = pack->Get<Sprite>()->Get("Player1_3");
}

void Player::Update() {
    Move();
    if (input_->IsPress("Fire")) {
        auto bullet = std::make_shared<Bullet>(0.0f);
        bullet->SetMove(std::make_shared<StraightMoveAction>(bullet->Transform())->SetSpeed(10.0f, 3.14f));
        bullet->Initialize();
        float bw = bullet->Sprite()->Texture()->Width();
        float pw = sprite_->Texture()->Width();
        bullet->Fire(transform_->GetPositionX() + ((pw - bw) * 0.5f), transform_->GetPositionY());
        BulletManagerInstance.Add(bullet);
    }
}

void Player::Render(sip::RenderCommandTaskPtr& render_task) {
    render_task->Push(sip::SpriteRenderCommand::Create(sprite_, sip::Vector3(transform_->GetPositionX(), transform_->GetPositionY(), 0.0f)), 0);
}

void Player::Damage(int d) {
    Character::Damage(d);
    if (hp_ > 0) {
        using Sprite = Sample::Sprite;
        auto pack = ResourceManagerInstance.GetPack("Player1");
        std::string str = "Player1_" + std::to_string(hp_);
        sprite_ = pack->Get<Sprite>()->Get(str);
    }
}
