#pragma once
#include "RenderFrameBufferBindCommand.h"

#ifdef __GLLIB
namespace sip {

    class GLRenderFrameBufferBindCommand : public RenderFrameBufferBindCommand {
    public:
        using RenderFrameBufferBindCommand::RenderFrameBufferBindCommand;
        void Exec() override;
    };

    inline RenderCommandPtr RenderFrameBufferBindCommand::Create(FrameBufferPtr buffer) {
        return std::make_shared< GLRenderFrameBufferBindCommand >(buffer);
    }
}

#endif //__GLLIB