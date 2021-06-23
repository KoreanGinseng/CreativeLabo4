#pragma once

#include    "IRenderCommand.h"

namespace sip {

    /**
     * @brief        �`��I���R�}���h
     */
    class RenderResetTargetCommand : public IRenderCommand {
    public:
        /**
         * @brief        �R���X�g���N�^
         */
        RenderResetTargetCommand() {
        }

        /**
         * @brief        �e���̃R�}���h����
         */
        static RenderCommandPtr Create();
    };
}

#if   defined __MOFLIB
#elif defined __GLLIB
#include    "GLRenderResetTargetCommand.h"
#endif