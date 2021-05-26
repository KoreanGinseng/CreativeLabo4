#pragma once

#include	"ResourceContainer.h"

namespace sip {

    /**
     * @brief		�Ǘ����\�[�X�p�b�N
     */
    template <typename... Types>
    class ResourcePack {
    private:
        std::tuple<ResourceContainerPtr<Types>...>		elements_;

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
    public:
        /**
         * @brief		�R���X�g���N�^
         */
        ResourcePack()
            : elements_() {
        }

        /**
         * @brief		�o�^�R���e�i�̎擾
         */
        template <typename T>
        ResourceContainerPtr<T>& Get() {
            constexpr unsigned int index = FindElement<ResourceContainerPtr<T>>::value;
            auto& re = std::get<index>(elements_);
            if (re == nullptr) {
                re = std::make_shared<ResourceContainer<T>>();
            }
            return re;
        }

        template <typename T>
        const ResourceContainerPtr<T>& Get() const {
            return const_cast<ResourcePack*>(this)->Get<T>();
        }

        /**
         * @brief		���\�[�X���̎擾
         * @return		���\�[�X��
         */
        template <typename T> size_t GetSize() const { return Get<T>()->GetSize(); }
    };
    template <typename... Types> using ResourcePackPtr = std::shared_ptr< ResourcePack<Types...> >;

}