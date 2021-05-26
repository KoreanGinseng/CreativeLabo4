#pragma once

namespace sip {
#ifdef __MOFLIB
    /**
        * 矩形機能
        * Mofを基準で他のライブラリ環境への移植を考える場合
        *
        * Mofの場合CRectangleをそのまま使うが、
        * 自作分でカバーしない分に関してはdeleteで削除して使えなくする
        */
#include	<Mof.h>
    class Rectangle : public CRectangle {
    public:
        //CRectangleのコンストラクタを利用
        using CRectangle::CRectangle;

        /**
            * @brief		反転した矩形の取得
            */
        Rectangle Reverse() {
            return Rectangle(Right, Top, Left, Bottom);
        }

        //カバーしないので使ってほしくない機能の削除
        void Expansion(const MofFloat e) = delete;
        void Expansion(const MofFloat ex, const MofFloat ey) = delete;
    };
#endif // __MOFLIB
}
