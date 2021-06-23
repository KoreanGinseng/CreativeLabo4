#include "GLSpriteRenderCommand.h"

using namespace sip;

#ifdef __GLLIB
void GLSpriteRenderCommand::Exec() {
    if (sprite_ == nullptr) return;
    sprite_->Alpha(alpha_);
    sprite_->Position(position_);
    sprite_->RefreshMatrix();
    sprite_->Render();
}

#endif //__GLLIB