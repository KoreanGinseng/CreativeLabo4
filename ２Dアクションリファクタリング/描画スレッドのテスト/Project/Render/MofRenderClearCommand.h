#pragma once

#include	"RenderClearCommand.h"

#ifdef __MOFLIB
#include	<Mof.h>

namespace Sample {

	/**
	 * @brief		�`��N���A�R�}���h
	 */
	class MofRenderClearCommand : public RenderClearCommand
	{
	public:
		//RenderClearCommand�̃R���X�g���N�^�𗘗p
		using RenderClearCommand::RenderClearCommand;

		/**
		 * @brief		���s
		 */
		void Exec() override {
			g_pGraphics->ClearTarget(R_, G_, B_, A_, D_, S_);
		}
	};

	/**
	 * @brief		�e���̃R�}���h����
	 */
	inline RenderCommandPtr RenderClearCommand::Create(float r, float g, float b, float a, float d, float s) {
		return std::make_shared< MofRenderClearCommand >(r, g, b, a, d, s);
	}
}
#endif // __MOFLIB
