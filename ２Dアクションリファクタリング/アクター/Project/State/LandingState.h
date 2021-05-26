#pragma once

#include	"State.h"
#include	"../Player.h"

namespace Sample {

	/**
	 * @brief		着地ステート
	 */
	class LandingState : public State
	{
	public:
		/**
		 * @brief		コンストラクタ
		 */
		LandingState()
			: State() {
		}

		/**
		 * @brief		ステート内の開始処理
		 */
		void Start() override {
			Actor()->GetAnimationState()->ChangeMotion("JumpEnd");
		}

		/**
		 * @brief		ステート内の実行処理
		 */
		void Exec() override {
			if (Actor()->GetAnimationState()->IsEndMotion())
			{
				ChangeState("Idle");
			}
		}

		/**
		 * @brief		ステート内の入力処理
		 */
		void InputExec() override {
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
			return "Landing";
		}
	};

}