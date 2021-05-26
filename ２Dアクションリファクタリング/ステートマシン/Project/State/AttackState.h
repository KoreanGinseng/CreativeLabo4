#pragma once

#include	"State.h"
#include	"../Player.h"

namespace Sample {

	/**
	 * @brief		攻撃ステート
	 */
	class AttackState : public State
	{
	public:
		/**
		 * @brief		コンストラクタ
		 */
		AttackState()
			: State() {
		}

		/**
		 * @brief		ステート内の開始処理
		 */
		void Start(CPlayer* player) override {
			player->GetAnimationState()->ChangeMotion("Attack");
		}

		/**
		 * @brief		ステート内の実行処理
		 */
		void Exec(CPlayer* player) override {
			if (player->GetAnimationState()->IsEndMotion())
			{
				StateMachine()->ChangeState(player, "Idle");
			}
			//移動更新
			player->UpdateMove();
		}

		/**
		 * @brief		ステート内の入力処理
		 */
		void InputExec(CPlayer* player) override {
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
			return "Attack";
		}
	};

}