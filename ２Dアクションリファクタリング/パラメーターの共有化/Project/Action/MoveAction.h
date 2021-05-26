#pragma once

#include	"Action.h"
#include	"../PlayerDefine.h"

namespace Sample {

	/**
	 * @brief		移動アクション
	 */
	class MoveAction : public Action
	{
	private:
		/** 移動フラグ */
		bool			move_;

		/** X移動量 */
		float			moveX_;
		/** Y移動量 */
		float			moveY_;

		/** 反転フラグ */
		bool			reverse_;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		MoveAction()
			: Action() 
			, move_(false)
			, moveX_(0)
			, moveY_(0)
			, reverse_(false) {
		}

		/**
		 * @brief		アクション内の開始処理
		 */
		void Start() override {
		}

		/**
		 * @brief		アクション内の実行処理
		 */
		void Exec() override {
			//移動がない場合減速
			if (!move_)
			{
				Decelerate(PLAYER_SPEED);
			}
			//重力
			Gravity(GRAVITY);
			//実際に座標を移動させる
			Transform()->Move(moveX_, moveY_);
			//移動フラグOFF
			move_ = false;
		}

		/**
		 * @brief		アクション内の終了処理
		 */
		void End() override {
		}

		/**
		 * @brief		速度リセット
		 */
		void Reset() {
			move_ = false;
			moveX_ = 0;
			moveY_ = 0;
			reverse_ = false;
		}

		/**
		 * @brief		重力加速
		 * @param[in]	val		加速量
		 */
		void Gravity(float val) {
			moveY_ += val;
			if (moveY_ >= GRAVITYMAX)
			{
				moveY_ = GRAVITYMAX;
			}
		}

		/**
		 * @brief		加速
		 * @param[in]	val		加速量
		 * @param[in]	rev		反転フラグ
		 */
		void Acceleration(float val, float maxspeed, bool rev) {
			move_ = true;
			moveX_ += val;
			moveX_ = ((moveX_ > maxspeed) ? maxspeed : ((moveX_ < -maxspeed) ? -maxspeed : moveX_));
			reverse_ = rev;
		}

		/**
		 * @brief		減速
		 * @param[in]	dec		減速量
		 */
		void Decelerate(float dec) {
			if (moveX_ > 0)
			{
				moveX_ -= dec;
				if (moveX_ <= 0)
				{
					moveX_ = 0;
				}
			}
			else if (moveX_ < 0)
			{
				moveX_ += dec;
				if (moveX_ >= 0)
				{
					moveX_ = 0;
				}
			}
		}

		/**
		 * @brief		速度設定
		 * @param[in]	val		速度
		 * @param[in]	rev		反転フラグ
		 */
		void SetSpeed(float val, bool rev) {
			moveX_ = val;
			reverse_ = rev;
		}

		/**
		 * @brief		速度設定
		 * @param[in]	val		速度
		 */
		void SetSpeedX(float val) {
			moveX_ = val;
		}

		/**
		 * @brief		速度設定
		 * @param[in]	val		速度
		 */
		void SetSpeedY(float val) {
			moveY_ = val;
		}

		/**
		 * @brief		速度取得
		 */
		float GetSpeedX() {
			return moveX_;
		}

		/**
		 * @brief		速度取得
		 */
		float GetSpeedY() {
			return moveY_;
		}

		/**
		 * @brief		反転フラグ
		 */
		bool IsReverse() const {
			return reverse_;
		}

		/**
		 * @brief		移動判断
		 *				横の移動速度が一定以下なら停止とみなす
		 */
		bool IsMove() const {
			return std::abs(moveX_) > 0.01f;
		}

		/**
		 * @brief		ステートキーの取得
		 */
		const ActionKeyType GetKey() const override {
			return "Move";
		}
	};
	//ポインタ置き換え
	using MoveActionPtr = std::shared_ptr<MoveAction>;

}