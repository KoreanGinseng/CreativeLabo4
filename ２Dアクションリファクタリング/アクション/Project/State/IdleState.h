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
		}

		/**
		 * @brief		ステート内の入力処理
		 */
		void InputExec(CPlayer* player) override {
			//キーボードでの移動
			if (Input()->IsNegativePress("Horizontal"))
			{
				player->GetMoveAction()->Acceleration(-PLAYER_SPEED, PLAYER_MAXSPEED, true);
				ChangeState(player, "Move");
			}
			else if (Input()->IsPress("Horizontal"))
			{
				player->GetMoveAction()->Acceleration(PLAYER_SPEED, PLAYER_MAXSPEED, false);
				ChangeState(player, "Move");
			}
			//上キーでジャンプ
			if (Input()->IsPress("Jump"))
			{
				ChangeState(player, "Jump");
			}
			//SPACEキーで攻撃
			if (Input()->IsPush("Attack"))
			{
				ChangeState(player, "Attack");
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