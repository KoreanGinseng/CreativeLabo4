#pragma once

#include	"IState.h"

namespace Sample {

	/**
	 * @brief		ステートマシーンインターフェイス
	 */
	class IStateMachine
	{
	public:
		/**
		 * @brief		デストラクタ
		 */
		virtual ~IStateMachine() = default;

		/**
		 * @brief		ステートの追加
		 * @param[in]	state		追加するステート
		 */
		virtual void AddState(const StatePtr& state) = 0;

		/**
		 * @brief		ステートの追加
		 * @param[in]	key			ステートキー
		 * @param[in]	state		追加するステート
		 */
		virtual void AddState(const StateKeyType& key, const StatePtr& state) = 0;

		/**
		 * @brief		ステートの変更
		 * @param[in]	key			ステートキー
		 * @return		true		成功
		 *				false		失敗
		 */
		virtual bool ChangeState(const StateKeyType& key) = 0;

		/**
		 * @brief		ステート内の入力処理
		 */
		virtual void InputExec() = 0;

		/**
		 * @brief		ステート内の実行処理
		 */
		virtual void Exec() = 0;

		/**
		 * @brief		ステート内の接触イベント
		 * @param[in]	type		当たった相手のタイプ
		 * @param[in]	obj			当たった相手のオブジェクト
		 */
		virtual void CollisionEvent(unsigned int type, anytype obj) = 0;

		/**
		 * @brief		現在のステート取得
		 */
		virtual const StatePtr& GetCurrentState() const = 0;

		/**
		 * @brief		現在のステートが指定された名将のものか判断する
		 * @param[in]	key			ステートキー
		 * @return		true		指定されたステート
		 *				false		違う
		 */
		virtual bool IsState(const StateKeyType& key) const = 0;
	};
	//ポインタ置き換え
	using StateMachinePtr = std::shared_ptr<IStateMachine>;
	using StateMachineWeakPtr = std::weak_ptr<IStateMachine>;

}