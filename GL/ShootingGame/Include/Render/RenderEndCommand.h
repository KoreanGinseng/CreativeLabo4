#pragma once

#include    "IRenderCommand.h"

namespace sip {

    /**
     * @brief        �`��I���R�}���h
     */
    class RenderEndCommand : public IRenderCommand {
    public:
        /**
         * @brief        �R���X�g���N�^
         */
        RenderEndCommand() {
        }

        /**
         * @brief        �e���̃R�}���h����
         */
        static RenderCommandPtr Create();
    };
}

#if   defined __MOFLIB
#include    "MofRenderEndCommand.h"
#elif defined __GLLIB
#include    "GLRenderEndCommand.h"
#endif