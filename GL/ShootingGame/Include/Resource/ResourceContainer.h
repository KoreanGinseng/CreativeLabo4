#pragma once

#include	"../Common/Common.h"

namespace sip {

    //キー
    using ResourceContainerKeyType = std::string;

    /**
     * @brief	リソース管理用コンテナ
     */
    template < typename T >
    class ResourceContainer {
    public:
        using Resource = std::shared_ptr< T >;
    private:
        std::unordered_map< ResourceContainerKeyType, Resource > resources_;

    public:
        /**
         * @brief		コンストラクタ
         */
        ResourceContainer()
            : resources_() {
        }

        /**
         * @brief		リソースの新規追加
         * @param[in]	key		登録キー
         * @param[in]	_Types	追加するリソースの初期化に必要なもの
         * @return		追加したリソース
         *
         */
        template < typename... _Types >
        Resource Add(const ResourceContainerKeyType& key, _Types&& ... _Args) {
            auto re = std::make_shared<T>(_Args...);
            resources_[key] = re;
            return re;
        }

        /**
         * @brief		既存リソースの追加
         * @param[in]	key		登録キー
         * @param[in]	rc		追加するリソース
         */
        void Add(const ResourceContainerKeyType& key, Resource& rc) {
            resources_[key] = rc;
        }

        /**
         * @brief		リソースの取得
         * @param[in]	key		キー
         * @return		該当するリソース
         */
        Resource Get(const ResourceContainerKeyType& key) {
            auto it = resources_.find(key);
            if (it != resources_.end()) {
                return it->second;
            }
            return std::shared_ptr< T >();
        }

        std::unordered_map< ResourceContainerKeyType, Resource >& Resources() { return resources_; }

        /**
         * @brief		リソース数の取得
         * @return		リソース数
         */
        size_t GetSize() const { return resources_.size(); }
    };
    template <typename T> using ResourceContainerPtr = std::shared_ptr< ResourceContainer<T> >;
}