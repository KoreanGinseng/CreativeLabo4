#pragma once

#include	"FillRectRenderCommand.h"

#ifdef __MOFLIB
#include	<Mof.h>

namespace sip {

    /**
     * @brief		矩形描画コマンド
     */
    class MofFillRectRenderCommand : public FillRectRenderCommand {
    public:
        //FillRectRenderCommandのコンストラクタを利用
        using FillRectRenderCommand::FillRectRenderCommand;

        /**
         * @brief		実行
         */
        void Exec() override {
            CGraphicsUtilities::RenderFillRect(rect_, color_);
        }
    };

    /**
     * @brief		各環境のコマンド実装
     */
    inline RenderCommandPtr FillRectRenderCommand::Create(float l, float t, float r, float b, unsigned int col) {
        return std::make_shared< MofFillRectRenderCommand >(l, t, r, b, col);
    }

    /**
     * @brief		各環境のコマンド実装
     */
    inline RenderCommandPtr FillRectRenderCommand::Create(const Rectangle& rec, unsigned int col) {
        return std::make_shared< MofFillRectRenderCommand >(rec, col);
    }
}
namespace detail {
    using FillRectRenderCommand = sip::MofFillRectRenderCommand;
}
#endif // __MOFLIB
