#pragma once

#include	"../Animation/IAnimationCreator.h"
#include	"../Action/IAction.h"

namespace Sample {

	/**
	 * @brief		アクターインターフェイス
	 */
	class IActor
	{
	public:
		/**
		 * @brief		デストラクタ
		 */
		virtual ~IActor() = default;

		/**
		 * @brief		アクションの追加
		 * @param[in]	name		アクション名
		 * @param[in]	action		追加するアクション
		 */
		virtual void AddAction(const ActionPtr& action) = 0;

		/**
		 * @brief		アクションの追加
		 * @param[in]	key			アクションキー
		 * @param[in]	action		追加するアクション
		 */
		virtual void AddAction(const ActionKeyType& key, const ActionPtr& action) = 0;

		/**
		 * @brief		アクションの取得
		 * @param[in]	key			アクションキー
		 * @return		アクション
		 */
		virtual ActionPtr GetAction(const ActionKeyType& key) = 0;

		/**
		 * @brief		アクションの取得
		 * @param[in]	key			アクションキー
		 * @return		アクション
		 */
		template< typename T >
		std::shared_ptr< T > GetAction(const ActionKeyType& key) {
			return std::dynamic_pointer_cast<T>(GetAction(key));
		}

		/**
		 * @brief		座標設定
		 */
		virtual void SetPosition(float x, float y) = 0;

		/**
		 * @brief		アニメーション
		 */
		virtual void SetAnimationState(AnimationStatePtr animState) = 0;

		/**
		 * @brief		姿勢取得
		 */
		virtual TransformPtr GetTransform() const = 0;

		/**
		 * @brief		座標取得
		 */
		virtual float GetPositionX() const = 0;

		/**
		 * @brief		座標取得
		 */
		virtual float GetPositionY() const = 0;

		/**
		 * @brief		アニメーション
		 */
		virtual AnimationStatePtr GetAnimationState() const = 0;
	};
	//ポインタ置き換え
	using ActorPtr = std::shared_ptr<IActor>;
	using ActorWeakPtr = std::weak_ptr<IActor>;

}