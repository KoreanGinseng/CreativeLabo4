#pragma once

#include	"../Common/Common.h"
#include	"../Common/Rectangle.h"

namespace sip {
    /**
        * @brief		�A�j���[�V�����C���^�[�t�F�C�X
        */
    class __declspec(novtable) IAnimationState {
    public:

        /**
            * @brief		�A�j���[�V�����p�^�[���f�[�^
            */
        struct AnimationPattern {
            int									Wait;						//!<�t���[���E�F�C�g
            int									No;							//!<�p�^�[���ԍ�
            int									Step;						//!<�p�^�[���i
        };
        /**
            * @brief		�A�j���[�V�����f�[�^
            */
        struct AnimationData {
            std::string							Name;						//!<�A�j���[�V������
            float								OffsetX;					//!<X�I�t�Z�b�g�ʒu
            float								OffsetY;					//!<Y�I�t�Z�b�g�ʒu
            float								Width;						//!<��
            float								Height;						//!<����
            bool								bLoop;						//!<���[�v�t���O(TRUE�Ȃ烋�[�v�AFALSE�Ȃ�ŏI�t���[���Œ�~)
            std::vector< AnimationPattern >		Pattern;					//!<�p�^�[��
        };

        /**
            * @brief		�f�X�g���N�^
            */
        virtual ~IAnimationState() = default;

        /**
            * @brief		Mof�̃A�j���[�V�����R���g���[���[����
            * @param[in]	pattern			�A�j���[�V�����������
            * @return		true			����
            *				false			���s
            */
        virtual bool Create(const std::vector< AnimationData >& pattern) = 0;

        /**
            * @brief		�X�V
            */
        virtual void Update() = 0;

        /**
            * @brief		���݂̃��[�V������ύX
            * @param[in]	name	�o�^���[�V������
            * @param[in]	isSame	���ꃂ�[�V�����ł̍X�V�t���O
            * @return		true	�w�胂�[�V�������s��
            *				false	�Ⴄ
            */
        virtual bool ChangeMotion(const std::string& name, bool isSame = true) = 0;

        /**
            * @brief		�w�薼�̂̓o�^���[�V���������s����Ă��邩�ǂ���
            * @param[in]	name	�o�^���[�V������
            * @return		true	�w�胂�[�V�������s��
            *				false	�Ⴄ
            */
        virtual bool IsMotion(const std::string& name) const = 0;

        /**
            * @brief		���݂̃��[�V�������I�����Ă��邩�𔻒肷��B
            *				���[�V���������[�v����ꍇ��TRUE�ɂȂ邱�Ƃ͂Ȃ�
            * @return		true	�I���ς�
            *				false	�܂��I�����Ă��Ȃ�
            */
        virtual bool IsEndMotion() = 0;

        /**
            * @brief	���݂̃A�j���[�V������`�擾
            * @return	���݂̃A�j���[�V������`
            */
        virtual Rectangle& GetSrcRect() = 0;
        /**
            * @brief	���݂̃A�j���[�V������`�擾
            * @return	���݂̃A�j���[�V������`
            */
        virtual const Rectangle& GetSrcRect() const = 0;
    };
    //�|�C���^�u������
    using AnimationStatePtr = std::shared_ptr<IAnimationState>;
}
