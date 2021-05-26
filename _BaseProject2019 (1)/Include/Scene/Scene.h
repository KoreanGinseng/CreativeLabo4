#pragma once

#include "IScene.h"

namespace sip {

    class Scene : public IScene {
    protected:

        KeyType      keyType_;
        SceneDataPtr sceneData_;

    public:

        Scene(IScene::InitData& init)
            : keyType_(init.keyType)
            , sceneData_(init.sceneData) {
        }

        /**
        * @bref �f�X�g���N�^
        */
        virtual ~Scene() override = default;

        /**
        * @bref �X�V����
        */
        virtual void Update() override {}

        /**
        * @bref �`�揈��
        */
        virtual void Render() override {}

        /**
        * @bref �L�[�̎擾
        */
        virtual const KeyType& GetKey() const override { return keyType_; }

        /**
        * @bref ���L�f�[�^�̎擾
        */
        virtual SceneDataPtr& GetData() override { return sceneData_; }

    };
}