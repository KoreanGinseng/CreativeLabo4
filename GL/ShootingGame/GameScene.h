#pragma once
#include "GameDefine.h"

class GameScene : public SceneBase<GameSceneData> {
private:

public:
    GameScene(GameSceneData& sceneData);
    virtual ~GameScene();

    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render(sip::RenderCommandTaskPtr& render_task) override;
};

