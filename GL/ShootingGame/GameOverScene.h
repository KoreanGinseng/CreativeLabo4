#pragma once
#include "GameDefine.h"
#include "Include/Input/InputManager.h"

class GameOverScene : public SceneBase<GameSceneData> {
private:

    SpritePtr          sprite_;
    sip::InputPtr      input_;

public:
    GameOverScene(GameSceneData& sceneData);
    virtual ~GameOverScene();

    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render(sip::RenderCommandTaskPtr& render_task) override;
};

