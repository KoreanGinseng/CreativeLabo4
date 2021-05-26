#pragma once

#include	"StringRenderCommand.h"

#ifdef __MOFLIB
#include	<Mof.h>

namespace Sample {

	/**
	 * @brief		文字列描画コマンド
	 */
	class MofStringRenderCommand : public StringRenderCommand
	{
	public:
		//StringRenderCommandのコンストラクタを利用
		using StringRenderCommand::StringRenderCommand;

		/**
		 * @brief		実行
		 */
		void Exec() override {
			CGraphicsUtilities::RenderString(posX_, posY_, string_.c_str());
		}
	};

	/**
	 * @brief		各環境のコマンド実装
	 */
	inline RenderCommandPtr StringRenderCommand::Create(float x, float y, const char* text, ...) {
		static char temp[1024];
		va_list arg;
		va_start(arg, text);
		vsprintf(temp, text, arg);
		va_end(arg);
		return std::make_shared< MofStringRenderCommand >(x, y, temp);
	}
}
#endif // __MOFLIB
