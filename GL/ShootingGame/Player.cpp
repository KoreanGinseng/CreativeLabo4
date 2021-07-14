#include "Player.h"
#include "Include/Resource/ResourceManager.h"
#include "Include/Render/SpriteRenderCommand.h"
#include "BulletManager.h"
#include "GoStraightBullet.h"

Player::Player() 
    : Character() {
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
    if (auto axis = input_->GetAxis("Horizontal")) {
        posX_ += axis;
    }
    if (auto axis = input_->GetAxis("Vertical")) {
        posY_ += axis;
    }
    if (input_->IsPress("Fire")) {
        auto bullet = std::make_shared<GoStraightBullet>(0.0f, 10.0f);
        bullet->Initialize();
        float bw = bullet->Sprite()->Texture()->Width();
        float pw = sprite_->Texture()->Width();
        bullet->Fire(posX_ + ((pw - bw) * 0.5f), posY_);
        BulletManagerInstance.Add(bullet);
    }
}

void Player::Render(sip::RenderCommandTaskPtr& render_task) {
    render_task->Push(sip::SpriteRenderCommand::Create(sprite_, sip::Vector3(posX_, posY_, 0.0f)), 0);
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
