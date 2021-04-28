#pragma once

#include	"RenderClearCommand.h"

#ifdef __MOFLIB
#include	<Mof.h>

namespace Sample {

	/**
	 * @brief		描画クリアコマンド
	 */
	class MofRenderClearCommand : public RenderClearCommand
	{
	public:
		//RenderClearCommandのコンストラクタを利用
		using RenderClearCommand::RenderClearCommand;

		/**
		 * @brief		実行
		 */
		void Exec() override {
			g_pGraphics->ClearTarget(R_, G_, B_, A_, D_, S_);
		}
	};

	/**
	 * @brief		各環境のコマンド実装
	 */
	inline RenderCommandPtr RenderClearCommand::Create(float r, float g, float b, float a, float d, float s) {
		return std::make_shared< MofRenderClearCommand >(r, g, b, a, d, s);
	}
}
#endif // __MOFLIB
