#pragma once

#include    "../../Framework/Common/Common.h"

namespace sip {
    /**
        * @brief        描画コマンド
        */
    class __declspec(novtable) ICommand {
    public:
        /**
            * @brief        デストラクタ
            */
        virtual ~ICommand() = default;

        /**
            * @brief        実行
            */
        virtual void Exec() = 0;
    };
    //ポインタ置き換え
    using CommandPtr = std::shared_ptr<ICommand>;
    using CommandList = std::vector<CommandPtr>;
}
