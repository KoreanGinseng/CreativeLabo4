#pragma once

#include    "RenderCommandTask.h"

namespace sip {

    /**
     * @brief        �`��R�}���h
     */
    class __declspec(novtable) IRenderRegister {
    public:
        /**
         * @brief        �f�X�g���N�^
         */
        virtual ~IRenderRegister() = default;

        /**
         * @brief        �o�^
         */
        virtual void Register(sip::RenderCommandTaskPtr& task) = 0;
    };
    //�|�C���^�u������
    using RenderRegisterPtr = std::shared_ptr<IRenderRegister>;
    using RenderRegisterList = std::vector<RenderRegisterPtr>;

}