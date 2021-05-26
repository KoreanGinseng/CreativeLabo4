#pragma once

#include	"StateMachine.h"

namespace Sample {

	/**
	 * @brief		ステート基底クラス
	 */
	class State : public IState
	{
	private:
		/** 所属ステートマシン */
		StateMachineWeakPtr			stateMachine_;

		/** 入力クラス */
		InputPtr					input_;

		/**
		 * @brief		ステートマシン登録
		 */
		void SetStateMachine(StateMachineWeakPtr machine) final { stateMachine_ = machine; }

		/**
		 * @brief		入力登録
		 */
		void SetInput(InputPtr input) final { input_ = input; }
	protected:
		/**
		 * @brief		コンストラクタ
		 */
		State()
			: stateMachine_()
			, input_() {
		}

		/** privateメンバ取得専用 */
		InputPtr Input() { return input_; }

		/**
		 * @brief		ステートの変更
		 * @param[in]	key			ステートキー
		 * @return		true		成功
		 *				false		失敗
		 */
		bool ChangeState(CPlayer* player, const StateKeyType& key) override {
			return stateMachine_.lock()->ChangeState(player, key);
		}

	public:
		/**
		 * @brief		新規ステートの生成
		 * @return		生成したステート
		 */
		template < typename T >
		static std::shared_ptr< T > Create(InputPtr input) {
			if (!std::is_base_of<State, T >::value)
			{
				return std::shared_ptr<T>();
			}
			auto ptr = std::make_shared<T>();
			ptr->SetInput(input);
			return ptr;
		}
	};

}