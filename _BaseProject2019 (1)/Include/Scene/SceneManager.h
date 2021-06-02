#pragma once

#include "IScene.h"
#include "../Common/Singleton.h"
#include "../Render/FillRectRenderCommand.h"
#include "../Render/RenderManager.h"

namespace sip {

    template<class Data = SceneData>
    class SceneManager : public Singleton<SceneManager<Data>> {
    private:

        using KeyType = IScene::KeyType;

        using FactoryFunc = std::function<ScenePtr()>;

        using FactoryMap = std::unordered_map<IScene::KeyType, FactoryFunc>;

        using SceneDataPtr_t = std::shared_ptr<Data>;

        FactoryMap                       factories_;
        SceneDataPtr_t                   sceneData_;
                                         
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
        unsigned int                     fadeColor_;

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
            , transition_(1.0f) 
            , fadeColor_(0) {
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
            , transition_(1.0f)
            , fadeColor_(0) {
        }

        template<class T>
        void AddScene(const KeyType& keyType) {
            typename T::InitData initData{ keyType, sceneData_ };
            FactoryFunc factory = [=] {
                return std::make_shared<T>(initData);
            };
            auto it = factories_.find(keyType);
            if (it != factories_.end()) {
                factories_[keyType] = factory;
            }
            else {
                factories_.emplace(keyType, factory);
                if (!firstState_) {
                    firstState_ = std::make_shared<KeyType>();
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
                Initialize(*(firstState_.get()));
            }
            UpdateSingle();
        }

        void RenderScene(RenderCommandTaskPtr& render_task) {
            if (transitionState_ == Transition::Active || !transition_) {
                currentScene_->Render(render_task);
            }
            if (transitionState_ == Transition::FadeIn) {
                currentScene_->Render(render_task);
                unsigned char alpha = (1.0f - (timer_ / transition_)) * 255;
                unsigned int  color = fadeColor_;
                color &= 0x00FFFFFF;
                color |= alpha << 24;
                Rectangle rect(0, 0, window_width, window_height);
                render_task->Push(std::make_shared<detail::FillRectRenderCommand>(rect, color), 0);
            }
            else if (transitionState_ == Transition::FadeOut) {
                currentScene_->Render(render_task);
                unsigned char alpha = (timer_ / transition_) * 255;
                unsigned int  color = fadeColor_;
                color &= 0x00FFFFFF;
                color |= alpha << 24;
                Rectangle rect(0, 0, window_width, window_height);
                render_task->Push(std::make_shared<detail::FillRectRenderCommand>(rect, color), 0);
            }
        }

        void Update() {
            UpdateScene();
        }

        void Render(RenderCommandTaskPtr& render_task) {
            RenderScene(render_task);
        }

        SceneDataPtr_t GetData() {
            return sceneData_;
        }

        const SceneDataPtr_t GetData() const {
            return sceneData_;
        }

        void ChangeScene(const IScene::KeyType& keyType, float transition = 1.0f) {
            if (factories_.find(keyType) == factories_.end()) {
                return;
            }
            nextState_ = keyType;
            transition_ = transition * 0.5f;
            transitionState_ = Transition::FadeOut;
            timer_ = 0.0f;
            timerFlag_ = true;
        }

        void SetFadeColor(unsigned int color) {
            fadeColor_ = color;
        }

        unsigned int GetFadeColor() const {
            return fadeColor_;
        }
    };
}