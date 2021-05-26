#pragma once

#include	"State.h"
#include	"../Player.h"

namespace Sample {

	/**
	 * @brief		移動ステート
	 */
	class MoveState : public State
	{
	private:
		/** 移動アクション */
		MoveActionPtr			moveAction_;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		MoveState()
			: State() {
		}

		/**
		 * @brief		ステート内の開始処理
		 */
		void Start() override {
			moveAction_ = Actor()->GetAction<MoveAction>("Move");
			Actor()->GetAnimationState()->ChangeMotion("Move");
		}

		/**
		 * @brief		ステート内の実行処理
		 */
		void Exec() override {
		}

		/**
		 * @brief		ステート内の入力処理
		 */
		void InputExec() override {
			//左右で移動
			if (Input()->IsNegativePress("Horizontal"))
			{
				moveAction_->Acceleration(-PLAYER_SPEED, PLAYER_MAXSPEED, true);
			}
			else if (Input()->IsPress("Horizontal"))
			{
				moveAction_->Acceleration(PLAYER_SPEED, PLAYER_MAXSPEED, false);
			}
			else
			{
				if (!moveAction_->IsMove())
				{
					ChangeState("Idle");
				}
			}
			//上キーでジャンプ
			if (Input()->IsPress("Jump"))
			{
				ChangeState("Jump");
			}
			//SPACEキーで攻撃
			if (Input()->IsPush("Attack"))
			{
				ChangeState("Attack");
			}
		}

		/**
		 * @brief		ステート内の終了処理
		 */
		void End() override {
		}

		/**
		 * @brief		ステート内の接触イベント
		 * @param[in]	type		当たった相手のタイプ
		 * @param[in]	obj			当たった相手のオブジェクト
		 */
		void CollisionEvent(unsigned int type, anytype obj) override {
		}

		/**
		 * @brief		ステートキーの取得
		 */
		const StateKeyType GetKey() const override {
			return "Move";
		}
	};

}