#pragma once
#include "Framework/Common/Common.h"
#include "Include/Render/RenderCommandTask.h"

struct EmptyData {};

template<class SceneData = EmptyData>
class SceneBase {
protected:

    SceneData sceneData_;

public:

    SceneBase(SceneData& sceneData) : sceneData_(sceneData) {}

    virtual ~SceneBase() = default;

    virtual void Initialize() = 0;

    virtual void Update() = 0;

    virtual void Render(sip::RenderCommandTask& render_task) = 0;

    SceneData* SceneData() { return &sceneData_; }
    void SceneData(SceneData& sceneData) { sceneData_ = sceneData; }
};

template<class SceneData = EmptyData>
using ScenePtr = std::shared_ptr<SceneBase<SceneData>>;