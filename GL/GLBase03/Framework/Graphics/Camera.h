#pragma once

#include	"../Math/Vector3.h"

namespace Sample {

	class Camera
	{
	private:
		/** カメラの位置 */
		Vector3F			position_;

		/** ビュープロジェクション行列 */
		glm::mat4			matVP_;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		Camera()
			: position_()
			, matVP_() {
		}
		/**
		 * @brief		コピーコンストラクタ
		 * @param[in]	obj	コピーするカメラ
		 */
		Camera(const Camera& obj)
			: position_(obj.position_)
			, matVP_(obj.matVP_) {
		}

		/**
		 * @brief		デストラクタ
		 */
		virtual ~Camera() {
		}

		/**
		 * @brief		2D用カメラの生成
		 * @param[in]	w	幅
		 * @param[in]	h	高さ
		 */
		void Create2D(int w, int h) {
			const glm::vec2 hs(w * 0.5f, h * 0.5f);
			const glm::mat4x4 matProj = glm::ortho(-hs.x, hs.x, -hs.y, hs.y, 1.0f, 1000.0f);
			const glm::mat4x4 matView = glm::lookAt(
				glm::vec3(hs.x + position_.x, -hs.y - position_.y, 100),
				glm::vec3(hs.x + position_.x, -hs.y - position_.y, 0), glm::vec3(0, 1, 0));
			matVP_ = matProj * matView;
		}

		/**
		 * @brief		PositionへのAccessor
		 * @param[in]	p	位置
		 */
		void Position(const Vector3F& p) { position_ = p; }
		/**
		 * @brief		PositionへのAccessor
		 * @return		位置
		 */
		const Vector3F& Position() const noexcept { return position_; }

		/**
		 * @brief		matVP_へのAccessor
		 * @return		ビュープロジェクション
		 */
		const glm::mat4& ViewProjection() const { return matVP_; }
	};
	//ポインタ置き換え
	using CameraPtr = std::shared_ptr<Camera>;

}