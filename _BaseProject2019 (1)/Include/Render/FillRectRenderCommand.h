#pragma once

#include    "IRenderCommand.h"
#include    "../Common/Rectangle.h"

namespace sip {

    /**
    * @brief        �h��Ԃ���`�`��R�}���h
    */
    class FillRectRenderCommand : public IRenderCommand {
    protected:
        /** ��` */
        Rectangle       rect_;
        /** �F */
        unsigned int    color_;
    public:
        /**
        * @brief        �R���X�g���N�^
        */
        FillRectRenderCommand(float l, float t, float r, float b, unsigned int col)
            : rect_(l, t, r, b)
            , color_(col) {
        }

        /**
        * @brief        �R���X�g���N�^
        */
        FillRectRenderCommand(const Rectangle& rec, unsigned int col)
            : rect_(rec)
            , color_(col) {
        }

        /**
         * @brief		�e���̃R�}���h����
         */
        static RenderCommandPtr Create(float l, float t, float r, float b, unsigned int col);
        static RenderCommandPtr Create(const Rectangle& rec, unsigned int col);
    };
}

#ifdef __MOFLIB
#include    "MofFillRectRenderCommand.h"
#endif