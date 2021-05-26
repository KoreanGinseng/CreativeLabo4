#pragma once

#include	"../Common/Common.h"

namespace Sample {

	/**
	 * @brief		パラメーター保持
	 */
	template < typename T >
	class ParameterHandle
	{
	protected:
		/** パラメーター */
		std::shared_ptr< T >			value_;

	public:
		/**
		 * @brief		コンストラクタ
		 */
		ParameterHandle() : value_(std::make_shared<T>()) { }
		ParameterHandle(const ParameterHandle& param) : value_(param) {}
		ParameterHandle(const T& initValue) : value_(std::make_shared<T>(initValue)) {}

		/**
		 * @brief		取得
		 */
		T& Get() { return *value_; }
		const T& Get() const { return *value_; }
		operator T& () { return *value_; }
		operator const T& () const { return *value_; }

		/**
		 * @brief		設定
		 */
		void Set(const T& v) { *value_ = v; }
		ParameterHandle< T >& operator = (const ParameterHandle< T >& v) {
			value_ = v.value_;
			return *this;
		}
		const T& operator = (const T& v) {
			*value_ = v;
			return *value_;
		}
		const T& operator * () {
			return *value_;
		}

		/** 算術演算子 +　-　* /　*/
		T operator + (const ParameterHandle< T >& v) const {
			return *value_ + *v.value;
		}
		T operator + (const T& v) const {
			return *value_ + v;
		}
		T operator - (const ParameterHandle< T >& v) const {
			return *value_ - *v.value;
		}
		T operator - (const T& v) const {
			return *value_ - v;
		}
		T operator * (const ParameterHandle< T >& v) const {
			return *value_ * *v.value;
		}
		T operator * (const T& v) const {
			return *value_ * v;
		}
		T operator / (const ParameterHandle< T >& v) const {
			return *value_ / *v.value;
		}
		T operator / (const T& v) const {
			return *value_ / v;
		}

		/** 複合代入演算子 +=　-=　*=　/= */
		ParameterHandle< T >& operator += (const ParameterHandle< T >& v) {
			*value_ += *v.value;
			return *this;
		}
		ParameterHandle< T >& operator += (const T& v) {
			*value_ += v;
			return *this;
		}
		ParameterHandle< T >& operator -= (const ParameterHandle< T >& v) {
			*value_ -= *v.value;
			return *this;
		}
		ParameterHandle< T >& operator -= (const T& v) {
			*value_ -= v;
			return *this;
		}
		ParameterHandle< T >& operator *= (const ParameterHandle< T >& v) {
			*value_ *= *v.value;
			return *this;
		}
		ParameterHandle< T >& operator *= (const T& v) {
			*value_ *= v;
			return *this;
		}
		ParameterHandle< T >& operator /= (const ParameterHandle< T >& v) {
			*value_ /= *v.value;
			return *this;
		}
		ParameterHandle< T >& operator /= (const T& v) {
			*value_ /= v;
			return *this;
		}

		/** 比較演算子 == != <= < >= > */
		bool operator == (const ParameterHandle< T >& v) const {
			return *value_ == *v.value;
		}
		bool operator == (const T& v) const {
			return *value_ == v;
		}
		bool operator != (const ParameterHandle< T >& v) const {
			return *value_ != *v.value;
		}
		bool operator != (const T& v) const {
			return *value_ != v;
		}
		bool operator <= (const ParameterHandle< T >& v) const {
			return *value_ <= *v.value;
		}
		bool operator <= (const T& v) const {
			return *value_ <= v;
		}
		bool operator < (const ParameterHandle< T >& v) const {
			return *value_ < *v.value;
		}
		bool operator < (const T& v) const {
			return *value_ < v;
		}
		bool operator >= (const ParameterHandle< T >& v) const {
			return *value_ >= *v.value;
		}
		bool operator >= (const T& v) const {
			return *value_ >= v;
		}
		bool operator > (const ParameterHandle< T >& v) const {
			return *value_ > *v.value;
		}
		bool operator > (const T& v) const {
			return *value_ > v;
		}
	};

}