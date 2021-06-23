#pragma once
#include "IRenderCommand.h"
#include "../Common/Sprite.h"
#include "../Common/Math.h"

namespace sip {

    class SpriteRenderCommand : public IRenderCommand {
    protected:

        Vector3   position_;
        float     alpha_;
        SpritePtr sprite_;

    public:

        SpriteRenderCommand(SpritePtr sprite, const Vector3& position)
            : sprite_(sprite)
            , position_(position)
            , alpha_(1.0f) {
        }
        SpriteRenderCommand(SpritePtr sprite, const float& alpha)
            : sprite_(sprite)
            , position_(Vector3(0.0f, 0.0f, 0.0f))
            , alpha_(alpha) {
        }

        static RenderCommandPtr Create(SpritePtr sprite, const Vector3& position);
        static RenderCommandPtr Create(SpritePtr sprite, const float& alpha);
    };
}

#if   defined __MOFLIB
#elif defined __GLLIB
#include "GLSpriteRenderCommand.h"
#endif