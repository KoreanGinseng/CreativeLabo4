#pragma once

#include	"ResourcePack.h"
#include	"JsonResourcePackCreator.h"
#include	"JsonResourceLoadHelper.h"
#include	"../Common/Singleton.h"

namespace sip {

    /**
     * @brief		���\�[�X�Ǘ�
     */
    template <typename... Types>
    class ResourceManager : public Singleton<ResourceManager<Types...>> {
        friend class Singleton<ResourceManager<Types...>>;
    private:
        std::unordered_map< ResourceContainerKeyType, ResourcePackPtr<Types...> > resources_;

        /**
         * @brief		�R���X�g���N�^
         */
        ResourceManager()
            : resources_() {
        }
    public:
        /**
         * @brief		�V�K���\�[�X�p�b�N�̐���
         * @param[in]	key		�L�[
         * @return		�����������\�[�X�p�b�N
         */
        ResourcePackPtr<Types...> AddPack(const ResourceContainerKeyType& key) {
            auto re = std::make_shared<ResourcePack<Types...>>();
            resources_[key] = re;
            return re;
        }

        /**
         * @brief		�V�K���\�[�X�p�b�N�̓ǂݍ���
         * @param[in]	key		�L�[
         * @param[in]	name	Json�t�@�C����
         * @return		�����������\�[�X�p�b�N
         */
        ResourcePackPtr<Types...> LoadPack(const ResourceContainerKeyType& key, const std::string& name) {
            auto re = JsonResourcePackCreator<Types...>::Create(name);
            resources_[key] = re;
            return re;
        }

        /**
         * @brief		���\�[�X�p�b�N�̍폜
         * @param[in]	key		�L�[
         * @return		true	����
         *				false	���s
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
         * @brief		�o�^���\�[�X�p�b�N�̎擾
         * @param[in]	key		�L�[
         * @return		���������\�[�X�p�b�N
         */
        ResourcePackPtr<Types...> GetPack(const ResourceContainerKeyType& key) {
            auto it = resources_.find(key);
            if (it != resources_.end()) {
                return it->second;
            }
            return ResourcePackPtr<Types...>();
        }

        /**
         * @brief		�S�Ă̓o�^���\�[�X����̌���
         * @param[in]	key		�L�[
         * @return		���������\�[�X
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

//�ȈՃA�N�Z�X�p
#include	"Texture.h"
#include	"JsonTextureResourceCreator.h"
#define UsedResources sip::Texture
#define ResourceManagerInstance	sip::ResourceManager<UsedResources>::GetInstance()
