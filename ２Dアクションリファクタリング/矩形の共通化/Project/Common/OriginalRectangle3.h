#pragma once

namespace Sample {

	/**
	 * �����`�@�\
	 *
	 * ���C�u�����ł͓����p�����[�^�[�ł����O���Ⴄ�ꍇ
	 */
	struct ExternalRectangle {
		float			left;						//!<��
		float			top;						//!<��
		float			right;						//!<�E
		float			bottom;						//!<��


		/**
		 * @brief		����
		 */
		bool Intersect(const ExternalRectangle& r) const {
			if (r.right >= left && r.left <= right && r.bottom >= top && r.top <= bottom)
			{
				return true;
			}
			return false;
		}
	};

	/**
	 * �����`�@�\
	 *
	 * �����`�@�\���g���Ȃ���Wof�ւ̎󂯓n�����l����ꍇ
	 */
	class Rectangle {
	public:
		//���p�̂ŋ��ʂ̃��������Q��
		union {
			ExternalRectangle	rect;
			struct
			{
				float			Left;						//!<��
				float			Top;						//!<��
				float			Right;						//!<�E
				float			Bottom;						//!<��
			};
		};

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

		float GetWidth(void) const
		{
			return Right - Left;
		}

		float GetHeight(void) const
		{
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
			return rect.Intersect(r.rect);
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