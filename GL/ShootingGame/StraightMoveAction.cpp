#include "StraightMoveAction.h"

void StraightMoveAction::Exec() {
    Transform()->Move(speedX_, speedY_);
}
