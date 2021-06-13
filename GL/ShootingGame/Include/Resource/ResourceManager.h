#pragma once

#include	"ResourcePack.h"
#include	"JsonResourcePackCreator.h"
#include	"JsonResourceLoadHelper.h"
#include	"../Common/Singleton.h"

namespace sip {

    /**
     * @brief		リソース管理
     */
    template <typename... Types>
    class ResourceManager : public Singleton<ResourceManager<Types...>> {
        friend class Singleton<ResourceManager<Types...>>;
    private:
        std::unordered_map< ResourceContainerKeyType, ResourcePackPtr<Types...> > resources_;

        /**
         * @brief		コンストラクタ
         */
        ResourceManager()
            : resources_() {
        }
    public:
        /**
         * @brief		新規リソースパックの生成
         * @param[in]	key		キー
         * @return		生成したリソースパック
         */
        ResourcePackPtr<Types...> AddPack(const ResourceContainerKeyType& key) {
            auto re = std::make_shared<ResourcePack<Types...>>();
            resources_[key] = re;
            return re;
        }

        /**
         * @brief		新規リソースパックの読み込み
         * @param[in]	key		キー
         * @param[in]	name	Jsonファイル名
         * @return		生成したリソースパック
         */
        ResourcePackPtr<Types...> LoadPack(const ResourceContainerKeyType& key, const std::string& name) {
            auto re = JsonResourcePackCreator<Types...>::Create(name);
            resources_[key] = re;
            return re;
        }

        /**
         * @brief		リソースパックの削除
         * @param[in]	key		キー
         * @return		true	成功
         *				false	失敗
         */
        bool DeletePack(const ResourceContainerKeyType& key) {
            auto it = resources_.find(key);
            if (it != resources_.end()) {
                resources_.erase(it);
                return true;
            }
            return false;
        }

        /**
         * @brief		登録リソースパックの取得
         * @param[in]	key		キー
         * @return		見つけたリソースパック
         */
        ResourcePackPtr<Types...> GetPack(const ResourceContainerKeyType& key) {
            auto it = resources_.find(key);
            if (it != resources_.end()) {
                return it->second;
            }
            return ResourcePackPtr<Types...>();
        }

        /**
         * @brief		全ての登録リソースからの検索
         * @param[in]	key		キー
         * @return		見つけたリソース
         */
        template <typename T>
        std::shared_ptr<T> GetResource(const ResourceContainerKeyType& key) {
            for (auto it : resources_) {
                auto t = it.second->Get<T>()->Get(key);
                if (t) {
                    return t;
                }
            }
            return std::shared_ptr<T>();
        }
    };

}

//簡易アクセス用
#include	"Texture.h"
#include	"JsonTextureResourceCreator.h"
#define UsedResources sip::Texture
#define ResourceManagerInstance	sip::ResourceManager<UsedResources>::GetInstance()
