#pragma once

#include	"StateMachine.h"

namespace Sample {

	/**
	 * @brief		�X�e�[�g���N���X
	 */
	class State : public IState
	{
	protected:

		/** �����X�e�[�g�}�V�� */
		StateMachineWeakPtr			stateMachine_;

		/** ���̓N���X */
		InputPtr					input_;

		/**
		 * @brief		�X�e�[�g�}�V���o�^
		 */
		void SetStateMachine(StateMachineWeakPtr machine) final { stateMachine_ = machine; }

		/**
		 * @brief		���͓o�^
		 */
		void SetInput(InputPtr input) final { input_ = input; }
	protected:
		/** private�����o�擾��p */
		StateMachinePtr StateMachine() { return stateMachine_.lock(); }
		InputPtr Input() { return input_; }
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		State()
			: stateMachine_()
			, input_() {
		}

		/**
		 * @brief		�V�K�X�e�[�g�̐���
		 * @return		���������X�e�[�g
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