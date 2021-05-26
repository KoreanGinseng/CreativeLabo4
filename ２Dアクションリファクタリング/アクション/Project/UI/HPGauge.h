#pragma once

#include	"IHPGauge.h"

namespace Sample {

	/**
	 * @brief		HP
	 */
	class HPGauge : public IHPGauge<int>
	{
	protected:
		/** HP */
		int					HP_;
		/** 最大HP */
		int					maxHP_;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		HPGauge(int val)
			: HP_(val) 
			, maxHP_(val) {
		}

		/**
		 * @brief		HP設定
		 */
		void Set(const int& v) override {
			if (v <= 0) { HP_ = 0; }
			else if (v >= maxHP_) { HP_ = maxHP_; }
			else { HP_ = v; }
		}

		/**
		 * @brief		HP取得
		 */
		const int Get() const override {
			return HP_;
		}

		/**
		 * @brief		HP割合取得
		 */
		const float GetPercent() const override {
			return static_cast<float>(HP_) / static_cast<float>(maxHP_);
		}

		/**
		 * @brief	通知メソッド
		 */
		void Notify(int val) override {
			Set(val);
		}
	};

}