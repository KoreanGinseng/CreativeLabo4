#pragma once
#include "GameDefine.h"
#include "Include/Input/InputManager.h"

class TitleScene : public SceneBase<GameSceneData> {
private:

    SpritePtr          sprite_;
    sip::InputPtr      input_;

public:
    TitleScene(GameSceneData& sceneData);
    virtual ~TitleScene();

    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render(sip::RenderCommandTaskPtr& render_task) override;
};