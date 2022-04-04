#pragma once
#include "Character.h"
#include "Include/Input/InputManager.h"

class Player : public Character {
private:

	sip::InputPtr input_;

public:

	explicit Player(MoveActionPtr action);

	virtual ~Player() override;

	virtual void Initialize() override;

	virtual void Update() override;

	virtual void Render(sip::RenderCommandTaskPtr& render_task) override;

	void SetInput(const sip::InputPtr& input) {
		input_ = input;
	}

	virtual void Damage(int d) override;
};

