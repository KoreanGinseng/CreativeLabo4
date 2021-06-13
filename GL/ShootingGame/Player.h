#pragma once
#include "Character.h"
class Player : public Character {
private:

public:

	Player();

	virtual ~Player() override;

	virtual void Initialize() override;

	virtual void Update() override;

	virtual void Render(sip::RenderCommandTask& render_task) override;

};

