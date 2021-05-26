#pragma once

#include	"IRenderCommand.h"

namespace Sample {

	/**
	 * @brief		文字列描画コマンド
	 */
	class StringRenderCommand : public IRenderCommand
	{
	protected:
		/** X位置 */
		float			posX_;
		/** Y位置 */
		float			posY_;
		/** 文字列 */
		std::string		string_;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		StringRenderCommand(float x, float y, const char* text)
			: posX_(x)
			, posY_(y)
			, string_(text) {
		}

		/**
		 * @brief		各環境のコマンド実装
		 */
		static RenderCommandPtr Create(float x, float y, const char* text, ...);
	};
}

#ifdef __MOFLIB
#include	"MofStringRenderCommand.h"
#endif