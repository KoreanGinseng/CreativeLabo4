#pragma once

#include	"IRenderCommand.h"

namespace Sample {

	/**
	 * @brief		描画開始コマンド
	 */
	class RenderStartCommand : public IRenderCommand
	{
	public:
		/**
		 * @brief		コンストラクタ
		 */
		RenderStartCommand() {
		}

		/**
		 * @brief		各環境のコマンド実装
		 */
		static RenderCommandPtr Create();
	};
}

#ifdef __MOFLIB
#include	"MofRenderStartCommand.h"
#endif