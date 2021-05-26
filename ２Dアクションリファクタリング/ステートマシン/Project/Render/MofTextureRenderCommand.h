#pragma once

#include	"TextureRenderCommand.h"

#ifdef __MOFLIB

namespace Sample {

	/**
	 * @brief		テクスチャ描画コマンド
	 */
	class MofTextureRenderCommand : public TextureRenderCommand
	{
	public:
		//TextureRenderCommandのコンストラクタを利用
		using TextureRenderCommand::TextureRenderCommand;

		/**
		 * @brief		実行
		 */
		void Exec() override {
			texture_->Render(posX_, posY_, srcRect_);
		}
	};

	/**
	 * @brief		各環境のコマンド実装
	 */
	inline RenderCommandPtr TextureRenderCommand::Create(float x, float y, const TexturePtr& tex) {
		return std::make_shared< MofTextureRenderCommand >(x, y, tex);
	}

	/**
	 * @brief		各環境のコマンド実装
	 */
	inline RenderCommandPtr TextureRenderCommand::Create(float x, float y, const Rectangle& rec, const TexturePtr& tex) {
		return std::make_shared< MofTextureRenderCommand >(x, y, rec, tex);
	}
}
#endif // __MOFLIB
