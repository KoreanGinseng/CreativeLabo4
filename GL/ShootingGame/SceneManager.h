#pragma once
#include "Framework/Common/Singleton.h"
#include "SceneBase.h"
#include "Include/Render/RenderCommandTask.h"
#include "Include/Render/RenderFrameBufferBindCommand.h"
#include "Include/Render/RenderResetTargetCommand.h"
#include "Include/Render/RenderClearCommand.h"
#include "Include/Render/SpriteRenderCommand.h"
#include "Include/Common/Math.h"

template<class Key, class SceneData = EmptyData>
class SceneManager : public Sample::Singleton<SceneManager<Key, SceneData>> {
    friend class Sample::Singleton<SceneManager<Key, SceneData>>;
private:

    enum class Transition {
        FadeIn,
        FadeOut,
        Active,
    } transition_;

    int                 timer_;
    int                 transitionFrame_;

    SceneData           sceneData_;

    ScenePtr<SceneData> currentScene_;
    ScenePtr<SceneData> nextScene_;

    FrameBufferPtr      frameBuffer_;
    SpritePtr           frameSprite_;

    Key                 current_;
    Key                 next_;

    using SceneFactory   = std::function<ScenePtr<SceneData>(void)>;
    using SceneFactories = std::unordered_map<Key, SceneFactory>;
    SceneFactories      sceneFactories_;
    sip::Vector4        fadeColor_;

public:

    using Scene = SceneBase<SceneData>;
    template<class Scene>
    void Add(const Key& key) {
        auto factory = sceneFactories_.find(key);
        if (factory == sceneFactories_.end()) {
            sceneFactories_[key] = [=]() { return std::make_shared<Scene>(sceneData_); };
        }
    }

    void ChangeScene(const Key& nextScene, int transitionFrame = 60) {
        next_ = nextScene;
        timer_ = 0;
        transitionFrame_ = transitionFrame;
        auto factory = sceneFactories_.find(next_);
        if (factory == sceneFactories_.end()) {
            nextScene_ = nullptr;
            return;
        }
        nextScene_ = factory->second();
        nextScene_->Initialize();
        transition_ = Transition::FadeOut;
    }

    void FrameBufferCreate() {
        if (!frameBuffer_) {
            frameBuffer_ = std::make_shared<FrameBuffer>();
            frameBuffer_->Create(GraphicsControllerInstance.ScreenWidth(),
                GraphicsControllerInstance.ScreenHeight());
        }
        if (!frameSprite_) {
            frameSprite_ = frameBuffer_->CreateSprite(GraphicsControllerInstance.SpriteShader());
        }
    }


    FrameBufferPtr GetFrameBuffer(void) const {
        return frameBuffer_;
    }

    SpritePtr GetFrameSprite(void) const {
        return frameSprite_;
    }

    void FadeColor(const sip::Vector4& color) {
        fadeColor_ = color;
    }

    sip::Vector4 FadeColor(void) const {
        return fadeColor_;
    }

    void Initialize(const Key& initScene, int transitionFrame = 60) {
        current_ = initScene;
        timer_ = transitionFrame * 0.5f;
        transitionFrame_ = transitionFrame;
        auto factory = sceneFactories_.find(current_);
        if (factory == sceneFactories_.end()) {
            currentScene_ = nullptr;
            return;
        }
        currentScene_ = factory->second();
        currentScene_->Initialize();
        transition_ = Transition::FadeIn;
    }

    void Update() {
        switch (transition_) {
        case Transition::FadeIn:
        {
            timer_++;
            if (transitionFrame_ <= timer_) {
                timer_ = -1;
                transition_ = Transition::Active;
            }
        } return;
        case Transition::FadeOut:
        {
            timer_++;
            if (transitionFrame_ * 0.5f <= timer_) {
                transition_   = Transition::FadeIn;
                current_      = next_;
                currentScene_ = nextScene_;
                nextScene_    = nullptr;
            }
        } return;
        case Transition::Active:
        {
        } break;
        }
        currentScene_->Update();
    }

    void Render(sip::RenderCommandTaskPtr& render_task) {
        float alpha  = 1.0f;
        render_task->Push(sip::GLRenderFrameBufferBindCommand::Create(frameBuffer_), 0);
        switch (transition_) {
        case Transition::FadeIn:
        {
            alpha = (timer_ - transitionFrame_ * 0.5f) / (transitionFrame_ * 0.5f);
        } break;
        case Transition::FadeOut:
        {
            alpha = 1.0f - (timer_ / (transitionFrame_ * 0.5f));
        } break;
        case Transition::Active:
        {
        } break;
        }
        currentScene_->Render(render_task);
        render_task->Push(sip::RenderResetTargetCommand::Create(), 0);
        render_task->Push(sip::RenderClearCommand::Create(fadeColor_.r, fadeColor_.g, fadeColor_.b, 1, 0, 0), 0);
        render_task->Push(sip::SpriteRenderCommand::Create(frameSprite_, alpha), 0);
    }

    const SceneData& GetSceneData(void) const {
        return sceneData_;
    }

    SceneData* GetSceneData(void) {
        return &sceneData_;
    }
};

