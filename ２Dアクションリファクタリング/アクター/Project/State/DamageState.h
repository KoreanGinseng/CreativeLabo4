#pragma once

#include	"State.h"
#include	"../Player.h"

namespace Sample {

	/**
	 * @brief		�_���[�W�X�e�[�g
	 */
	class DamageState : public State
	{
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		DamageState()
			: State() {
		}

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start() override {
			Actor()->GetAnimationState()->ChangeMotion("Damage");
		}

		/**
		 * @brief		�X�e�[�g���̎��s����
		 */
		void Exec() override {
			if (Actor()->GetAnimationState()->IsEndMotion())
			{
				ChangeState("Idle");
			}
		}

		/**
		 * @brief		�X�e�[�g���̓��͏���
		 */
		void InputExec() override {
		}

		/**
		 * @brief		�X�e�[�g���̏I������
		 */
		void End() override {
		}

		/**
		 * @brief		�X�e�[�g���̐ڐG�C�x���g
		 * @param[in]	type		������������̃^�C�v
		 * @param[in]	obj			������������̃I�u�W�F�N�g
		 */
		void CollisionEvent(unsigned int type, anytype obj) override {
		}

		/**
		 * @brief		�X�e�[�g�L�[�̎擾
		 */
		const StateKeyType GetKey() const override {
			return "Damage";
		}
	};

}