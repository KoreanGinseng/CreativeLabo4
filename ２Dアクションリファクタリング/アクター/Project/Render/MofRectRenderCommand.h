#pragma once

#include	"RectRenderCommand.h"

#ifdef __MOFLIB
#include	<Mof.h>

namespace Sample {

	/**
	 * @brief		��`�`��R�}���h
	 */
	class MofRectRenderCommand : public RectRenderCommand
	{
	public:
		//RectRenderCommand�̃R���X�g���N�^�𗘗p
		using RectRenderCommand::RectRenderCommand;

		/**
		 * @brief		���s
		 */
		void Exec() override {
			CGraphicsUtilities::RenderRect(rect_, color_);
		}
	};

	/**
	 * @brief		�e���̃R�}���h����
	 */
	inline RenderCommandPtr RectRenderCommand::Create(float l, float t, float r, float b, unsigned int col) {
		return std::make_shared< MofRectRenderCommand >(l, t, r, b, col);
	}

	/**
	 * @brief		�e���̃R�}���h����
	 */
	inline RenderCommandPtr RectRenderCommand::Create(const Rectangle& rec, unsigned int col) {
		return std::make_shared< MofRectRenderCommand >(rec, col);
	}
}
#endif // __MOFLIB
