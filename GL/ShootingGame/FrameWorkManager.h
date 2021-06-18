#pragma once
#include "Framework/Common/Common.h"
#include "Framework/Common/Singleton.h"
#include "Framework/Framework/Framework.h"

/**
* @brief        フレームワーク管理
*/
class FrameWorkManager : public Sample::Singleton<FrameWorkManager> {
    friend class Sample::Singleton<FrameWorkManager>;

    /** フレームワークポインタ */
    Sample::Framework* framework_{ nullptr };

public:

    /**
    * @brief         ウィンドウの取得
    */
    GLFWwindow* GetWindow() {
        if(framework_) return framework_->GetWindow();
        return nullptr;
    }

    int GetWindowWidth() const {
        if (framework_) return framework_->GetWindowWidth();
        return 0;
    }

    int GetWindowHeight() const {
        if (framework_) return framework_->GetWindowHeight();
        return 0;
    }

    /**
    * @brief         フレームワークの設定
    * @param[in]     framework     フレームワークポインタ
    */
    void SetFramework(Sample::Framework* framework) {
        framework_ = framework;
    }
};
//簡易アクセス用
#define FrameWorkManagerInstance FrameWorkManager::GetInstance()