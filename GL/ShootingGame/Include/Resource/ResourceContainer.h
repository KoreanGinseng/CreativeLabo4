#pragma once

#include	"../Common/Common.h"

namespace sip {

    //�L�[
    using ResourceContainerKeyType = std::string;

    /**
     * @brief	���\�[�X�Ǘ��p�R���e�i
     */
    template < typename T >
    class ResourceContainer {
    public:
        using Resource = std::shared_ptr< T >;
    private:
        std::unordered_map< ResourceContainerKeyType, Resource > resources_;

    public:
        /**
         * @brief		�R���X�g���N�^
         */
        ResourceContainer()
            : resources_() {
        }

        /**
         * @brief		���\�[�X�̐V�K�ǉ�
         * @param[in]	key		�o�^�L�[
         * @param[in]	_Types	�ǉ����郊�\�[�X�̏������ɕK�v�Ȃ���
         * @return		�ǉ��������\�[�X
         *
         */
        template < typename... _Types >
        Resource Add(const ResourceContainerKeyType& key, _Types&& ... _Args) {
            auto re = std::make_shared<T>(_Args...);
            resources_[key] = re;
            return re;
        }

        /**
         * @brief		�������\�[�X�̒ǉ�
         * @param[in]	key		�o�^�L�[
         * @param[in]	rc		�ǉ����郊�\�[�X
         */
        void Add(const ResourceContainerKeyType& key, Resource& rc) {
            resources_[key] = rc;
        }

        /**
         * @brief		���\�[�X�̎擾
         * @param[in]	key		�L�[
         * @return		�Y�����郊�\�[�X
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
         * @brief		���\�[�X���̎擾
         * @return		���\�[�X��
         */
        size_t GetSize() const { return resources_.size(); }
    };
    template <typename T> using ResourceContainerPtr = std::shared_ptr< ResourceContainer<T> >;
}