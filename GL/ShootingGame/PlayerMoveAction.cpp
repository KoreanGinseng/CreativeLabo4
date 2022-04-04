#include "PlayerMoveAction.h"

void PlayerMoveAction::Exec() {
    float x = 0, y = 0;
    if (auto axis = input_->GetAxis("Horizontal")) {
        x += axis;
    }
    if (auto axis = input_->GetAxis("Vertical")) {
        y += axis;
    }
    Transform()->Move(x, y);
}
