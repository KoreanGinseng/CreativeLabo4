#pragma once

#include	"JsonResourceLoadHelper.h"
#include	"../Common/Sprite.h"
#include	"../Resource/Texture.h"
#include    "../Common/GraphicsController.h"

namespace sip {

    /**
     * @brief		リソースパックをJsonから生成する
     */
    class JsonSpriteResourceCreator {
    public:
        /**
         * @brief		JSonファイルからの生成
         */
        static ResourceContainerPtr<Sprite> Create(const std::string& name) {
            std::ifstream ifs(name);
            if (ifs.fail()) {
                return ResourceContainerPtr<Sprite>();
            }
            nlohmann::json os = nlohmann::json::parse(ifs);
            auto re = std::make_shared<ResourceContainer<Sprite>>();
            Create(re, os);
            return re;
        }

        /**
         * @brief		JSonファイルからの生成
         */
        static void Create(ResourceContainerPtr<Sprite>& bases_, nlohmann::json& os) {
            auto& texs = os["Sprites"];
            for (auto& tex : texs) {
                ResourceContainerKeyType key;
                tex["Key"].get_to(key);
                std::string name;
                tex["File"].get_to(name);
                auto tex = std::make_shared<Texture>();
                tex->Load(name.c_str());
                auto sprite = bases_->Add(key);
                sprite->Create(tex, GraphicsControllerInstance.SpriteShader());
            }
        }
    };

    /**
     * 読み込み用ヘルパー
     */
    template < >
    struct JsonResourceLoadHelper<Sprite> {
        static void Load(ResourceContainerPtr<Sprite>& bases_, nlohmann::json& os) {
            JsonSpriteResourceCreator::Create(bases_, os);
        }
    };

}