#pragma once

#include    "RenderCommandTask.h"
#include    "RenderStartCommand.h"
#include    "RenderEndCommand.h"
#include    "../../Framework/Common/Singleton.h"
#include    "../../FrameWorkManager.h"

namespace sip {

    /**
     * @brief        描画管理
     */
    class RenderManager : public Sample::Singleton<RenderManager> {
        friend class Sample::Singleton<RenderManager>;
    public:
        /** 過去の実行キュー保存数 */
        static const int ExecutedQueueCount = 60;

    private:

        /** 描画キュー */
        RenderCommandTaskQueue       queue_;
        /** 過去の描画キュー */
        RenderCommandTaskList        executedTask_;
        /** ロック */
        std::mutex                   lock_;
        /** スレッド */
        std::thread                  thread_;
        /** 実行フラグ */
        bool                         run_;
        
        bool                         context_;

        bool                         set_context_;

        /**
         * @brief        コンストラクタ
         */
        RenderManager()
            : Sample::Singleton<RenderManager>()
            , queue_()
            , executedTask_()
            , lock_()
            , thread_()
            , run_(true)
            , set_context_(true)
            , context_(false) {
            thread_ = std::thread([this] { Exec(); });
            executedTask_.reserve(ExecutedQueueCount);
        }
        /**
         * @brief        デストラクタ
         */
        ~RenderManager() {
            run_ = false;
            thread_.join();
        }

        /**
         * @brief        描画スレッド
         */
        void Exec() {
            while (run_) {
                if (!context_) {
                    if (set_context_) {
                        continue;
                    }
                    SetContext(false);
                    set_context_ = true;
                }
                else if (!set_context_) {
                    SetContext(true);
                    set_context_ = true;
                }
                //タスクを取り出し
                RenderCommandTaskPtr task = Pop();
                if (!task) {
                    //タスクがないので待機
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                    continue;
                }
                //実行
                task->Exec();
            }
        }

        /**
         * @brief        タスクの取り出し
         */
        RenderCommandTaskPtr Pop() {
            std::lock_guard<std::mutex> guard(lock_);
            if (queue_.size() <= 0) {
                return RenderCommandTaskPtr();
            }
            RenderCommandTaskPtr re = queue_.front();
            queue_.pop();
            //過去の実行キューとして保存
            while (executedTask_.size() >= ExecutedQueueCount) {
                executedTask_.erase(executedTask_.begin());
            }
            executedTask_.push_back(re);
            return re;
        }
    public:

        /**
         * @brief        タスクの生成
         */
        template< typename T, typename... Args >
        static std::shared_ptr<T> CreateTask(Args&& ... _Args) {
            auto task = std::make_shared< T >(_Args...);
            task->Push(sip::RenderStartCommand::Create(), 0);
            return task;
        }

        /**
         * @brief        タスクの追加
         */
        void Push(const RenderCommandTaskPtr& task) {
            task->Push(sip::RenderEndCommand::Create(), task->GetLayerCount() - 1);
            std::lock_guard<std::mutex> guard(lock_);
            queue_.push(task);
        }

        /**
         * @brief        過去タスクの取り出し
         */
        RenderCommandTaskPtr GetExecutedTask(int cnt) {
            std::lock_guard<std::mutex> guard(lock_);
            if (executedTask_.size() <= cnt) {
                return RenderCommandTaskPtr();
            }
            return *(executedTask_.rbegin() + cnt);
        }

        void SetThreadContext(bool b) {
            set_context_ = false;
            context_ = b;
        }

        bool IsUseContext() const {
            return context_;
        }

        bool IsActiveContext() const {
            return set_context_;
        }

        static void SetContext(bool b, GLFWwindow* pointer = nullptr) {
            GLFWwindow* window = (b ? FrameWorkManagerInstance.GetWindow() : nullptr);
            if (b && pointer) window = pointer;
            glfwMakeContextCurrent(window);
        }
    };

}
//簡易アクセス用
#define RenderManagerInstance    sip::RenderManager::GetInstance()