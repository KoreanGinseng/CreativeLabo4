#pragma once

#include "IScene.h"
#include "../Common/Singleton.h"

namespace sip {

    template<class Data = SceneData>
    class SceneManager : public Singleton<SceneManager> {
    private:

        using FactoryFunc = std::function<ScenePtr()>;

        using FactoryMap = std::unordered_map<IScene::KeyType, FactoryFunc>;

        FactoryMap                       factories_;
        SceneDataPtr                     sceneData_;
                                         
        ScenePtr                         currentScene_;
        ScenePtr                         nextScene_;
                                         
        IScene::KeyType                  currentState_;
        IScene::KeyType                  nextState_;

        std::shared_ptr<IScene::KeyType> firstState_;

        enum class Transition {
            None,
            FadeIn,
            Active,
            FadeOut,
        } transitionState_;

        float                            timer_;
        bool                             timerFlag_;
        float                            transition_;

        void UpdateSingle() {
            if (timerFlag_) {
                timer_ += 0.017f;
            }
            if (transitionState_ == Transition::FadeOut && timer_ >= transition_) {
                currentScene_    = nullptr;
                currentScene_    = factories_[nextState_]();
                currentState_    = nextState_;
                transitionState_ = Transition::FadeIn;
                timer_           = 0.0f;
            }
            if (transitionState_ == Transition::FadeIn && timer_ >= transition_) {
                timer_           = 0.0f;
                transitionState_ = Transition::Active;
            }
            switch (transitionState_) {
            case Transition::FadeIn:
                assert(transition_);
                break;
            case Transition::FadeOut:
                assert(transition_);
                break;
            case Transition::Active:
                currentScene_->Update();
                break;
            default:
                break;
            }
        }

    public:

        SceneManager() 
            : sceneData_(std::make_shared<Data>())
            , factories_()
            , currentScene_(nullptr)
            , nextScene_(nullptr)
            , firstState_(nullptr)
            , transitionState_(Transition::None) 
            , timer_(0.0f) 
            , timerFlag_(false)
            , transition_(1.0f) {
        }

        SceneManager(std::shared_ptr<Data>& data) 
            : sceneData_(data)
            , factories_()
            , currentScene_(nullptr)
            , nextScene_(nullptr)
            , firstState_(nullptr)
            , transitionState_(Transition::None) 
            , timer_(0.0f) 
            , timerFlag_(false)
            , transition_(1.0f) {
        }

        template<class IScene>
        void AddScene(const IScene::KeyType& keyType) {
            typename IScene::InitData initData{ keyType, sceneData_ };
            FactoryFunc factory = [=] {
                return std::make_shared<IScene>(initData);
            };
            auto it = factories_.find(keyType);
            if (it != factories_.end()) {
                factories_[keyType] = factory;
            }
            else {
                factories_.emplace(keyType, factory);
                if (!firstState_) {
                    firstState_ = std::make_shared<IScene::KeyType>();
                    *(firstState_.get()) = keyType;
                }
            }
        }

        void Initialize(const IScene::KeyType& keyType) {
            if (currentScene_) {
                return;
            }
            auto it = factories_.find(keyType);
            if (it == factories_.end()) {
                return;
            }
            currentState_    = keyType;
            currentScene_    = it->second();
            transitionState_ = Transition::FadeIn;
            timer_           = 0.0f;
            timerFlag_       = true;
        }

        void UpdateScene() {
            if (!currentScene_) {
                if (firstState_) {
                    return;
                }
                else if ((!Initialize(*firstState_.get())) {
                    return;
                }
            }
            UpdateSingle();
        }

        void RenderScene() {
            if (transitionState_ == Transition::Active || !transition_) {
                currentScene_->Render();
            }
            if (transitionState_ == Transition::FadeIn) {

            }
            else if (transitionState_ == Transition::FadeOut) {

            }
        }

        void ChangeScene(const IScene::KeyType& keyType, float transition = 1.0f) {

        }
    };
}