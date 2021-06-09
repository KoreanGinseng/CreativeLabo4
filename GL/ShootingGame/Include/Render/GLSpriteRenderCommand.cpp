#include "GLSpriteRenderCommand.h"

using namespace sip;

void GLSpriteRenderCommand::Exec() {
    if (sprite_ == nullptr) return;
    sprite_->RefreshMatrix();
    sprite_->Render();
}