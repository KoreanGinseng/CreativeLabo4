#pragma once
#include "IRenderCommand.h"
#include "../Common/Sprite.h"

namespace sip {

    class SpriteRenderCommand : public IRenderCommand {
    protected:

        SpritePtr sprite_;

    public:

        SpriteRenderCommand(SpritePtr sprite)
            : sprite_(sprite) {
        }

        static RenderCommandPtr Create(SpritePtr sprite);
    };
}

#if   defined __MOFLIB
#elif defined __GLLIB
#include "GLSpriteRenderCommand.h"
#endif