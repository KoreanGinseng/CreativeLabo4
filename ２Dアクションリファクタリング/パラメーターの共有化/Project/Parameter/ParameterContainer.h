#pragma once

#include	"ParameterHandle.h"

namespace Sample {

	//�L�[
	using ParameterKeyType = std::string;

	/**
	 * @brief	�p�����[�^�[�Ǘ��p�R���e�i
	 */
	template < typename T >
	class ParameterContainer {
	private:
		/** �l�̃R���e�i */
		std::unordered_map< ParameterKeyType, ParameterHandle< T > > values_;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		ParameterContainer()
			: values_() {}

		/**
		 * @brief		�ݒ�
		 */
		void Set(const ParameterKeyType& key, const T& value) { values_[key] = value; }

		/**
		 * @brief		�擾
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