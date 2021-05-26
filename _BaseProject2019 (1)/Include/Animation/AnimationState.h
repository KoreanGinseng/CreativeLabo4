#pragma once

#include	"IAnimationState.h"

namespace sip {
    /**
        * @brief		�A�j���[�V����
        */
    class AnimationState : public IAnimationState {
    protected:
        /** ���` */
        Rectangle		srcRect_;
    public:
        /**
            * @brief		�R���X�g���N�^
            */
        AnimationState()
            : srcRect_() {
        }

        /**
            * @brief	���݂̃A�j���[�V������`�擾
            * @return	���݂̃A�j���[�V������`
            */
        Rectangle& GetSrcRect() override {
            return srcRect_;
        }
        /**
            * @brief	���݂̃A�j���[�V������`�擾
            * @return	���݂̃A�j���[�V������`
            */
        const Rectangle& GetSrcRect() const override {
            return srcRect_;
        }
    };
}