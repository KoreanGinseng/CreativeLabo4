#pragma once

#include	"IAction.h"

namespace Sample {

	/**
	 * @brief		アクション基底クラス
	 */
	class Action : public IAction
	{
	private:
		/** 姿勢クラス */
		TransformPtr					transform_;

		/** アニメーションクラス */
		AnimationStatePtr				animation_;

		/**
		 * @brief		姿勢登録
		 */
		void SetTransform(TransformPtr t) final { transform_ = t; }

		/**
		 * @brief		アニメーション登録
		 */
		void SetAnimation(AnimationStatePtr a) final { animation_ = a; }
	protected:
		/** privateメンバ取得専用 */
		TransformPtr Transform() { return transform_; }
		AnimationStatePtr AnimationState() { return animation_; }
	public:
		/**
		 * @brief		コンストラクタ
		 */
		Action()
			: transform_()
			, animation_() {
		}

		/**
		 * @brief		新規アクションの生成
		 * @return		生成したアクション
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