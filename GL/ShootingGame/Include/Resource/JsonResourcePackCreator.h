#pragma once

#include	"ResourcePack.h"
#include    "JsonResourceLoadHelper.h"
#include	"../External/nlohmann/json.hpp"

namespace sip {

    /**
     * @brief		リソースパックをJsonから生成する
     */
    template <typename... Types>
    class JsonResourcePackCreator {
    private:
        /**
         * @brief	内部タプル展開用ヘルパー
         */
        template<class First, class... Rest>
        struct Helper {
            static void Load(ResourcePackPtr<Types...>& bases_, nlohmann::json& os) {
                JsonResourceLoadHelper<First>::Load(bases_->Get<First>(), os);
                Helper<Rest...>::Load(bases_, os);
            }
        };

        template<class First>
        struct Helper<First> {
            static void Load(ResourcePackPtr<Types...>& bases_, nlohmann::json& os) {
                JsonResourceLoadHelper<First>::Load(bases_->Get<First>(), os);
            }
        };

    public:
        /**
         * @brief		JSonファイルからの生成
         */
        static ResourcePackPtr<Types...> Create(const std::string& name) {
            std::ifstream ifs(name);
            if (ifs.fail()) {
                return ResourcePackPtr<Types...>();
            }
            nlohmann::json os = nlohmann::json::parse(ifs);
            auto re = std::make_shared<ResourcePack<Types...>>();
            Helper<Types...>::Load(re, os);
            return re;
        }
    };

}