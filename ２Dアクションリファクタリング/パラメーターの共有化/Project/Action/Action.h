#pragma once

#include	"IAction.h"

namespace Sample {

	/**
	 * @brief		�A�N�V�������N���X
	 */
	class Action : public IAction
	{
	private:
		/** �p���N���X */
		TransformPtr					transform_;

		/** �A�j���[�V�����N���X */
		AnimationStatePtr				animation_;

		/**
		 * @brief		�p���o�^
		 */
		void SetTransform(TransformPtr t) final { transform_ = t; }

		/**
		 * @brief		�A�j���[�V�����o�^
		 */
		void SetAnimation(AnimationStatePtr a) final { animation_ = a; }
	protected:
		/** private�����o�擾��p */
		TransformPtr Transform() { return transform_; }
		AnimationStatePtr AnimationState() { return animation_; }
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		Action()
			: transform_()
			, animation_() {
		}

		/**
		 * @brief		�V�K�A�N�V�����̐���
		 * @return		���������A�N�V����
		 */
		template < typename T >
		static std::shared_ptr< T > Create() {
			if (!std::is_base_of<Action, T >::value)
			{
				return std::shared_ptr<T>();
			}
			auto re = std::make_shared<T>();
			return re;
		}
	};

}