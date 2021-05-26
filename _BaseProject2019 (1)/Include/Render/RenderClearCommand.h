#pragma once

#include	"IRenderCommand.h"

namespace sip {

    /**
     * @brief		描画クリアコマンド
     */
    class RenderClearCommand : public IRenderCommand {
    protected:
        /** 色 */
        float		R_;
        float		G_;
        float		B_;
        float		A_;

        /** 深度 */
        float		D_;

        /** ステンシル */
        float		S_;
    public:
        /**
         * @brief		コンストラクタ
         * @param[in]	r			赤
         * @param[in]	g			緑
         * @param[in]	b			青
         * @param[in]	a			アルファ
         * @param[in]	d			深度
         * @param[in]	s			ステンシル
         */
        RenderClearCommand(float r, float g, float b, float a, float d, float s)
            : R_(r)
            , G_(g)
            , B_(b)
            , A_(a)
            , D_(d)
            , S_(s) {
        }

        /**
         * @brief		各環境のコマンド実装
         */
        static RenderCommandPtr Create(float r, float g, float b, float a, float d, float s);
    };
}

#ifdef __MOFLIB
#include	"MofRenderClearCommand.h"
#endif