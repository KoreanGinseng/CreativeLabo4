#pragma once

#include    "../Common/ICommand.h"

namespace sip {

    /**
     * @brief        �`��R�}���h
     */
    class __declspec(novtable) IRenderCommand : public ICommand {
    public:
    };
    //�|�C���^�u������
    using RenderCommandPtr = std::shared_ptr<IRenderCommand>;
    using RenderCommandList = std::vector<RenderCommandPtr>;

}