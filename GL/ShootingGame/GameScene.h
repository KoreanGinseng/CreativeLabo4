#pragma once
#include "GameDefine.h"
#include "Stage.h"
#include "GameObject.h"

class GameScene : public SceneBase<GameSceneData> {
private:

    Stage stage_;
    std::vector<GameObjectPtr> objects_;

public:
    GameScene(GameSceneData& sceneData);
    virtual ~GameScene();

    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render(sip::RenderCommandTaskPtr& render_task) override;
};

