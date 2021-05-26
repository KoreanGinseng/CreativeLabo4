#pragma once

#include	"IRenderCommand.h"
#include	"../Common/Rectangle.h"
#include	"../Resource/Texture.h"

namespace Sample {

	/**
	 * @brief		テクスチャ描画コマンド
	 */
	class TextureRenderCommand : public IRenderCommand
	{
	protected:
		/** X位置 */
		float			posX_;
		/** Y位置 */
		float			posY_;
		/** 矩形 */
		Rectangle		srcRect_;
		/** テクスチャ */
		TexturePtr		texture_;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		TextureRenderCommand(float x, float y, const TexturePtr& tex)
			: posX_(x)
			, posY_(y)
			, srcRect_(0, 0, tex->GetWidth(), tex->GetHeight())
			, texture_(tex) {
		}
		/**
		 * @brief		コンストラクタ
		 */
		TextureRenderCommand(float x, float y, const Rectangle& rec, const TexturePtr& tex) 
			: posX_(x)
			, posY_(y)
			, srcRect_(rec)
			, texture_(tex) {
		}

		/**
		 * @brief		各環境のコマンド実装
		 */
		static RenderCommandPtr Create(float x, float y, const TexturePtr& tex);
		static RenderCommandPtr Create(float x, float y, const Rectangle& rec, const TexturePtr& tex);
	};

}

#ifdef __MOFLIB
#include	"MofTextureRenderCommand.h"
#endif