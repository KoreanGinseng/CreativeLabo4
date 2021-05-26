#pragma once

#include	"../Common/Transform.h"
#include	"../Animation/IAnimationState.h"

namespace Sample {

	//キー
	using ActionKeyType = std::string;

	/**
	 * @brief		アクションインターフェイス
	 */
	class IAction
	{
		//アクターからのみ登録ができる様にfriend指定
		friend class Actor;
	private:
		/**
		 * @brief		姿勢登録
		 */
		virtual void SetTransform(TransformPtr t) = 0;

		/**
		 * @brief		アニメーション登録
		 */
		virtual void SetAnimation(AnimationStatePtr a) = 0;

	public:
		/**
		 * @brief		デストラクタ
		 */
		virtual ~IAction() = default;

		/**
		 * @brief		アクション内の開始処理
		 */
		virtual void Start() = 0;

		/**
		 * @brief		アクション内の実行処理
		 */
		virtual void Exec() = 0;

		/**
		 * @brief		アクション内の終了処理
		 */
		virtual void End() = 0;

		/**
		 * @brief		アクション名の取得
		 */
		virtual const ActionKeyType GetKey() const = 0;
	};
	//ポインタ置き換え
	using ActionPtr = std::shared_ptr<IAction>;

}