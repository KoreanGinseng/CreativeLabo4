#pragma once
#include "RenderClearCommand.h"

#ifdef __GLLIB

namespace sip {

    class GLRenderClearCommand : public RenderClearCommand {
    public:
        using RenderClearCommand::RenderClearCommand;
        void Exec() override;
    };

    /**
     * @brief        各環境のコマンド実装
     */
    inline RenderCommandPtr RenderClearCommand::Create(float r, float g, float b, float a, float d, float s) {
        return std::make_shared< GLRenderClearCommand >(r, g, b, a, d, s);
    }
}

#endif //__GLLIB