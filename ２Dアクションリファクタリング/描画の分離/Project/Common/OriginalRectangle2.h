#pragma once

namespace Sample {

	/**
	 * �����`�@�\
	 *
	 * ���C�u�����ł͕ʂ̃p�����[�^�[�ŋ�`���������Ă���ꍇ
	 */
	struct ExternalRectangle {
		float			X;							//!<X
		float			Y;							//!<Y
		float			Width;						//!<��
		float			Height;						//!<����
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
		 * @brief		���]������`�̎擾
		 */
		Rectangle Reverse() {
			return Rectangle(X, Y, -Width, Height);
		}

		/**
		 * @brief		����
		 */
		bool CollisionRect(const Rectangle& r) const {
			if ((r.X + r.Width) >= X && r.X <= (X + Width) && (r.Y + r.Height) >= Y && r.Y <= (Y + Height))
			{
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