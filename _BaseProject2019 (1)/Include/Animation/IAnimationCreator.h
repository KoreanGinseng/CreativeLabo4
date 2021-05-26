#pragma once

#include	"IAnimationState.h"

namespace sip {
    /**
        * @brief		アニメーションインターフェイス
        */
    class __declspec(novtable) IAnimationCreator {
    public:
        /**
            * @brief		デストラクタ
            */
        virtual ~IAnimationCreator() = default;

        /**
            * @brief		生成
            */
        virtual AnimationStatePtr Create() = 0;
    };
    //ポインタ置き換え
    using AnimationCreatorPtr = std::shared_ptr<IAnimationCreator>;
}
