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
		}

		/**
		 * @brief		�X�e�[�g���̓��͏���
		 */
		void InputExec(CPlayer* player) override {
			//���E�ňړ�
			if (Input()->IsNegativePress("Horizontal"))
			{
				player->GetMoveAction()->Acceleration(-PLAYER_SPEED, PLAYER_MAXSPEED, true);
			}
			else if (Input()->IsPress("Horizontal"))
			{
				player->GetMoveAction()->Acceleration(PLAYER_SPEED, PLAYER_MAXSPEED, false);
			}
			else
			{
				if (!player->GetMoveAction()->IsMove())
				{
					ChangeState(player, "Idle");
				}
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
			return "Move";
		}
	};

}