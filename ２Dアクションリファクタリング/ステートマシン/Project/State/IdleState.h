#pragma once

#include	"State.h"
#include	"../Player.h"

namespace Sample {

	/**
	 * @brief		待機ステート
	 */
	class IdleState : public State
	{
	public:
		/**
		 * @brief		コンストラクタ
		 */
		IdleState()
			: State() {
		}

		/**
		 * @brief		ステート内の開始処理
		 */
		void Start(CPlayer* player) override {
			player->GetAnimationState()->ChangeMotion("Wait");
		}

		/**
		 * @brief		ステート内の実行処理
		 */
		void Exec(CPlayer* player) override {
			//移動更新
			player->UpdateMove();
		}

		/**
		 * @brief		ステート内の入力処理
		 */
		void InputExec(CPlayer* player) override {
			//キーボードでの移動
			if (input_->IsNegativePress("Horizontal"))
			{
				player->Acceleration(-PLAYER_SPEED, PLAYER_MAXSPEED, true);
				StateMachine()->ChangeState(player, "Move");
			}
			else if (input_->IsPress("Horizontal"))
			{
				player->Acceleration(PLAYER_SPEED, PLAYER_MAXSPEED, false);
				StateMachine()->ChangeState(player, "Move");
			}
			//上キーでジャンプ
			if (input_->IsPress("Jump"))
			{
				StateMachine()->ChangeState(player, "Jump");
			}
			//SPACEキーで攻撃
			if (input_->IsPush("Attack"))
			{
				StateMachine()->ChangeState(player, "Attack");
			}
		}

		/**
		 * @brief		ステート内の終了処理
		 */
		void End(CPlayer* player) override {
		}

		/**
		 * @brief		ステート内の接触イベント
		 * @param[in]	type		当たった相手のタイプ
		 * @param[in]	obj			当たった相手のオブジェクト
		 */
		void CollisionEvent(CPlayer* player, unsigned int type, anytype obj) override {
		}

		/**
		 * @brief		ステートキーの取得
		 */
		const StateKeyType GetKey() const override {
			return "Idle";
		}
	};

}