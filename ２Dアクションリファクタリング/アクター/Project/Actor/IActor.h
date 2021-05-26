#pragma once

#include	"../Animation/IAnimationCreator.h"
#include	"../Action/IAction.h"

namespace Sample {

	/**
	 * @brief		�A�N�^�[�C���^�[�t�F�C�X
	 */
	class IActor
	{
	public:
		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~IActor() = default;

		/**
		 * @brief		�A�N�V�����̒ǉ�
		 * @param[in]	name		�A�N�V������
		 * @param[in]	action		�ǉ�����A�N�V����
		 */
		virtual void AddAction(const ActionPtr& action) = 0;

		/**
		 * @brief		�A�N�V�����̒ǉ�
		 * @param[in]	key			�A�N�V�����L�[
		 * @param[in]	action		�ǉ�����A�N�V����
		 */
		virtual void AddAction(const ActionKeyType& key, const ActionPtr& action) = 0;

		/**
		 * @brief		�A�N�V�����̎擾
		 * @param[in]	key			�A�N�V�����L�[
		 * @return		�A�N�V����
		 */
		virtual ActionPtr GetAction(const ActionKeyType& key) = 0;

		/**
		 * @brief		�A�N�V�����̎擾
		 * @param[in]	key			�A�N�V�����L�[
		 * @return		�A�N�V����
		 */
		template< typename T >
		std::shared_ptr< T > GetAction(const ActionKeyType& key) {
			return std::dynamic_pointer_cast<T>(GetAction(key));
		}

		/**
		 * @brief		���W�ݒ�
		 */
		virtual void SetPosition(float x, float y) = 0;

		/**
		 * @brief		�A�j���[�V����
		 */
		virtual void SetAnimationState(AnimationStatePtr animState) = 0;

		/**
		 * @brief		�p���擾
		 */
		virtual TransformPtr GetTransform() const = 0;

		/**
		 * @brief		���W�擾
		 */
		virtual float GetPositionX() const = 0;

		/**
		 * @brief		���W�擾
		 */
		virtual float GetPositionY() const = 0;

		/**
		 * @brief		�A�j���[�V����
		 */
		virtual AnimationStatePtr GetAnimationState() const = 0;
	};
	//�|�C���^�u������
	using ActorPtr = std::shared_ptr<IActor>;
	using ActorWeakPtr = std::weak_ptr<IActor>;

}