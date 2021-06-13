#pragma once

#include    "../../Framework/Common/Common.h"

namespace sip {
    /**
        * @brief        �`��R�}���h
        */
    class __declspec(novtable) ICommand {
    public:
        /**
            * @brief        �f�X�g���N�^
            */
        virtual ~ICommand() = default;

        /**
            * @brief        ���s
            */
        virtual void Exec() = 0;
    };
    //�|�C���^�u������
    using CommandPtr = std::shared_ptr<ICommand>;
    using CommandList = std::vector<CommandPtr>;
}