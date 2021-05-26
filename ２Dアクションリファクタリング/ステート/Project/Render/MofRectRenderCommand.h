#pragma once

#include	"RectRenderCommand.h"

#ifdef __MOFLIB
#include	<Mof.h>

namespace Sample {

	/**
	 * @brief		矩形描画コマンド
	 */
	class MofRectRenderCommand : public RectRenderCommand
	{
	public:
		//RectRenderCommandのコンストラクタを利用
		using RectRenderCommand::RectRenderCommand;

		/**
		 * @brief		実行
		 */
		void Exec() override {
			CGraphicsUtilities::RenderRect(rect_, color_);
		}
	};

	/**
	 * @brief		各環境のコマンド実装
	 */
	inline RenderCommandPtr RectRenderCommand::Create(float l, float t, float r, float b, unsigned int col) {
		return std::make_shared< MofRectRenderCommand >(l, t, r, b, col);
	}

	/**
	 * @brief		各環境のコマンド実装
	 */
	inline RenderCommandPtr RectRenderCommand::Create(const Rectangle& rec, unsigned int col) {
		return std::make_shared< MofRectRenderCommand >(rec, col);
	}
}
#endif // __MOFLIB
