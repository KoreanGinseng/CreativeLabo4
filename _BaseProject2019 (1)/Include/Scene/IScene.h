#pragma once

#include "../Common/Common.h"
#include "../Render/RenderManager.h"

namespace sip {

    struct SceneData {};

    using SceneDataPtr = std::shared_ptr<SceneData>;

    /**
    * @bref シーンインターフェース
    */
    class __declspec(novtable) IScene {
    public:

        using KeyType      = std::string;

        struct InitData {
            KeyType      keyType;
            SceneDataPtr sceneData;
        };

        /**
        * @bref デストラクタ
        */
        virtual ~IScene() = default;

        /**
        * @bref 更新処理
        */
        virtual void Update() = 0;

        /**
        * @bref 描画処理
        */
        virtual void Render(RenderCommandTaskPtr& render_task) = 0;

        /**
        * @bref キーの取得
        */
        virtual const KeyType& GetKey() const = 0;

        /**
        * @bref 共有データの取得
        */
        virtual SceneDataPtr& GetData() = 0;
    };

    using ScenePtr = std::shared_ptr<IScene>;
}