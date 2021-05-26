#pragma once

#include	"IRenderCommand.h"

namespace sip {

    /**
     * @brief		�`��N���A�R�}���h
     */
    class RenderClearCommand : public IRenderCommand {
    protected:
        /** �F */
        float		R_;
        float		G_;
        float		B_;
        float		A_;

        /** �[�x */
        float		D_;

        /** �X�e���V�� */
        float		S_;
    public:
        /**
         * @brief		�R���X�g���N�^
         * @param[in]	r			��
         * @param[in]	g			��
         * @param[in]	b			��
         * @param[in]	a			�A���t�@
         * @param[in]	d			�[�x
         * @param[in]	s			�X�e���V��
         */
        RenderClearCommand(float r, float g, float b, float a, float d, float s)
            : R_(r)
            , G_(g)
            , B_(b)
            , A_(a)
            , D_(d)
            , S_(s) {
        }

        /**
         * @brief		�e���̃R�}���h����
         */
        static RenderCommandPtr Create(float r, float g, float b, float a, float d, float s);
    };
}

#ifdef __MOFLIB
#include	"MofRenderClearCommand.h"
#endif