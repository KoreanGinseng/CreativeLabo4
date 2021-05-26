#pragma once

#include	"State.h"
#include	"../Player.h"

namespace Sample {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class MoveState : public State
	{
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		MoveState()
			: State() {
		}

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start(CPlayer* player) override {
			player->GetAnimationState()->ChangeMotion("Move");
		}

		/**
		 * @brief		�X�e�[�g���̎��s����
		 */
		void Exec(CPlayer* player) override {
			//�ړ��X�V
			player->UpdateMove();
		}

		/**
		 * @brief		�X�e�[�g���̓��͏���
		 */
		void InputExec(CPlayer* player) override {
			//���E�ňړ�
			if (input_->IsNegativePress("Horizontal"))
			{
				player->Acceleration(-PLAYER_SPEED, PLAYER_MAXSPEED, true);
			}
			else if (input_->IsPress("Horizontal"))
			{
				player->Acceleration(PLAYER_SPEED, PLAYER_MAXSPEED, false);
			}
			//��L�[�ŃW�����v
			if (input_->IsPress("Jump"))
			{
				player->ChangeState("Jump");
			}
			//SPACE�L�[�ōU��
			if (input_->IsPush("Attack"))
			{
				player->ChangeState("Attack");
			}
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
			return "Move";
		}
	};

}