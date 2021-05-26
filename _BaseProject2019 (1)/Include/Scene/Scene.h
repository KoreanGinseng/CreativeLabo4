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
        * @bref デストラクタ
        */
        virtual ~Scene() override = default;

        /**
        * @bref 更新処理
        */
        virtual void Update() override {}

        /**
        * @bref 描画処理
        */
        virtual void Render() override {}

        /**
        * @bref キーの取得
        */
        virtual const KeyType& GetKey() const override { return keyType_; }

        /**
        * @bref 共有データの取得
        */
        virtual SceneDataPtr& GetData() override { return sceneData_; }

    };
}