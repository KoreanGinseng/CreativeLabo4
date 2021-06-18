#pragma once

#include    "IRenderCommand.h"
#include    "../Common/Rectangle.h"
#include    "../Common/Math.h"

namespace sip {

    /**
     * @brief        矩形描画コマンド
     */
    class RenderFillRectCommand : public IRenderCommand {
    protected:

        sip::Rectangle rect_;

        sip::Vector4   color_;

    public:
        /**
         * @brief        コンストラクタ
         * @param[in]    rect        矩形
         * @param[in]    color       色
         */
        RenderFillRectCommand(const sip::Rectangle& rect, const sip::Vector4& color)
            : rect_(rect)
            , color_(color) {
        }

        /**
         * @brief        各環境のコマンド実装
         */
        static RenderCommandPtr Create(const sip::Rectangle& rect, const sip::Vector4& color);
    };
}

#if   defined __MOFLIB
#include    "MofRenderFillRectCommand.h"
#elif defined __GLLIB
#include    "GLRenderFillRectCommand.h"
#endif
