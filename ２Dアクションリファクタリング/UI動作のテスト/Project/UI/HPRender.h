#pragma once

#include	"IUIObject.h"
#include	"IHPGauge.h"
#include	"../Render/TextureRenderCommand.h"

namespace Sample {

	/**
	 * @brief		HP
	 */
	class HPRender : public IUIObject
	{
	protected:
		/** HP */
		HPGaugePtr			hp_;

		/** �g */
		TexturePtr			frameTexture_;

		/** �Q�[�W */
		TexturePtr			gaugeTexture_;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		HPRender(const HPGaugePtr& hp)
			: hp_(hp)
			, frameTexture_()
			, gaugeTexture_() {
		}

		/**
		 * @brief		�ǂݍ���
		 */
		bool Load(ResourcePackPtr<UsedResources>& pack) override {
			frameTexture_ = pack->Get<Sample::Texture>()->Get("Frame");
			gaugeTexture_ = pack->Get<Sample::Texture>()->Get("HP");
			return true;
		}

		/**
		 * @brief		�`��
		 */
		void Register(RenderCommandTaskPtr& task) override {
			//HP�ɉ����ċ�`�̕���ω�������
			CRectangle rec(0, 0, 532 * hp_->GetPercent(), 64);
			task->Push(Sample::TextureRenderCommand::Create(248, 20, rec, gaugeTexture_), 1);
			task->Push(Sample::TextureRenderCommand::Create(0, 0, frameTexture_), 1);
		}

		/**
		 * @brief		HP�Q�[�W
		 */
		HPGaugePtr& GetGauge() { return hp_; }

		/**
		 * @brief		���
		 */
		void Release(void) override {
			gaugeTexture_.reset();
			frameTexture_.reset();
			hp_.reset();
		}
	};

}