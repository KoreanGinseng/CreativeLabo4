#pragma once

#include	"IActor.h"

namespace Sample {

	/**
	 * @brief		アクタークラス
	 */
	class Actor : public IActor, public std::enable_shared_from_this<IActor>
	{
	protected:
		/** 姿勢 */
		TransformPtr			transform_;

		/** アクション */
		using ActionMap = std::unordered_map< ActionKeyType, ActionPtr >;
		ActionMap				actionMap_;

		/** パラメーター */
		ParameterMapPtr			parameterMap_;

		/** モーション */
		AnimationStatePtr		motion_;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		Actor() 
			: enable_shared_from_this()
			, transform_(std::make_shared<Transform>())
			, actionMap_()
			, parameterMap_()
			, motion_() {
		}

		/**
		 * @brief		アクションの追加
		 * @param[in]	key			アクションキー
		 * @param[in]	action		追加するアクション
		 */
		void AddAction(const ActionPtr& action) override {
			AddAction(action->GetKey(), action);
		}

		/**
		 * @brief		アクションの追加
		 * @param[in]	key			アクションキー
		 * @param[in]	action		追加するアクション
		 */
		void AddAction(const ActionKeyType& key, const ActionPtr& action) override {
			actionMap_[key] = action;
			action->SetTransform(transform_);
			action->SetAnimation(motion_);
		}

		/**
		 * @brief		座標設定
		 */
		void SetPosition(float x, float y) override {
			transform_->SetPosition(x, y);
		}

		/**
		 * @brief		アニメーション
		 */
		void SetAnimationState(AnimationStatePtr animState) override {
			motion_ = animState;
		}

		/**
		 * @brief		アクションの取得
		 * @param[in]	key			アクションキー
		 * @return		アクション
		 */
		ActionPtr GetAction(const ActionKeyType& key) override {
			auto& act = actionMap_.find(key);
			assert(act != actionMap_.end());
			return act->second;
		}


		/**
		 * @brief		姿勢取得
		 */
		TransformPtr GetTransform() const override {
			return transform_;
		}

		/**
		 * @brief		座標取得
		 */
		float GetPositionX() const override {
			return transform_->GetPositionX();
		}

		/**
		 * @brief		座標取得
		 */
		float GetPositionY() const override {
			return transform_->GetPositionY();
		}

		/**
		 * @brief		パラメーター
		 */
		ParameterMapPtr GetParameterMap() override {
			return parameterMap_;
		}

		/**
		 * @brief		パラメーター
		 */
		const ParameterMapPtr& GetParameterMap() const override {
			return parameterMap_;
		}

		/**
		 * @brief		アニメーション
		 */
		AnimationStatePtr GetAnimationState() const override {
			return motion_;
		}

	protected:
		/**
		 * @brief		パラメーター
		 */
		void SetParameterMap(ParameterMapPtr ptr) override {
			parameterMap_ = ptr;
		}
	};

}