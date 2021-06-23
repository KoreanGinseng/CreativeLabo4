#pragma once

#include    "IRenderCommand.h"
#include    "../Common/FrameBuffer.h"

namespace sip {

    /**
     * @brief        �`��FrameBufferBind�R�}���h
     */
    class RenderFrameBufferBindCommand : public IRenderCommand {
    protected:

        FrameBufferPtr buffer_;

    public:
        /**
         * @brief        �R���X�g���N�^
         */
        RenderFrameBufferBindCommand(FrameBufferPtr buffer)
            : buffer_(buffer) {
        }

        /**
         * @brief        �e���̃R�}���h����
         */
        static RenderCommandPtr Create(FrameBufferPtr buffer);
    };
}

#if   defined __MOFLIB
#elif defined __GLLIB
#include    "GLRenderFrameBufferBindCommand.h"
#endif