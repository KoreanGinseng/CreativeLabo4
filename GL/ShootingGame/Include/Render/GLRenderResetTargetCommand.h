#pragma once
#include "RenderResetTargetCommand.h"

#ifdef __GLLIB

namespace sip {

    class GLRenderResetTargetCommand : public RenderResetTargetCommand {
    public:
        using RenderResetTargetCommand::RenderResetTargetCommand;
        void Exec() override;
    };

    inline RenderCommandPtr RenderResetTargetCommand::Create() {
        return std::make_shared< GLRenderResetTargetCommand >();
    }
}

#endif //__GLLIB
