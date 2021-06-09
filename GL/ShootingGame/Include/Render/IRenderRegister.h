#pragma once

#include    "RenderCommandTask.h"

namespace sip {

    /**
     * @brief        描画コマンド
     */
    class __declspec(novtable) IRenderRegister {
    public:
        /**
         * @brief        デストラクタ
         */
        virtual ~IRenderRegister() = default;

        /**
         * @brief        登録
         */
        virtual void Register(sip::RenderCommandTaskPtr& task) = 0;
    };
    //ポインタ置き換え
    using RenderRegisterPtr = std::shared_ptr<IRenderRegister>;
    using RenderRegisterList = std::vector<RenderRegisterPtr>;

}