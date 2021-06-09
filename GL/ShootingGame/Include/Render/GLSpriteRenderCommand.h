#pragma once
#include "SpriteRenderCommand.h"

#ifdef __GLLIB
namespace sip {

    class GLSpriteRenderCommand : public SpriteRenderCommand {
    public:
        using SpriteRenderCommand::SpriteRenderCommand;
        void Exec() override;
    };

    inline RenderCommandPtr SpriteRenderCommand::Create(SpritePtr sprite) {
        return std::make_shared< GLSpriteRenderCommand >(sprite);
    }
}

#endif //__GLLIB