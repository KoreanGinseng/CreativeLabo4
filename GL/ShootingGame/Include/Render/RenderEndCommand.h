#pragma once

#include    "IRenderCommand.h"

namespace sip {

    /**
     * @brief        描画終了コマンド
     */
    class RenderEndCommand : public IRenderCommand {
    public:
        /**
         * @brief        コンストラクタ
         */
        RenderEndCommand() {
        }

        /**
         * @brief        各環境のコマンド実装
         */
        static RenderCommandPtr Create();
    };
}

#if   defined __MOFLIB
#include    "MofRenderEndCommand.h"
#elif defined __GLLIB
#include    "GLRenderEndCommand.h"
#endif