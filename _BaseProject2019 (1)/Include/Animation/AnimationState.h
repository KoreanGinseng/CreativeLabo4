#pragma once

#include	"IAnimationState.h"

namespace sip {
    /**
        * @brief		アニメーション
        */
    class AnimationState : public IAnimationState {
    protected:
        /** 基準矩形 */
        Rectangle		srcRect_;
    public:
        /**
            * @brief		コンストラクタ
            */
        AnimationState()
            : srcRect_() {
        }

        /**
            * @brief	現在のアニメーション矩形取得
            * @return	現在のアニメーション矩形
            */
        Rectangle& GetSrcRect() override {
            return srcRect_;
        }
        /**
            * @brief	現在のアニメーション矩形取得
            * @return	現在のアニメーション矩形
            */
        const Rectangle& GetSrcRect() const override {
            return srcRect_;
        }
    };
}