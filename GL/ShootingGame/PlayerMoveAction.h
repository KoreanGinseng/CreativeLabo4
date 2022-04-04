#pragma once
#include "MoveAction.h"
#include "Include/Input/Input.h"

class PlayerMoveAction : public MoveAction {
private:
    sip::InputPtr input_;

public:
    PlayerMoveAction() : MoveAction(nullptr), input_(nullptr) {}
    PlayerMoveAction(TransformPtr transform) : MoveAction(transform), input_(nullptr) {}
    virtual ~PlayerMoveAction() {}

    MoveActionPtr SetInput(sip::InputPtr input) { input_ = input; return shared_from_this(); }

    virtual void Exec() override;
};

