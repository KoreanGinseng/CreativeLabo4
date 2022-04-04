#pragma once
#include "GameObject.h"
#include "Include/Common/Sprite.h"
#include "MoveAction.h"

class Character : public GameObject {
protected:

	int hp_;

	SpritePtr sprite_;

	MoveActionPtr move_;

public:

	explicit Character(MoveActionPtr action)
		: GameObject()
		, hp_(1)
		, sprite_()
	    , move_(action) {
	}

	virtual ~Character() override {
	}

	const SpritePtr& Sprite() const { return sprite_; }
	void Sprite(const SpritePtr& sprite) { sprite_ = sprite; }

	virtual void Damage(int d) {
		hp_ -= d;
		if (hp_ < 0) {
			hp_ = 0;
		}
	}

	void Move() {
		if (move_) move_->Exec();
	}

	int HP() const { return hp_; }

	void SetMove(MoveActionPtr move) { move_ = move; }

	virtual Circle GetCircle() const noexcept override { return Circle(transform_->GetPositionX() + sprite_->Texture()->Width() * 0.5f, transform_->GetPositionY() + sprite_->Texture()->Height() * 0.5f, radius_); }

};

