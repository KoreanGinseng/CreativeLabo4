#pragma once

#include	"FillRectRenderCommand.h"

#ifdef __MOFLIB
#include	<Mof.h>

namespace sip {

    /**
     * @brief		��`�`��R�}���h
     */
    class MofFillRectRenderCommand : public FillRectRenderCommand {
    public:
        //FillRectRenderCommand�̃R���X�g���N�^�𗘗p
        using FillRectRenderCommand::FillRectRenderCommand;

        /**
         * @brief		���s
         */
        void Exec() override {
            CGraphicsUtilities::RenderFillRect(rect_, color_);
        }
    };

    /**
     * @brief		�e���̃R�}���h����
     */
    inline RenderCommandPtr FillRectRenderCommand::Create(float l, float t, float r, float b, unsigned int col) {
        return std::make_shared< MofFillRectRenderCommand >(l, t, r, b, col);
    }

    /**
     * @brief		�e���̃R�}���h����
     */
    inline RenderCommandPtr FillRectRenderCommand::Create(const Rectangle& rec, unsigned int col) {
        return std::make_shared< MofFillRectRenderCommand >(rec, col);
    }
}
namespace detail {
    using FillRectRenderCommand = sip::MofFillRectRenderCommand;
}
#endif // __MOFLIB
