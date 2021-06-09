#pragma once
#include "RenderEndCommand.h"

#ifdef __GLLIB
#include "../../Framework/Framework/Framework.h"
#include "../../FrameWorkManager.h"

namespace sip {

    class GLRenderEndCommand : public RenderEndCommand {
    private:
        GLFWwindow* window_;
    public:
        GLRenderEndCommand(GLFWwindow* window);
        void Exec() override;
    };

    inline RenderCommandPtr RenderEndCommand::Create() {
        auto window = FrameWorkManagerInstance.GetWindow();
        return std::make_shared< GLRenderEndCommand >(window);
    }
}

#endif