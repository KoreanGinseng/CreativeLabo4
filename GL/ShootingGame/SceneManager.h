#pragma once
#include "Framework/Common/Singleton.h"
#include "SceneBase.h"

template<class Key, class SceneData = EmptyData>
class SceneManager : public Sample::Singleton<SceneManager> {
private:

    enum class Transition {
        FadeIn,
        FadeOut,
        Active,
    } transition_;

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

    void ChangeScene(const Key& nextScene, float tlansition = 1.0f) {
        next_ = nextScene;
        auto factory = sceneFactories_.find(next_);
        if (factory == sceneFactories_.end()) {
            nextScene_ = nullptr;
            return;
        }
        nextScene_ = factory();
    }
};
