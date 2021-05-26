#pragma once

#include	"StateMachine.h"

namespace Sample {

	/**
	 * @brief		ステート基底クラス
	 */
	class State : public IState
	{
	protected:

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
		/** privateメンバ取得専用 */
		StateMachinePtr StateMachine() { return stateMachine_.lock(); }
		InputPtr Input() { return input_; }
	public:
		/**
		 * @brief		コンストラクタ
		 */
		State()
			: stateMachine_()
			, input_() {
		}

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