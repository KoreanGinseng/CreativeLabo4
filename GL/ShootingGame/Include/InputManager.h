#pragma once

#include	"Input.h"
#include	"../Framework/Common/Singleton.h"

namespace sip {

    /**
     * @brief		インプットマネージャー
     */
    class InputManager : public Sample::Singleton<InputManager> {
        friend class Sample::Singleton<InputManager>;
    private:
        /** 入力リスト */
        InputList			inputList_;
        /**
         * @brief		コンストラクタ
         */
        InputManager()
            : Sample::Singleton<InputManager>()
            , inputList_() {
        }
    public:

        /**
         * @brief		新規入力認識の追加
         */
        template< class T >
        std::shared_ptr<T> AddInput() {
            auto add = std::make_shared<T>();
            inputList_.push_back(add);
            return add;
        }

        /**
         * @brief		新規入力認識の追加
         */
        template < typename T, typename... _Types >
        std::shared_ptr<T> AddInput(_Types&& ... _Args) {
            auto add = std::make_shared<T>(_Args...);
            inputList_.push_back(add);
            return add;
        }

        /**
         * @brief		更新
         */
        void Update() {
            for (auto& input : inputList_) { input->Update(); }
        }

        /**
         * @brief		入力の取得
         */
        InputPtr& GetInput(int id) { return inputList_[id]; }

    };
}
//簡易アクセス用
#define InputManagerInstance	sip::InputManager::GetInstance()
