#pragma once

#include	"ParameterHandle.h"

namespace Sample {

	//キー
	using ParameterKeyType = std::string;

	/**
	 * @brief	パラメーター管理用コンテナ
	 */
	template < typename T >
	class ParameterContainer {
	private:
		/** 値のコンテナ */
		std::unordered_map< ParameterKeyType, ParameterHandle< T > > values_;

	public:
		/**
		 * @brief		コンストラクタ
		 */
		ParameterContainer()
			: values_() {}

		/**
		 * @brief		設定
		 */
		void Set(const ParameterKeyType& key, const T& value) { values_[key] = value; }

		/**
		 * @brief		取得
		 */
		ParameterHandle< T >& Get(const ParameterKeyType& key) { return values_[key]; }
		const ParameterHandle< T >& Get(const ParameterKeyType& key) const {
			auto& it = values_.find(key);
			assert(it != values_.end());
			return it->second;
		}
		ParameterHandle< T >& operator [] (const ParameterKeyType& key) { return values_[key]; }
		const ParameterHandle< T >& operator [] (const ParameterKeyType& key) const {
			auto& it = values_.find(key);
			assert(it != values_.end());
			return it->second;
		}
		size_t GetSize() const { return values_.size(); }

	};
	template <typename T> using ParameterContainerPtr = std::shared_ptr< ParameterContainer<T> >;
}