#pragma once
#include "SpriteRenderCommand.h"

#ifdef __GLLIB
namespace sip {

    class GLSpriteRenderCommand : public SpriteRenderCommand {
    public:
        using SpriteRenderCommand::SpriteRenderCommand;
        void Exec() override;
    };

    inline RenderCommandPtr SpriteRenderCommand::Create(SpritePtr sprite, const Vector3& position) {
        return std::make_shared< GLSpriteRenderCommand >(sprite, position);
    }

    inline RenderCommandPtr SpriteRenderCommand::Create(SpritePtr sprite, const float& alpha) {
        return std::make_shared< GLSpriteRenderCommand >(sprite, alpha);
    }
}

#endif //__GLLIB