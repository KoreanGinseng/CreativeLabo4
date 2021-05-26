#pragma once

#include	"ParameterContainer.h"

namespace Sample {

	/**
	 * @brief		�p�����[�^�[�ێ�
	 */
	class IParameterMap
	{
	protected:
		struct GetterBase {
			virtual ~GetterBase() {}
			virtual const size_t Hash() const = 0;
		};
		using GetterPtr = std::shared_ptr< GetterBase >;
		template < typename T >
		struct Getter : public GetterBase {
			const size_t Hash() const override { static const size_t hash = typeid(T).hash_code(); return hash; }
			virtual ParameterContainerPtr<T>& Get(IParameterMap* _this) = 0;
			virtual const ParameterContainerPtr<T>& Get(const IParameterMap* _this) const = 0;
			virtual ParameterHandle<T>& Get(IParameterMap* _this, const ParameterKeyType& key) = 0;
			virtual const ParameterHandle<T>& Get(const IParameterMap* _this, const ParameterKeyType& key) const = 0;
			virtual void Set(IParameterMap* _this, const ParameterKeyType& key, const T& value) = 0;
			virtual size_t GetSize(const IParameterMap* _this) const = 0;
		};

		virtual const std::vector<GetterPtr>& Getters() const = 0;
	public:
		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~IParameterMap() = default;

		/**
		 * @brief		�ݒ�
		 */
		template <typename T>
		void Set(const ParameterKeyType& key, const T& value)
		{
			return Get<T>()->Set(key, value);
		}

		/**
		 * @brief		�o�^�R���e�i�̎擾
		 */
		template <typename T>
		ParameterContainerPtr<T> Get()
		{
			static const size_t hash = typeid(T).hash_code();
			auto& getters = Getters();
			for (auto& g : getters)
			{
				if (g->Hash() == hash)
				{
					return std::static_pointer_cast<Getter<T>>(g)->Get(this);
				}
			}
			assert(false);
			return ParameterContainerPtr<T>();
		}

		template <typename T>
		const ParameterContainerPtr<T> Get() const
		{
			return const_cast<IParameterMap*>(this)->Get<T>();
		}

		/**
		 * @brief		�o�^�p�����[�^�[�̎擾
		 */
		template <typename T>
		ParameterHandle<T>& Get(const ParameterKeyType& key)
		{
			return Get<T>()->Get(key);
		}

		template <typename T>
		const ParameterHandle<T>& Get(const ParameterKeyType& key) const
		{
			return const_cast<ParameterMap*>(this)->Get<T>(key);
		}

		/**
		 * @brief		�p�����[�^�[���̎擾
		 * @return		�p�����[�^�[��
		 */
		template <typename T> size_t GetSize() const { return Get<T>()->GetSize(); }
	};
	//�|�C���^�u������
	using ParameterMapPtr = std::shared_ptr<IParameterMap>;
}