#pragma once

#include	"RenderStartCommand.h"

#ifdef __MOFLIB
#include	<Mof.h>

namespace Sample {

	/**
	 * @brief		�`��J�n�R�}���h
	 */
	class MofRenderStartCommand : public RenderStartCommand
	{
	public:
		//RenderStartCommand�̃R���X�g���N�^�𗘗p
		using RenderStartCommand::RenderStartCommand;

		/**
		 * @brief		���s
		 */
		void Exec() override {
			g_pGraphics->RenderStart();
		}
	};

	/**
	 * @brief		�e���̃R�}���h����
	 */
	inline RenderCommandPtr RenderStartCommand::Create() {
		return std::make_shared< MofRenderStartCommand >();
	}
}
#endif // __MOFLIB
