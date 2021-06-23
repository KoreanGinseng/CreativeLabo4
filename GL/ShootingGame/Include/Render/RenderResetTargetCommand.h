#pragma once

#include    "IRenderCommand.h"

namespace sip {

    /**
     * @brief        描画終了コマンド
     */
    class RenderResetTargetCommand : public IRenderCommand {
    public:
        /**
         * @brief        コンストラクタ
         */
        RenderResetTargetCommand() {
        }

        /**
         * @brief        各環境のコマンド実装
         */
        static RenderCommandPtr Create();
    };
}

#if   defined __MOFLIB
#elif defined __GLLIB
#include    "GLRenderResetTargetCommand.h"
#endif