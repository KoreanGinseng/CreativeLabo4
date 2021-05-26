#pragma once

#include	"RenderEndCommand.h"

#ifdef __MOFLIB
#include	<Mof.h>

namespace sip {

    /**
     * @brief		�`��I���R�}���h
     */
    class MofRenderEndCommand : public RenderEndCommand {
    public:
        //RenderEndCommand�̃R���X�g���N�^�𗘗p
        using RenderEndCommand::RenderEndCommand;

        /**
         * @brief		���s
         */
        void Exec() override {
            g_pGraphics->RenderEnd();
        }
    };

    /**
     * @brief		�e���̃R�}���h����
     */
    inline RenderCommandPtr RenderEndCommand::Create() {
        return std::make_shared< MofRenderEndCommand >();
    }
}
#endif // __MOFLIB
