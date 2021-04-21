#include	"MofInput.h"

#ifdef __MOFLIB
#include	<Mof.h>

using namespace Sample;

/**
 * @brief		キーボードキーの取得
 * @param[in]	positive		＋方向のキー
 * @param[in]	negative		－方向のキー
 * @return		キー入力の値
 */
float MofInput::GetKeyboardKeyState(int positive, int negative) const {
	if (positive >= 0 && g_pInput->IsKeyHold(positive)) { return 1.0f; }
	if (negative >= 0 && g_pInput->IsKeyHold(negative)) { return -1.0f; }
	return 0;
}


/**
 * @brief		マウスキーの取得
 * @param[in]	positive		＋方向のキー
 * @param[in]	negative		－方向のキー
 * @return		キー入力の値
 */
float MofInput::GetMouseKeyState(int positive, int negative) const {
	if (positive >= 0 && g_pInput->IsMouseKeyHold(positive)) { return 1.0f; }
	if (negative >= 0 && g_pInput->IsMouseKeyHold(negative)) { return -1.0f; }
	return 0;
}

/**
 * @brief		ジョイパッドキーの取得
 * @param[in]	padNo			パッド番号
 * @param[in]	positive		＋方向のキー
 * @param[in]	negative		－方向のキー
 * @return		キー入力の値
 */
float MofInput::GetJoypadKeyState(int padNo, int positive, int negative) const {
	LPGamePad pad = g_pInput->GetGamePad(padNo);
	if (pad == nullptr)
	{
		return 0;
	}
	if (positive >= 0 && pad->IsKeyHold(positive)) { return 1.0f; }
	if (negative >= 0 && pad->IsKeyHold(negative)) { return -1.0f; }
	return 0;
}

/**
 * @brief		ジョイパッドスティックの取得
 * @param[in]	padNo			パッド番号
 * @return		キー入力の値
 */
float MofInput::GetJoypadStickHorizontal(int padNo) const {
	LPGamePad pad = g_pInput->GetGamePad(padNo);
	if (pad == nullptr)
	{
		return 0;
	}
	return pad->GetStickHorizontal();
}

/**
 * @brief		ジョイパッドスティックの取得
 * @param[in]	padNo			パッド番号
 * @return		キー入力の値
 */
float MofInput::GetJoypadStickVertical(int padNo) const {
	LPGamePad pad = g_pInput->GetGamePad(padNo);
	if (pad == nullptr)
	{
		return 0;
	}
	return pad->GetStickVertical();
}

#endif