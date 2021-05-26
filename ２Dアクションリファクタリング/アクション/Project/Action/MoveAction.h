#pragma once

#include	"Action.h"
#include	"../PlayerDefine.h"

namespace Sample {

	/**
	 * @brief		�ړ��A�N�V����
	 */
	class MoveAction : public Action
	{
	private:
		/** �ړ��t���O */
		bool			move_;

		/** X�ړ��� */
		float			moveX_;
		/** Y�ړ��� */
		float			moveY_;

		/** ���]�t���O */
		bool			reverse_;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		MoveAction()
			: Action() 
			, move_(false)
			, moveX_(0)
			, moveY_(0)
			, reverse_(false) {
		}

		/**
		 * @brief		�A�N�V�������̊J�n����
		 */
		void Start() override {
		}

		/**
		 * @brief		�A�N�V�������̎��s����
		 */
		void Exec() override {
			//�ړ����Ȃ��ꍇ����
			if (!move_)
			{
				Decelerate(PLAYER_SPEED);
			}
			//�d��
			Gravity(GRAVITY);
			//���ۂɍ��W���ړ�������
			Transform()->Move(moveX_, moveY_);
			//�ړ��t���OOFF
			move_ = false;
		}

		/**
		 * @brief		�A�N�V�������̏I������
		 */
		void End() override {
		}

		/**
		 * @brief		���x���Z�b�g
		 */
		void Reset() {
			move_ = false;
			moveX_ = 0;
			moveY_ = 0;
			reverse_ = false;
		}

		/**
		 * @brief		�d�͉���
		 * @param[in]	val		������
		 */
		void Gravity(float val) {
			moveY_ += val;
			if (moveY_ >= GRAVITYMAX)
			{
				moveY_ = GRAVITYMAX;
			}
		}

		/**
		 * @brief		����
		 * @param[in]	val		������
		 * @param[in]	rev		���]�t���O
		 */
		void Acceleration(float val, float maxspeed, bool rev) {
			move_ = true;
			moveX_ += val;
			moveX_ = ((moveX_ > maxspeed) ? maxspeed : ((moveX_ < -maxspeed) ? -maxspeed : moveX_));
			reverse_ = rev;
		}

		/**
		 * @brief		����
		 * @param[in]	dec		������
		 */
		void Decelerate(float dec) {
			if (moveX_ > 0)
			{
				moveX_ -= dec;
				if (moveX_ <= 0)
				{
					moveX_ = 0;
				}
			}
			else if (moveX_ < 0)
			{
				moveX_ += dec;
				if (moveX_ >= 0)
				{
					moveX_ = 0;
				}
			}
		}

		/**
		 * @brief		���x�ݒ�
		 * @param[in]	val		���x
		 * @param[in]	rev		���]�t���O
		 */
		void SetSpeed(float val, bool rev) {
			moveX_ = val;
			reverse_ = rev;
		}

		/**
		 * @brief		���x�ݒ�
		 * @param[in]	val		���x
		 */
		void SetSpeedX(float val) {
			moveX_ = val;
		}

		/**
		 * @brief		���x�ݒ�
		 * @param[in]	val		���x
		 */
		void SetSpeedY(float val) {
			moveY_ = val;
		}

		/**
		 * @brief		���x�擾
		 */
		float GetSpeedX() {
			return moveX_;
		}

		/**
		 * @brief		���x�擾
		 */
		float GetSpeedY() {
			return moveY_;
		}

		/**
		 * @brief		���]�t���O
		 */
		bool IsReverse() const {
			return reverse_;
		}

		/**
		 * @brief		�ړ����f
		 *				���̈ړ����x�����ȉ��Ȃ��~�Ƃ݂Ȃ�
		 */
		bool IsMove() const {
			return std::abs(moveX_) > 0.01f;
		}

		/**
		 * @brief		�X�e�[�g�L�[�̎擾
		 */
		const ActionKeyType GetKey() const override {
			return "Move";
		}
	};
	//�|�C���^�u������
	using MoveActionPtr = std::shared_ptr<MoveAction>;

}