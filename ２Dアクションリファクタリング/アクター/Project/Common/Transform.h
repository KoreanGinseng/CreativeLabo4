#pragma once

#include	"Common.h"

namespace Sample {

	/**
	 * @brief		�p���ϊ��N���X
	 */
	class Transform
	{
	protected:
		/** ���W */
		float				positionX_;
		float				positionY_;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		Transform()
			: positionX_(0)
			, positionY_(0) {
		}

		/**
		 * @brief		���W�ړ�
		 */
		void Move(float x, float y) noexcept {
			positionX_ += x;
			positionY_ += y;
		}

		/**
		 * @brief		���W�̐ݒ�
		 */
		void SetPosition(float x, float y) noexcept {
			positionX_ = x;
			positionY_ = y;
		}
		/**
		 * @brief		���W�̐ݒ�
		 */
		void SetPositionX(float x) noexcept {
			positionX_ = x;
		}
		/**
		 * @brief		���W�̐ݒ�
		 */
		void SetPositionY(float y) noexcept {
			positionY_ = y;
		}

		/**
		 * @brief		���W�̎擾
		 */
		float GetPositionX() const noexcept {
			return positionX_;
		}
		/**
		 * @brief		���W�̎擾
		 */
		float GetPositionY() const noexcept {
			return positionY_;
		}
	};
	//�|�C���^�u������
	using TransformPtr = std::shared_ptr<Transform>;

}