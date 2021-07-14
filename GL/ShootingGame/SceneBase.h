#pragma once
#include "Framework/Common/Common.h"
#include "Include/Render/RenderCommandTask.h"
#include "Include/Common/FrameBuffer.h"
#include "Include/Common/Sprite.h"
#include "Include/Common/GraphicsController.h"
#include "Include/Render/RenderManager.h"

struct EmptyData {};

template<class SceneData = EmptyData>
class SceneBase {
protected:

    SceneData      sceneData_;

public:

    SceneBase(SceneData& sceneData) : sceneData_(sceneData) {
    }

    virtual ~SceneBase() = default;

    virtual void Initialize() = 0;

    virtual void Update() = 0;

    virtual void Render(sip::RenderCommandTaskPtr& render_task) = 0;

    SceneData* GetSceneData() { return &sceneData_; }
    void SetSceneData(SceneData& sceneData) { sceneData_ = sceneData; }
};

template<class SceneData = EmptyData>
using ScenePtr = std::shared_ptr<SceneBase<SceneData>>;