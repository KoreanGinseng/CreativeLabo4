#pragma once

#include	"IRenderCommand.h"

namespace sip {

    /**
     * @brief		�`��I���R�}���h
     */
    class RenderEndCommand : public IRenderCommand {
    public:
        /**
         * @brief		�R���X�g���N�^
         */
        RenderEndCommand() {
        }

        /**
         * @brief		�e���̃R�}���h����
         */
        static RenderCommandPtr Create();
    };
}

#ifdef __MOFLIB
#include	"MofRenderEndCommand.h"
#endif