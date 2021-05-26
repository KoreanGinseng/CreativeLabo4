#pragma once

#include	"../Input/IInput.h"

//プレイヤー前方定義
class CPlayer;

namespace Sample {

	//キー
	using StateKeyType = std::string;

	//前方定義
	class IStateMachine;
	using StateMachineWeakPtr = std::weak_ptr<IStateMachine>;

	/**
	 * @brief		ステートインターフェイス
	 */
	class IState
	{
		//ステートマシンからのみ登録ができる様にfriend指定
		friend class StateMachine;
	protected:
		/**
		 * @brief		ステートマシン登録
		 */
		virtual void SetStateMachine(StateMachineWeakPtr machine) = 0;

		/**
		 * @brief		入力登録
		 */
		virtual void SetInput(InputPtr input) = 0;
	public:
		/**
		 * @brief		デストラクタ
		 */
		virtual ~IState() = default;

		/**
		 * @brief		アクション内の開始処理
		 */
		virtual void Start(CPlayer* player) = 0;

		/**
		 * @brief		アクション内の実行処理
		 */
		virtual void Exec(CPlayer* player) = 0;

		/**
		 * @brief		ステート内の入力処理
		 */
		virtual void InputExec(CPlayer* player) = 0;

		/**
		 * @brief		アクション内の終了処理
		 */
		virtual void End(CPlayer* player) = 0;

		/**
		 * @brief		ステート内の接触イベント
		 * @param[in]	type		当たった相手のタイプ
		 * @param[in]	obj			当たった相手のオブジェクト
		 */
		virtual void CollisionEvent(CPlayer* player, unsigned int type, anytype obj) = 0;

		/**
		 * @brief		ステート名の取得
		 */
		virtual const StateKeyType GetKey() const = 0;
	};
	//ポインタ置き換え
	using StatePtr = std::shared_ptr<IState>;

}