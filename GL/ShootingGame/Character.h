#pragma once
#include "GameObject.h"
#include "Include/Common/Sprite.h"

class Character : public GameObject {
protected:

	int hp_;

	SpritePtr sprite_;

public:

	Character()
		: GameObject()
		, hp_(1)
		, sprite_() {
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

	int HP() const { return hp_; }

	virtual Circle GetCircle() const noexcept override { return Circle(posX_ + sprite_->Texture()->Width() * 0.5f, posY_ + sprite_->Texture()->Height() * 0.5f, radius_); }

};

