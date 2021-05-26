#include	"Input.h"

using namespace sip;

/**
 * @brief		更新
 */
void Input::Update() {
    for (auto k = keyMap_.begin(); k != keyMap_.end(); ++k) {
        k->second.prevValue = k->second.nowValue;
        k->second.nowValue = 0;
        for (auto& key : k->second.key) {
            switch (key.type) {
                //キーボード
            case KeyData::Type::Keyboard:
                k->second.nowValue += GetKeyboardKeyState(key.positiveNo, key.negativeNo);
                break;

                //マウス
            case KeyData::Type::Mouse:
                k->second.nowValue += GetMouseKeyState(key.positiveNo, key.negativeNo);
                break;

                //ジョイパッド
            case KeyData::Type::JoyPad:
                k->second.nowValue += GetJoypadKeyState(key.padNo, key.positiveNo, key.negativeNo);
                break;

                //ジョイスティック
            case KeyData::Type::JoyStickHorizontal:
                k->second.nowValue += GetJoypadStickHorizontal(key.padNo);
                break;

                //ジョイスティック
            case KeyData::Type::JoyStickVertical:
                k->second.nowValue += GetJoypadStickVertical(key.padNo);
                break;

            }
        }
        //-1～+1でクリップ
        if (k->second.nowValue > 1) { k->second.nowValue = 1; }
        else if (k->second.nowValue < -1) { k->second.nowValue = -1; }
    }
}
