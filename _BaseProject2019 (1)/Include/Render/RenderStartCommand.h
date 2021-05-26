#pragma once

#include	"IRenderCommand.h"

namespace sip {

    /**
     * @brief		�`��J�n�R�}���h
     */
    class RenderStartCommand : public IRenderCommand {
    public:
        /**
         * @brief		�R���X�g���N�^
         */
        RenderStartCommand() {
        }

        /**
         * @brief		�e���̃R�}���h����
         */
        static RenderCommandPtr Create();
    };
}

#ifdef __MOFLIB
#include	"MofRenderStartCommand.h"
#endif