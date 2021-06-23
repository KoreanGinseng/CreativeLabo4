#pragma once
#include "GameDefine.h"

class TitleScene : public SceneBase<GameSceneData> {
private:

    Sample::TexturePtr texture_;
    SpritePtr          sprite_;

public:
    TitleScene(GameSceneData& sceneData);
    virtual ~TitleScene();

    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render(sip::RenderCommandTask& render_task) override;
};