#pragma once

#include	"TextureRenderCommand.h"

#ifdef __MOFLIB

namespace Sample {

	/**
	 * @brief		�e�N�X�`���`��R�}���h
	 */
	class MofTextureRenderCommand : public TextureRenderCommand
	{
	public:
		//TextureRenderCommand�̃R���X�g���N�^�𗘗p
		using TextureRenderCommand::TextureRenderCommand;

		/**
		 * @brief		���s
		 */
		void Exec() override {
			texture_->Render(posX_, posY_, srcRect_);
		}
	};

	/**
	 * @brief		�e���̃R�}���h����
	 */
	inline RenderCommandPtr TextureRenderCommand::Create(float x, float y, const TexturePtr& tex) {
		return std::make_shared< MofTextureRenderCommand >(x, y, tex);
	}

	/**
	 * @brief		�e���̃R�}���h����
	 */
	inline RenderCommandPtr TextureRenderCommand::Create(float x, float y, const Rectangle& rec, const TexturePtr& tex) {
		return std::make_shared< MofTextureRenderCommand >(x, y, rec, tex);
	}
}
#endif // __MOFLIB
