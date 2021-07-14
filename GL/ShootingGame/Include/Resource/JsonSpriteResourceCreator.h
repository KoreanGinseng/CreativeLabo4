#pragma once

#include	"JsonResourceLoadHelper.h"
#include	"../Common/Sprite.h"
#include	"../Resource/Texture.h"
#include    "../Common/GraphicsController.h"

namespace sip {

    /**
     * @brief		���\�[�X�p�b�N��Json���琶������
     */
    class JsonSpriteResourceCreator {
    public:
        /**
         * @brief		JSon�t�@�C������̐���
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
         * @brief		JSon�t�@�C������̐���
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
     * �ǂݍ��ݗp�w���p�[
     */
    template < >
    struct JsonResourceLoadHelper<Sprite> {
        static void Load(ResourceContainerPtr<Sprite>& bases_, nlohmann::json& os) {
            JsonSpriteResourceCreator::Create(bases_, os);
        }
    };

}