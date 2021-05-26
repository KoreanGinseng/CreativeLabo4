#pragma once

namespace sip {
    /**
        * �����`�@�\
        *
        * �����`�@�\���g���Ȃ���Wof�ւ̎󂯓n�����l����ꍇ
        */
    class Rectangle {
    public:
        float			Left;						//!<��
        float			Top;						//!<��
        float			Right;						//!<�E
        float			Bottom;						//!<��

        Rectangle()
            : Left(0)
            , Top(0)
            , Right(0)
            , Bottom(0) {
        }
        Rectangle(float l, float t, float r, float b)
            : Left(l)
            , Top(t)
            , Right(r)
            , Bottom(b) {
        }

        float GetWidth(void) const {
            return Right - Left;
        }

        float GetHeight(void) const {
            return Bottom - Top;
        }

        /**
            * @brief		���]������`�̎擾
            */
        Rectangle Reverse() {
            return Rectangle(Right, Top, Left, Bottom);
        }

        /**
            * @brief		����
            */
        bool CollisionRect(const Rectangle& r) const {
            if (r.Right >= Left && r.Left <= Right && r.Bottom >= Top && r.Top <= Bottom) {
                return true;
            }
            return false;
        }

        /**
            * @brief		MOF�Ƃ̕ϊ�
            */
#ifdef __MOFLIB
#include	<Mof.h>
        operator CRectangle () {
            return CRectangle(Left, Top, Right, Bottom);
        }
        operator const CRectangle() const {
            return CRectangle(Left, Top, Right, Bottom);
        }
        Rectangle(const CRectangle& v)
            : Left(v.Left)
            , Top(v.Top)
            , Right(v.Right)
            , Bottom(v.Bottom) {
        }
        Rectangle& operator = (const CRectangle& v) {
            Left = v.Left;
            Right = v.Right;
            Top = v.Top;
            Bottom = v.Bottom;
            return *this;
        }
#endif
    };
}