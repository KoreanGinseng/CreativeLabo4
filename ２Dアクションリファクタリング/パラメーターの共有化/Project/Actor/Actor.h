#pragma once

#include	"IActor.h"

namespace Sample {

	/**
	 * @brief		�A�N�^�[�N���X
	 */
	class Actor : public IActor, public std::enable_shared_from_this<IActor>
	{
	protected:
		/** �p�� */
		TransformPtr			transform_;

		/** �A�N�V���� */
		using ActionMap = std::unordered_map< ActionKeyType, ActionPtr >;
		ActionMap				actionMap_;

		/** �p�����[�^�[ */
		ParameterMapPtr			parameterMap_;

		/** ���[�V���� */
		AnimationStatePtr		motion_;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		Actor() 
			: enable_shared_from_this()
			, transform_(std::make_shared<Transform>())
			, actionMap_()
			, parameterMap_()
			, motion_() {
		}

		/**
		 * @brief		�A�N�V�����̒ǉ�
		 * @param[in]	key			�A�N�V�����L�[
		 * @param[in]	action		�ǉ�����A�N�V����
		 */
		void AddAction(const ActionPtr& action) override {
			AddAction(action->GetKey(), action);
		}

		/**
		 * @brief		�A�N�V�����̒ǉ�
		 * @param[in]	key			�A�N�V�����L�[
		 * @param[in]	action		�ǉ�����A�N�V����
		 */
		void AddAction(const ActionKeyType& key, const ActionPtr& action) override {
			actionMap_[key] = action;
			action->SetTransform(transform_);
			action->SetAnimation(motion_);
		}

		/**
		 * @brief		���W�ݒ�
		 */
		void SetPosition(float x, float y) override {
			transform_->SetPosition(x, y);
		}

		/**
		 * @brief		�A�j���[�V����
		 */
		void SetAnimationState(AnimationStatePtr animState) override {
			motion_ = animState;
		}

		/**
		 * @brief		�A�N�V�����̎擾
		 * @param[in]	key			�A�N�V�����L�[
		 * @return		�A�N�V����
		 */
		ActionPtr GetAction(const ActionKeyType& key) override {
			auto& act = actionMap_.find(key);
			assert(act != actionMap_.end());
			return act->second;
		}


		/**
		 * @brief		�p���擾
		 */
		TransformPtr GetTransform() const override {
			return transform_;
		}

		/**
		 * @brief		���W�擾
		 */
		float GetPositionX() const override {
			return transform_->GetPositionX();
		}

		/**
		 * @brief		���W�擾
		 */
		float GetPositionY() const override {
			return transform_->GetPositionY();
		}

		/**
		 * @brief		�p�����[�^�[
		 */
		ParameterMapPtr GetParameterMap() override {
			return parameterMap_;
		}

		/**
		 * @brief		�p�����[�^�[
		 */
		const ParameterMapPtr& GetParameterMap() const override {
			return parameterMap_;
		}

		/**
		 * @brief		�A�j���[�V����
		 */
		AnimationStatePtr GetAnimationState() const override {
			return motion_;
		}

	protected:
		/**
		 * @brief		�p�����[�^�[
		 */
		void SetParameterMap(ParameterMapPtr ptr) override {
			parameterMap_ = ptr;
		}
	};

}