#pragma once

#include	"RenderEndCommand.h"

#ifdef __MOFLIB
#include	<Mof.h>

namespace sip {

    /**
     * @brief		描画終了コマンド
     */
    class MofRenderEndCommand : public RenderEndCommand {
    public:
        //RenderEndCommandのコンストラクタを利用
        using RenderEndCommand::RenderEndCommand;

        /**
         * @brief		実行
         */
        void Exec() override {
            g_pGraphics->RenderEnd();
        }
    };

    /**
     * @brief		各環境のコマンド実装
     */
    inline RenderCommandPtr RenderEndCommand::Create() {
        return std::make_shared< MofRenderEndCommand >();
    }
}
#endif // __MOFLIB
