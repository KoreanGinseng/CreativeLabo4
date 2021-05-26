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

		/** 枠 */
		TexturePtr			frameTexture_;

		/** ゲージ */
		TexturePtr			gaugeTexture_;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		HPRender(const HPGaugePtr& hp)
			: hp_(hp)
			, frameTexture_()
			, gaugeTexture_() {
		}

		/**
		 * @brief		読み込み
		 */
		bool Load(ResourcePackPtr<UsedResources>& pack) override {
			frameTexture_ = pack->Get<Sample::Texture>()->Get("Frame");
			gaugeTexture_ = pack->Get<Sample::Texture>()->Get("HP");
			return true;
		}

		/**
		 * @brief		描画
		 */
		void Register(RenderCommandTaskPtr& task) override {
			//HPに応じて矩形の幅を変化させる
			CRectangle rec(0, 0, 532 * hp_->GetPercent(), 64);
			task->Push(Sample::TextureRenderCommand::Create(248, 20, rec, gaugeTexture_), 1);
			task->Push(Sample::TextureRenderCommand::Create(0, 0, frameTexture_), 1);
		}

		/**
		 * @brief		HPゲージ
		 */
		HPGaugePtr& GetGauge() { return hp_; }

		/**
		 * @brief		解放
		 */
		void Release(void) override {
			gaugeTexture_.reset();
			frameTexture_.reset();
			hp_.reset();
		}
	};

}