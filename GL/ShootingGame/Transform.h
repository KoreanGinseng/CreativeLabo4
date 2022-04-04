#pragma once
#include <memory>

class Transform {
protected:
	float positionX_;
	float positionY_;

public:

	Transform()
		: positionX_(0)
		, positionY_(0) {
	}

	void Move(float x, float y) noexcept {
		positionX_ += x;
		positionY_ += y;
	}

	void SetPosition(float x, float y) noexcept {
		positionX_ = x;
		positionY_ = y;
	}

	void SetPositionX(float x) noexcept {
		positionX_ = x;
	}

	void SetPositionY(float y) noexcept {
		positionY_ = y;
	}

	float GetPositionX() const noexcept {
		return positionX_;
	}

	float GetPositionY() const noexcept {
		return positionY_;
	}

	static std::shared_ptr<Transform> Create() { return std::make_shared<Transform>(); }
};

//ポインタ置き換え
using TransformPtr = std::shared_ptr<Transform>;
