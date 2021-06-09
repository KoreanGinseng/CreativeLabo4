#pragma once

#include    "RenderCommandTask.h"
#include    "RenderStartCommand.h"
#include    "RenderEndCommand.h"
#include    "../../Framework/Common/Singleton.h"

namespace sip {

    /**
     * @brief        �`��Ǘ�
     */
    class RenderManager : public Sample::Singleton<RenderManager> {
        friend class Sample::Singleton<RenderManager>;
    public:
        /** �ߋ��̎��s�L���[�ۑ��� */
        static const int ExecutedQueueCount = 60;

    private:

        /** �`��L���[ */
        RenderCommandTaskQueue        queue_;
        /** �ߋ��̕`��L���[ */
        RenderCommandTaskList        executedTask_;
        /** ���b�N */
        std::mutex                    lock_;
        /** �X���b�h */
        std::thread                    thread_;
        /** ���s�t���O */
        bool                        run_;

        /**
         * @brief        �R���X�g���N�^
         */
        RenderManager()
            : Sample::Singleton<RenderManager>()
            , queue_()
            , executedTask_()
            , lock_()
            , thread_()
            , run_(true) {
            thread_ = std::thread([this] { Exec(); });
            executedTask_.reserve(ExecutedQueueCount);
        }
        /**
         * @brief        �f�X�g���N�^
         */
        ~RenderManager() {
            run_ = false;
            thread_.join();
        }

        /**
         * @brief        �`��X���b�h
         */
        void Exec() {
            while (run_) {
                //�^�X�N�����o��
                RenderCommandTaskPtr task = Pop();
                if (!task) {
                    //�^�X�N���Ȃ��̂őҋ@
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                    continue;
                }
                //���s
                task->Exec();
            }
        }

        /**
         * @brief        �^�X�N�̎��o��
         */
        RenderCommandTaskPtr Pop() {
            std::lock_guard<std::mutex> guard(lock_);
            if (queue_.size() <= 0) {
                return RenderCommandTaskPtr();
            }
            RenderCommandTaskPtr re = queue_.front();
            queue_.pop();
            //�ߋ��̎��s�L���[�Ƃ��ĕۑ�
            while (executedTask_.size() >= ExecutedQueueCount) {
                executedTask_.erase(executedTask_.begin());
            }
            executedTask_.push_back(re);
            return re;
        }
    public:

        /**
         * @brief        �^�X�N�̐���
         */
        template< typename T, typename... Args >
        static std::shared_ptr<T> CreateTask(Args&& ... _Args) {
            auto task = std::make_shared< T >(_Args...);
            task->Push(sip::RenderStartCommand::Create(), 0);
            return task;
        }

        /**
         * @brief        �^�X�N�̒ǉ�
         */
        void Push(const RenderCommandTaskPtr& task) {
            task->Push(sip::RenderEndCommand::Create(), task->GetLayerCount() - 1);
            std::lock_guard<std::mutex> guard(lock_);
            queue_.push(task);
        }

        /**
         * @brief        �ߋ��^�X�N�̎��o��
         */
        RenderCommandTaskPtr GetExecutedTask(int cnt) {
            std::lock_guard<std::mutex> guard(lock_);
            if (executedTask_.size() <= cnt) {
                return RenderCommandTaskPtr();
            }
            return *(executedTask_.rbegin() + cnt);
        }
    };

}
//�ȈՃA�N�Z�X�p
#define RenderManagerInstance    sip::RenderManager::GetInstance()