#pragma once

#include	"Input.h"

namespace Sample {

	/**
	 * @brief		入力クラス
	 */
	class WinApiInput : public Input
	{
	protected:
		/**
		 * @brief		キーボードキーの取得
		 * @param[in]	positive		＋方向のキー
		 * @param[in]	negative		−方向のキー
		 * @return		キー入力の値
		 */
		float GetKeyboardKeyState(int positive, int negative) const override;

		/**
		 * @brief		マウスキーの取得
		 * @param[in]	positive		＋方向のキー
		 * @param[in]	negative		−方向のキー
		 * @return		キー入力の値
		 */
		float GetMouseKeyState(int positive, int negative) const override;

		/**
		 * @brief		ジョイパッドキーの取得
		 * @param[in]	padNo			パッド番号
		 * @param[in]	positive		＋方向のキー
		 * @param[in]	negative		−方向のキー
		 * @return		キー入力の値
		 */
		float GetJoypadKeyState(int padNo, int positive, int negative) const override;

		/**
		 * @brief		ジョイパッドスティックの取得
		 * @param[in]	padNo			パッド番号
		 * @return		キー入力の値
		 */
		float GetJoypadStickHorizontal(int padNo) const override;

		/**
		 * @brief		ジョイパッドスティックの取得
		 * @param[in]	padNo			パッド番号
		 * @return		キー入力の値
		 */
		float GetJoypadStickVertical(int padNo) const override;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		WinApiInput()
			: Input()
		{ }
	};

}