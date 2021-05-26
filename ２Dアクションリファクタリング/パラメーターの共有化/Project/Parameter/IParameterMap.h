#pragma once

#include	"ParameterContainer.h"

namespace Sample {

	/**
	 * @brief		パラメーター保持
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
		 * @brief		デストラクタ
		 */
		virtual ~IParameterMap() = default;

		/**
		 * @brief		設定
		 */
		template <typename T>
		void Set(const ParameterKeyType& key, const T& value)
		{
			return Get<T>()->Set(key, value);
		}

		/**
		 * @brief		登録コンテナの取得
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
		 * @brief		登録パラメーターの取得
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
		 * @brief		パラメーター数の取得
		 * @return		パラメーター数
		 */
		template <typename T> size_t GetSize() const { return Get<T>()->GetSize(); }
	};
	//ポインタ置き換え
	using ParameterMapPtr = std::shared_ptr<IParameterMap>;
}