#pragma once

#include	"IParameterMap.h"

namespace Sample {

	/**
	 * @brief		管理パラメーター
	 */
	template <typename... Types>
	class ParameterMap : public IParameterMap
	{
	protected:
		std::tuple<ParameterContainerPtr<Types>...>		elements_;

		std::vector<GetterPtr>							getters_;

		template <unsigned int Index>
		using elementType = typename std::tuple_element<Index, decltype(elements_)>::type;

		template<typename T, unsigned int Index>
		using IsElement = std::is_same<elementType<Index>, T>;

		template<typename T, unsigned int Index = 0>
		struct FindElement : public std::conditional_t<
			IsElement<T, Index>::value,
			std::integral_constant<decltype(Index), Index>,
			FindElement<T, Index + 1>>
		{};

		template < typename T >
		struct Getter : IParameterMap::Getter<T> {
			ParameterContainerPtr<T>& Get(IParameterMap* _this) override {
				return static_cast<ParameterMap<Types...>*>(_this)->Get<T>();
			}
			const ParameterContainerPtr<T>& Get(const IParameterMap* _this) const override {
				return static_cast<const ParameterMap<Types...>*>(_this)->Get<T>();
			}
			ParameterHandle<T>& Get(IParameterMap* _this, const ParameterKeyType& key) override {
				return static_cast<ParameterMap<Types...>*>(_this)->Get<T>(key);
			}
			const ParameterHandle<T>& Get(const IParameterMap* _this, const ParameterKeyType& key) const override {
				return static_cast<const ParameterMap<Types...>*>(_this)->Get<T>(key);
			}
			void Set(IParameterMap* _this, const ParameterKeyType& key, const T& value) override {
				return static_cast<ParameterMap<Types...>*>(_this)->Set<T>(key, value);
			}
			size_t GetSize(const IParameterMap* _this) const override {
				return static_cast<const ParameterMap<Types...>*>(_this)->GetSize<T>();
			}
		};

		template<class First, class... Rest>
		struct Helper {
			static void Init(std::vector<GetterPtr>& bases_)
			{
				bases_.emplace_back(std::make_shared < Getter<First> >());
				Helper<Rest...>::Init(bases_);
			}
		};

		template<class First>
		struct Helper<First> {
			static void Init(std::vector<GetterPtr>& bases_)
			{
				bases_.emplace_back(std::make_shared< Getter<First> >());
			}
		};

		const std::vector<GetterPtr>& Getters() const override {
			return getters_;
		}

	public:
		/**
		 * @brief		コンストラクタ
		 */
		ParameterMap()
			: elements_() 
			, getters_() {
			Helper<Types...>::Init(getters_);
		}

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
		ParameterContainerPtr<T>& Get()
		{
			constexpr unsigned int index = FindElement<ParameterContainerPtr<T>>::value;
			auto& re = std::get<index>(elements_);
			if (re == nullptr)
			{
				re = std::make_shared<ParameterContainer<T>>();
			}
			return re;
		}

		template <typename T>
		const ParameterContainerPtr<T>& Get() const
		{
			return const_cast<ParameterMap*>(this)->Get<T>();
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
}