#pragma once

#include	"../Actor/IActor.h"
#include	"../Input/IInput.h"

namespace Sample {

	//�L�[
	using StateKeyType = std::string;

	//�O����`
	class IStateMachine;
	using StateMachineWeakPtr = std::weak_ptr<IStateMachine>;

	/**
	 * @brief		�X�e�[�g�C���^�[�t�F�C�X
	 */
	class IState
	{
		//�X�e�[�g�}�V������̂ݓo�^���ł���l��friend�w��
		friend class StateMachine;
	protected:
		/**
		 * @brief		�A�N�^�[�o�^
		 */
		virtual void SetActor(ActorPtr actor) = 0;

		/**
		 * @brief		�X�e�[�g�}�V���o�^
		 */
		virtual void SetStateMachine(StateMachineWeakPtr machine) = 0;

		/**
		 * @brief		���͓o�^
		 */
		virtual void SetInput(InputPtr input) = 0;
	public:
		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~IState() = default;

		/**
		 * @brief		�A�N�V�������̊J�n����
		 */
		virtual void Start() = 0;

		/**
		 * @brief		�A�N�V�������̎��s����
		 */
		virtual void Exec() = 0;

		/**
		 * @brief		�X�e�[�g���̓��͏���
		 */
		virtual void InputExec() = 0;

		/**
		 * @brief		�A�N�V�������̏I������
		 */
		virtual void End() = 0;

		/**
		 * @brief		�X�e�[�g���̐ڐG�C�x���g
		 * @param[in]	type		������������̃^�C�v
		 * @param[in]	obj			������������̃I�u�W�F�N�g
		 */
		virtual void CollisionEvent(unsigned int type, anytype obj) = 0;

		/**
		 * @brief		�X�e�[�g�̕ύX
		 * @param[in]	key			�X�e�[�g�L�[
		 * @return		true		����
		 *				false		���s
		 */
		virtual bool ChangeState(const StateKeyType& key) = 0;

		/**
		 * @brief		�X�e�[�g���̎擾
		 */
		virtual const StateKeyType GetKey() const = 0;
	};
	//�|�C���^�u������
	using StatePtr = std::shared_ptr<IState>;

}