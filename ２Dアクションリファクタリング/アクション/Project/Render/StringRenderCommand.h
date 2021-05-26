#pragma once

#include	"IRenderCommand.h"

namespace Sample {

	/**
	 * @brief		������`��R�}���h
	 */
	class StringRenderCommand : public IRenderCommand
	{
	protected:
		/** X�ʒu */
		float			posX_;
		/** Y�ʒu */
		float			posY_;
		/** ������ */
		std::string		string_;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		StringRenderCommand(float x, float y, const char* text)
			: posX_(x)
			, posY_(y)
			, string_(text) {
		}

		/**
		 * @brief		�e���̃R�}���h����
		 */
		static RenderCommandPtr Create(float x, float y, const char* text, ...);
	};
}

#ifdef __MOFLIB
#include	"MofStringRenderCommand.h"
#endif