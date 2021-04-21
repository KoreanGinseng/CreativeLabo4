#pragma once

namespace Sample {

	/**
	 * 自作矩形機能
	 *
	 * ライブラリでは別のパラメーターで矩形を実現している場合
	 */
	struct ExternalRectangle {
		float			X;							//!<X
		float			Y;							//!<Y
		float			Width;						//!<幅
		float			Height;						//!<高さ
	};

	class Rectangle : public ExternalRectangle {
	public:
		Rectangle() {
			X = 0;
			Y = 0;
			Width = 0;
			Height = 0;
		}
		Rectangle(float l, float t, float r, float b) {
			X = l;
			Y = t;
			Width = r - l;
			Height = b - t;
		}

		float GetLeft(void) const
		{
			return X;
		}
		float GetRight(void) const
		{
			return X + Width;
		}

		float GetTop(void) const
		{
			return Y;
		}
		float GetBottom(void) const
		{
			return Y + Height;
		}

		/**
		 * @brief		反転した矩形の取得
		 */
		Rectangle Reverse() {
			return Rectangle(X, Y, -Width, Height);
		}

		/**
		 * @brief		判定
		 */
		bool CollisionRect(const Rectangle& r) const {
			if ((r.X + r.Width) >= X && r.X <= (X + Width) && (r.Y + r.Height) >= Y && r.Y <= (Y + Height))
			{
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
			return CRectangle(GetLeft(), GetTop(), GetRight(), GetBottom());
		}
		operator const CRectangle() const {
			return CRectangle(GetLeft(), GetTop(), GetRight(), GetBottom());
		}
		Rectangle(const CRectangle& v) {
			X = v.Left;
			Y = v.Top;
			Width = v.Right - v.Left;
			Height = v.Bottom - v.Top;
		}
		Rectangle& operator = (const CRectangle& v) {
			X = v.Left;
			Y = v.Top;
			Width = v.Right - v.Left;
			Height = v.Bottom - v.Top;
			return *this;
		}
#endif
	};
}