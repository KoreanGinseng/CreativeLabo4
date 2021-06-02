#include	"WinApiInput.h"
#include	<Windows.h>

using namespace sip;

/**
 * @brief		キーボードキーの取得
 * @param[in]	positive		＋方向のキー
 * @param[in]	negative		－方向のキー
 * @return		キー入力の値
 */
float WinApiInput::GetKeyboardKeyState(int positive, int negative) const {
    if (positive >= 0 && (GetKeyState(positive) & 0x80)) { return 1.0f; }
    if (negative >= 0 && (GetKeyState(negative) & 0x80)) { return -1.0f; }
    return 0;
}


/**
 * @brief		マウスキーの取得
 * @param[in]	positive		＋方向のキー
 * @param[in]	negative		－方向のキー
 * @return		キー入力の値
 */
float WinApiInput::GetMouseKeyState(int positive, int negative) const {
    if (positive >= 0 && (GetKeyState(positive) & 0x80)) { return 1.0f; }
    if (negative >= 0 && (GetKeyState(negative) & 0x80)) { return -1.0f; }
    return 0;
}

/**
 * @brief		ジョイパッドキーの取得
 * @param[in]	padNo			パッド番号
 * @param[in]	positive		＋方向のキー
 * @param[in]	negative		－方向のキー
 * @return		キー入力の値
 */
float WinApiInput::GetJoypadKeyState(int padNo, int positive, int negative) const {
    return 0;
}

/**
 * @brief		ジョイパッドスティックの取得
 * @param[in]	padNo			パッド番号
 * @return		キー入力の値
 */
float WinApiInput::GetJoypadStickHorizontal(int padNo) const {
    return 0;
}

/**
 * @brief		ジョイパッドスティックの取得
 * @param[in]	padNo			パッド番号
 * @return		キー入力の値
 */
float WinApiInput::GetJoypadStickVertical(int padNo) const {
    return 0;
}