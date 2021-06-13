#pragma once
#include "GameObject.h"
#include "Include/Common/Sprite.h"

class Character : public GameObject {
protected:

	SpritePtr sprite_;

public:

	Character()
		: GameObject()
		, sprite_() {
	}

	virtual ~Character() override {
		if (sprite_) { sprite_->Release(); }
	}

	const SpritePtr& Sprite() const { return sprite_; }
	void Sprite(const SpritePtr& sprite) { sprite_ = sprite; }

};

