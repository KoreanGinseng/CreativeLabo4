#pragma once

#include	"RenderStartCommand.h"

#ifdef __MOFLIB
#include	<Mof.h>

namespace Sample {

	/**
	 * @brief		描画開始コマンド
	 */
	class MofRenderStartCommand : public RenderStartCommand
	{
	public:
		//RenderStartCommandのコンストラクタを利用
		using RenderStartCommand::RenderStartCommand;

		/**
		 * @brief		実行
		 */
		void Exec() override {
			g_pGraphics->RenderStart();
		}
	};

	/**
	 * @brief		各環境のコマンド実装
	 */
	inline RenderCommandPtr RenderStartCommand::Create() {
		return std::make_shared< MofRenderStartCommand >();
	}
}
#endif // __MOFLIB
