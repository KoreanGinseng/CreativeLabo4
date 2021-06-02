#pragma once

#include "../Common/Common.h"
#include "../Render/RenderManager.h"

namespace sip {

    struct SceneData {};

    using SceneDataPtr = std::shared_ptr<SceneData>;

    /**
    * @bref �V�[���C���^�[�t�F�[�X
    */
    class __declspec(novtable) IScene {
    public:

        using KeyType      = std::string;

        struct InitData {
            KeyType      keyType;
            SceneDataPtr sceneData;
        };

        /**
        * @bref �f�X�g���N�^
        */
        virtual ~IScene() = default;

        /**
        * @bref �X�V����
        */
        virtual void Update() = 0;

        /**
        * @bref �`�揈��
        */
        virtual void Render(RenderCommandTaskPtr& render_task) = 0;

        /**
        * @bref �L�[�̎擾
        */
        virtual const KeyType& GetKey() const = 0;

        /**
        * @bref ���L�f�[�^�̎擾
        */
        virtual SceneDataPtr& GetData() = 0;
    };

    using ScenePtr = std::shared_ptr<IScene>;
}