#pragma once
#include "GameDefine.h"
#include "Include/Input/InputManager.h"

class GameClearScene : public SceneBase<GameSceneData> {
private:

    SpritePtr          sprite_;
    sip::InputPtr      input_;

public:
    GameClearScene(GameSceneData& sceneData);
    virtual ~GameClearScene();

    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render(sip::RenderCommandTaskPtr& render_task) override;
};

