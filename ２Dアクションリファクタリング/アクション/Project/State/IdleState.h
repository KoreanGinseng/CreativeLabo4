#pragma once

#include	"State.h"
#include	"../Player.h"

namespace Sample {

	/**
	 * @brief		�ҋ@�X�e�[�g
	 */
	class IdleState : public State
	{
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		IdleState()
			: State() {
		}

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start(CPlayer* player) override {
			player->GetAnimationState()->ChangeMotion("Wait");
		}

		/**
		 * @brief		�X�e�[�g���̎��s����
		 */
		void Exec(CPlayer* player) override {
		}

		/**
		 * @brief		�X�e�[�g���̓��͏���
		 */
		void InputExec(CPlayer* player) override {
			//�L�[�{�[�h�ł̈ړ�
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
			//��L�[�ŃW�����v
			if (Input()->IsPress("Jump"))
			{
				ChangeState(player, "Jump");
			}
			//SPACE�L�[�ōU��
			if (Input()->IsPush("Attack"))
			{
				ChangeState(player, "Attack");
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
			return "Idle";
		}
	};

}