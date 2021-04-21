#pragma once

namespace Sample {

	/**
	 * 自作矩形機能
	 *
	 * ライブラリでは同じパラメーターでも名前が違う場合
	 */
	struct ExternalRectangle {
		float			left;						//!<左
		float			top;						//!<上
		float			right;						//!<右
		float			bottom;						//!<下


		/**
		 * @brief		判定
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
	 * 自作矩形機能
	 *
	 * 自作矩形機能を使いながらWofへの受け渡しを考える場合
	 */
	class Rectangle {
	public:
		//共用体で共通のメモリを参照
		union {
			ExternalRectangle	rect;
			struct
			{
				float			Left;						//!<左
				float			Top;						//!<上
				float			Right;						//!<右
				float			Bottom;						//!<下
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
		 * @brief		反転した矩形の取得
		 */
		Rectangle Reverse() {
			return Rectangle(Right, Top, Left, Bottom);
		}

		/**
		 * @brief		判定
		 */
		bool CollisionRect(const Rectangle& r) const {
			return rect.Intersect(r.rect);
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