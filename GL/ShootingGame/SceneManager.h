#pragma once
#include "Framework/Common/Singleton.h"
#include "SceneBase.h"
#include "Include/Render/RenderCommandTask.h"

template<class Key, class SceneData = EmptyData>
class SceneManager : public Sample::Singleton<SceneManager> {
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

    Key                 current_;
    Key                 next_;

    using SceneFactory   = std::function<ScenePtr<SceneData>()>;
    using SceneFactories = std::unordered_map<Key, SceneFactory>;
    SceneFactories      sceneFactories_;

public:

    using Scene = SceneBase<SceneData>;
    template<class Scene>
    void Add(const Key& key) {
        auto factory = sceneFactories_.find(key);
        if (factory == sceneFactories_.end()) {
            sceneFactories_[key] = [=]() { return std::make_shared<Scene>(sceneData_); }
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
        nextScene_ = factory();
        transition_ = Transition::FadeOut;
    }

    void Initialize(const Key& initScene, int transitionFrame = 60) {
        current_ = initScene;
        timer_ = 0;
        transitionFrame_ = transitionFrame;
        auto factory = sceneFactories_.find(current_);
        if (factory == sceneFactories_.end()) {
            currentScene_ = nullptr;
            return;
        }
        currentScene_ = factory();
        transition_ = Transition::FadeIn;
    }

    void Update() {
        switch (transition_) {
        case Transition::FadeIn:
        {
            timer_++;
            if (transitionFrame_ >= timer_) {
                timer_ = -1;
                transition_ = Transition::Active;
            }
        } break;
        case Transition::FadeOut:
        {
            timer_++;
            if (transitionFrame_ * 0.5f >= timer_) {
                transition_ = Transition::FadeIn;
            }
        } break;
        case Transition::Active:
        {
            currentScene_->Update();
        } break;
        }
    }

    void Render(sip::RenderCommandTaskPtr& render_task) {

    }
};

