#include "GLInput.h"

#ifdef __GLLIB

using namespace sip;

float GLInput::GetKeyboardKeyState(int positive, int negative) const {
    if (positive >= 0 && input_->GetKeyState(positive)) { return 1.0f; }
    if (negative >= 0 && input_->GetKeyState(negative)) { return -1.0f; }
    return 0.0f;
}

float GLInput::GetMouseKeyState(int positive, int negative) const {
    if (positive >= 0 && input_->GetMouseState(positive)) { return 1.0f; }
    if (negative >= 0 && input_->GetMouseState(negative)) { return -1.0f; }
    return 0.0f;
}

float GLInput::GetJoypadKeyState(int padNo, int positive, int negative) const {
    return 0.0f;
}

float GLInput::GetJoypadStickHorizontal(int padNo) const {
    return 0.0f;
}

float GLInput::GetJoypadStickVertical(int padNo) const {
    return 0.0f;
}

#endif //__GLLIB