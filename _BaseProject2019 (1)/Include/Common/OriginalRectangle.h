#pragma once

namespace sip {
    /**
        * 自作矩形機能
        *
        * 自作矩形機能を使いながらWofへの受け渡しを考える場合
        */
    class Rectangle {
    public:
        float			Left;						//!<左
        float			Top;						//!<上
        float			Right;						//!<右
        float			Bottom;						//!<下

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
            * @brief		反転した矩形の取得
            */
        Rectangle Reverse() {
            return Rectangle(Right, Top, Left, Bottom);
        }

        /**
            * @brief		判定
            */
        bool CollisionRect(const Rectangle& r) const {
            if (r.Right >= Left && r.Left <= Right && r.Bottom >= Top && r.Top <= Bottom) {
                return true;
            }
            return false;
        }

        /**
            * @brief		MOFとの変換
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