#include	"WinApiInput.h"
#include	<Windows.h>

using namespace sip;

/**
 * @brief		�L�[�{�[�h�L�[�̎擾
 * @param[in]	positive		�{�����̃L�[
 * @param[in]	negative		�|�����̃L�[
 * @return		�L�[���͂̒l
 */
float WinApiInput::GetKeyboardKeyState(int positive, int negative) const {
    if (positive >= 0 && (GetKeyState(positive) & 0x80)) { return 1.0f; }
    if (negative >= 0 && (GetKeyState(negative) & 0x80)) { return -1.0f; }
    return 0;
}


/**
 * @brief		�}�E�X�L�[�̎擾
 * @param[in]	positive		�{�����̃L�[
 * @param[in]	negative		�|�����̃L�[
 * @return		�L�[���͂̒l
 */
float WinApiInput::GetMouseKeyState(int positive, int negative) const {
    if (positive >= 0 && (GetKeyState(positive) & 0x80)) { return 1.0f; }
    if (negative >= 0 && (GetKeyState(negative) & 0x80)) { return -1.0f; }
    return 0;
}

/**
 * @brief		�W���C�p�b�h�L�[�̎擾
 * @param[in]	padNo			�p�b�h�ԍ�
 * @param[in]	positive		�{�����̃L�[
 * @param[in]	negative		�|�����̃L�[
 * @return		�L�[���͂̒l
 */
float WinApiInput::GetJoypadKeyState(int padNo, int positive, int negative) const {
    return 0;
}

/**
 * @brief		�W���C�p�b�h�X�e�B�b�N�̎擾
 * @param[in]	padNo			�p�b�h�ԍ�
 * @return		�L�[���͂̒l
 */
float WinApiInput::GetJoypadStickHorizontal(int padNo) const {
    return 0;
}

/**
 * @brief		�W���C�p�b�h�X�e�B�b�N�̎擾
 * @param[in]	padNo			�p�b�h�ԍ�
 * @return		�L�[���͂̒l
 */
float WinApiInput::GetJoypadStickVertical(int padNo) const {
    return 0;
}