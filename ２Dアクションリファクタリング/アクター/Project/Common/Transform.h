#pragma once

#include	"Common.h"

namespace Sample {

	/**
	 * @brief		姿勢変換クラス
	 */
	class Transform
	{
	protected:
		/** 座標 */
		float				positionX_;
		float				positionY_;

	public:
		/**
		 * @brief		コンストラクタ
		 */
		Transform()
			: positionX_(0)
			, positionY_(0) {
		}

		/**
		 * @brief		座標移動
		 */
		void Move(float x, float y) noexcept {
			positionX_ += x;
			positionY_ += y;
		}

		/**
		 * @brief		座標の設定
		 */
		void SetPosition(float x, float y) noexcept {
			positionX_ = x;
			positionY_ = y;
		}
		/**
		 * @brief		座標の設定
		 */
		void SetPositionX(float x) noexcept {
			positionX_ = x;
		}
		/**
		 * @brief		座標の設定
		 */
		void SetPositionY(float y) noexcept {
			positionY_ = y;
		}

		/**
		 * @brief		座標の取得
		 */
		float GetPositionX() const noexcept {
			return positionX_;
		}
		/**
		 * @brief		座標の取得
		 */
		float GetPositionY() const noexcept {
			return positionY_;
		}
	};
	//ポインタ置き換え
	using TransformPtr = std::shared_ptr<Transform>;

}