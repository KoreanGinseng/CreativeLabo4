#pragma once

namespace sip {
#ifdef __MOFLIB
    /**
        * ��`�@�\
        * Mof����ő��̃��C�u�������ւ̈ڐA���l����ꍇ
        *
        * Mof�̏ꍇCRectangle�����̂܂܎g�����A
        * ���앪�ŃJ�o�[���Ȃ����Ɋւ��Ă�delete�ō폜���Ďg���Ȃ�����
        */
#include	<Mof.h>
    class Rectangle : public CRectangle {
    public:
        //CRectangle�̃R���X�g���N�^�𗘗p
        using CRectangle::CRectangle;

        /**
            * @brief		���]������`�̎擾
            */
        Rectangle Reverse() {
            return Rectangle(Right, Top, Left, Bottom);
        }

        //�J�o�[���Ȃ��̂Ŏg���Ăق����Ȃ��@�\�̍폜
        void Expansion(const MofFloat e) = delete;
        void Expansion(const MofFloat ex, const MofFloat ey) = delete;
    };
#endif // __MOFLIB
}
