#pragma once

#include	"IRenderCommand.h"
#include	"../Common/Rectangle.h"
#include	"../Resource/Texture.h"

namespace Sample {

	/**
	 * @brief		�e�N�X�`���`��R�}���h
	 */
	class TextureRenderCommand : public IRenderCommand
	{
	protected:
		/** X�ʒu */
		float			posX_;
		/** Y�ʒu */
		float			posY_;
		/** ��` */
		Rectangle		srcRect_;
		/** �e�N�X�`�� */
		TexturePtr		texture_;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		TextureRenderCommand(float x, float y, const TexturePtr& tex)
			: posX_(x)
			, posY_(y)
			, srcRect_(0, 0, tex->GetWidth(), tex->GetHeight())
			, texture_(tex) {
		}
		/**
		 * @brief		�R���X�g���N�^
		 */
		TextureRenderCommand(float x, float y, const Rectangle& rec, const TexturePtr& tex) 
			: posX_(x)
			, posY_(y)
			, srcRect_(rec)
			, texture_(tex) {
		}

		/**
		 * @brief		�e���̃R�}���h����
		 */
		static RenderCommandPtr Create(float x, float y, const TexturePtr& tex);
		static RenderCommandPtr Create(float x, float y, const Rectangle& rec, const TexturePtr& tex);
	};

}

#ifdef __MOFLIB
#include	"MofTextureRenderCommand.h"
#endif