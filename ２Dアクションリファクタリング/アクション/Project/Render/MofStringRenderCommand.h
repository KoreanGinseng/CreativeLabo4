#pragma once

#include	"StringRenderCommand.h"

#ifdef __MOFLIB
#include	<Mof.h>

namespace Sample {

	/**
	 * @brief		������`��R�}���h
	 */
	class MofStringRenderCommand : public StringRenderCommand
	{
	public:
		//StringRenderCommand�̃R���X�g���N�^�𗘗p
		using StringRenderCommand::StringRenderCommand;

		/**
		 * @brief		���s
		 */
		void Exec() override {
			CGraphicsUtilities::RenderString(posX_, posY_, string_.c_str());
		}
	};

	/**
	 * @brief		�e���̃R�}���h����
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
