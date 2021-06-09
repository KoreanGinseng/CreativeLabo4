#pragma once
#include "RenderStartCommand.h"

#ifdef __GLLIB
namespace sip {

    class GLRenderStartCommand : public RenderStartCommand {
    public:
        using RenderStartCommand::RenderStartCommand;
        void Exec() override;
    };

    inline RenderCommandPtr RenderStartCommand::Create() {
        return std::make_shared< GLRenderStartCommand >();
    }
}
#endif //__GLLIB