#pragma once
#include "Framework/Common/Common.h"
#include "Include/Render/RenderCommandTask.h"

class GameScene {
private:

public:

    GameScene();

    ~GameScene();

    virtual void Initialize();

    virtual void Update();

    virtual void Render(sip::RenderCommandTask& render_task);
};

