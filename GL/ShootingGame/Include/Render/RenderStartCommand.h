#pragma once

#include    "IRenderCommand.h"

namespace sip {

    /**
     * @brief        �`��J�n�R�}���h
     */
    class RenderStartCommand : public IRenderCommand {
    public:
        /**
         * @brief        �R���X�g���N�^
         */
        RenderStartCommand() {
        }

        /**
         * @brief        �e���̃R�}���h����
         */
        static RenderCommandPtr Create();
    };
}

#if   defined __MOFLIB
#include    "MofRenderStartCommand.h"
#elif defined __GLLIB
#include    "GLRenderStartCommand.h"
#endif