#pragma once

#include	"IRenderCommand.h"
#include	"../Common/Rectangle.h"

namespace sip {

    /**
     * @brief		矩形描画コマンド
     */
    class RectRenderCommand : public IRenderCommand {
    protected:
        /** 矩形 */
        Rectangle		rect_;
        /** 色 */
        unsigned int	color_;
    public:
        /**
         * @brief		コンストラクタ
         */
        RectRenderCommand(float l, float t, float r, float b, unsigned int col)
            : rect_(l, t, r, b)
            , color_(col) {
        }

        /**
         * @brief		コンストラクタ
         */
        RectRenderCommand(const Rectangle& rec, unsigned int col)
            : rect_(rec)
            , color_(col) {
        }

        /**
         * @brief		各環境のコマンド実装
         */
        static RenderCommandPtr Create(float l, float t, float r, float b, unsigned int col);
        static RenderCommandPtr Create(const Rectangle& rec, unsigned int col);
    };
}

#ifdef __MOFLIB
#include	"MofRectRenderCommand.h"
#endif