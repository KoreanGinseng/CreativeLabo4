#pragma once
#include "RenderManager.h"
/*
namespace sip {
    class ContextGuard {
    private:
        bool        skip_;
        GLFWwindow* window_;
    public:
        
        ContextGuard(GLFWwindow* window = nullptr) : skip_(false), window_(window) {
            lock();
        }

        ~ContextGuard() {
            release();
        }

        void lock() {
            RenderManagerInstance.SetThreadContext(false);
            while (!RenderManagerInstance.IsActiveContext()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
            sip::RenderManager::SetContext(true, window_);
        }

        void release() {
            sip::RenderManager::SetContext(false);
            if (!RenderManagerInstance.IsUseContext()) {
                RenderManagerInstance.SetThreadContext(true);
            }
        }
    };
}
*/