#pragma once

#include	"State.h"
#include	"../Player.h"

namespace Sample {

	/**
	 * @brief		�U���X�e�[�g
	 */
	class AttackState : public State
	{
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		AttackState()
			: State() {
		}

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start(CPlayer* player) override {
			player->GetAnimationState()->ChangeMotion("Attack");
		}

		/**
		 * @brief		�X�e�[�g���̎��s����
		 */
		void Exec(CPlayer* player) override {
			if (player->GetAnimationState()->IsEndMotion())
			{
				StateMachine()->ChangeState(player, "Idle");
			}
			//�ړ��X�V
			player->UpdateMove();
		}

		/**
		 * @brief		�X�e�[�g���̓��͏���
		 */
		void InputExec(CPlayer* player) override {
		}

		/**
		 * @brief		�X�e�[�g���̏I������
		 */
		void End(CPlayer* player) override {
		}

		/**
		 * @brief		�X�e�[�g���̐ڐG�C�x���g
		 * @param[in]	type		������������̃^�C�v
		 * @param[in]	obj			������������̃I�u�W�F�N�g
		 */
		void CollisionEvent(CPlayer* player, unsigned int type, anytype obj) override {
		}

		/**
		 * @brief		�X�e�[�g�L�[�̎擾
		 */
		const StateKeyType GetKey() const override {
			return "Attack";
		}
	};

}