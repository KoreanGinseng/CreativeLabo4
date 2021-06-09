#pragma once

#include    "IRenderCommand.h"

namespace sip {

    /**
     * @brief        描画開始コマンド
     */
    class RenderStartCommand : public IRenderCommand {
    public:
        /**
         * @brief        コンストラクタ
         */
        RenderStartCommand() {
        }

        /**
         * @brief        各環境のコマンド実装
         */
        static RenderCommandPtr Create();
    };
}

#if   defined __MOFLIB
#include    "MofRenderStartCommand.h"
#elif defined __GLLIB
#include    "GLRenderStartCommand.h"
#endif