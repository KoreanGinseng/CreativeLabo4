#pragma once
#include "Framework/Common/Common.h"
#include "Include/Render/RenderCommandTask.h"
#include "Include/Common/FrameBuffer.h"
#include "Include/Common/Sprite.h"
#include "Include/Common/GraphicsController.h"

struct EmptyData {};

template<class SceneData = EmptyData>
class SceneBase {
protected:

    SceneData      sceneData_;
    FrameBufferPtr frameBuffer_;
    SpritePtr      frameSprite_;

public:

    SceneBase(SceneData& sceneData) : sceneData_(sceneData) {
        //フレームバッファ生成
        frameBuffer_ = std::make_shared<FrameBuffer>();
        frameBuffer_->Create(GraphicsControllerInstance.ScreenWidth(),
            GraphicsControllerInstance.ScreenHeight());
        frameSprite_ = frameBuffer_->CreateSprite(GraphicsControllerInstance.SpriteShader());
    }

    virtual ~SceneBase() = default;

    virtual void Initialize() = 0;

    virtual void Update() = 0;

    virtual void Render(sip::RenderCommandTask& render_task) = 0;

    SceneData* GetSceneData() { return &sceneData_; }
    void SetSceneData(SceneData& sceneData) { sceneData_ = sceneData; }
    FrameBufferPtr GetFrameBuffer() { return frameBuffer_; }
    SpritePtr GetFrameSprite() { return frameSprite_; }
};

template<class SceneData = EmptyData>
using ScenePtr = std::shared_ptr<SceneBase<SceneData>>;