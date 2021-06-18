#pragma once
#include "Framework/Common/Common.h"
#include "Framework/Common/Singleton.h"
#include "Framework/Framework/Framework.h"

/**
* @brief        �t���[�����[�N�Ǘ�
*/
class FrameWorkManager : public Sample::Singleton<FrameWorkManager> {
    friend class Sample::Singleton<FrameWorkManager>;

    /** �t���[�����[�N�|�C���^ */
    Sample::Framework* framework_{ nullptr };

public:

    /**
    * @brief         �E�B���h�E�̎擾
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
    * @brief         �t���[�����[�N�̐ݒ�
    * @param[in]     framework     �t���[�����[�N�|�C���^
    */
    void SetFramework(Sample::Framework* framework) {
        framework_ = framework;
    }
};
//�ȈՃA�N�Z�X�p
#define FrameWorkManagerInstance FrameWorkManager::GetInstance()