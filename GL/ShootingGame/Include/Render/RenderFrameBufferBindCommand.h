#pragma once

#include    "IRenderCommand.h"
#include    "../Common/FrameBuffer.h"

namespace sip {

    /**
     * @brief        描画FrameBufferBindコマンド
     */
    class RenderFrameBufferBindCommand : public IRenderCommand {
    protected:

        FrameBufferPtr buffer_;

    public:
        /**
         * @brief        コンストラクタ
         */
        RenderFrameBufferBindCommand(FrameBufferPtr buffer)
            : buffer_(buffer) {
        }

        /**
         * @brief        各環境のコマンド実装
         */
        static RenderCommandPtr Create(FrameBufferPtr buffer);
    };
}

#if   defined __MOFLIB
#elif defined __GLLIB
#include    "GLRenderFrameBufferBindCommand.h"
#endif