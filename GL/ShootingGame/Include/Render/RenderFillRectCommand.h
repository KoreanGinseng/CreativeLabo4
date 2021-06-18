#pragma once

#include    "IRenderCommand.h"
#include    "../Common/Rectangle.h"
#include    "../Common/Math.h"

namespace sip {

    /**
     * @brief        ��`�`��R�}���h
     */
    class RenderFillRectCommand : public IRenderCommand {
    protected:

        sip::Rectangle rect_;

        sip::Vector4   color_;

    public:
        /**
         * @brief        �R���X�g���N�^
         * @param[in]    rect        ��`
         * @param[in]    color       �F
         */
        RenderFillRectCommand(const sip::Rectangle& rect, const sip::Vector4& color)
            : rect_(rect)
            , color_(color) {
        }

        /**
         * @brief        �e���̃R�}���h����
         */
        static RenderCommandPtr Create(const sip::Rectangle& rect, const sip::Vector4& color);
    };
}

#if   defined __MOFLIB
#include    "MofRenderFillRectCommand.h"
#elif defined __GLLIB
#include    "GLRenderFillRectCommand.h"
#endif
