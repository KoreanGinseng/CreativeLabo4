#pragma once

#include    "../../Framework/Common/Common.h"

namespace sip {
    /**
     * @brief        ���̓C���^�[�t�F�C�X
     */
    class __declspec(novtable) IInput {
    public:
        //�L�[
        using KeyType = std::string;

        /**
         * @brief        �f�X�g���N�^
         */
        virtual ~IInput() = default;

        /**
         * @brief        �X�V
         */
        virtual void Update() = 0;

        /**
         * @brief        �w�薼�̂̓o�^�L�[�̓��͒l���擾
         * @param[in]    kn        �o�^�L�[��
         * @return        �L�[���͂̒l
         */
        virtual float GetAxis(const KeyType& kn) const = 0;

        /**
         * @brief        �w�薼�̂̓o�^�L�[�����̃t���[���ɉ����ꂽ���ǂ���
         * @param[in]    kn        �o�^�L�[��
         * @return        true    ���̃t���[���ŉ����ꂽ
         *                false    ���̃t���[���ł͉�����Ă��Ȃ�
         */
        virtual bool IsPush(const KeyType& kn) const = 0;

        /**
         * @brief        �w�薼�̂̓o�^�L�[�����̃t���[���ɉ����ꂽ���ǂ���
         * @param[in]    kn        �o�^�L�[��
         * @return        true    ���̃t���[���ŉ����ꂽ
         *                false    ���̃t���[���ł͉�����Ă��Ȃ�
         */
        virtual bool IsNegativePush(const KeyType& kn) const = 0;

        /**
         * @brief        �w�薼�̂̓o�^�L�[�����̃t���[���ɗ����ꂽ���ǂ���
         * @param[in]    kn        �o�^�L�[��
         * @return        true    ���̃t���[���ŗ����ꂽ
         *                false    ���̃t���[���ł͗�����Ă��Ȃ�
         */
        virtual bool IsPull(const KeyType& kn) const = 0;

        /**
         * @brief        �w�薼�̂̓o�^�L�[�����̃t���[���ɗ����ꂽ���ǂ���
         * @param[in]    kn        �o�^�L�[��
         * @return        true    ���̃t���[���ŗ����ꂽ
         *                false    ���̃t���[���ł͗�����Ă��Ȃ�
         */
        virtual bool IsNegativePull(const KeyType& kn) const = 0;

        /**
         * @brief        �w�薼�̂̓o�^�L�[��������Ă��邩�ǂ���
         * @param[in]    kn        �o�^�L�[��
         * @return        true    ���̃t���[���ŉ�����Ă���
         *                false    ���̃t���[���ŉ�����Ă��Ȃ�
         */
        virtual bool IsPress(const KeyType& kn) const = 0;

        /**
         * @brief        �w�薼�̂̓o�^�L�[��������Ă��邩�ǂ���
         * @param[in]    kn        �o�^�L�[��
         * @return        true    ���̃t���[���ŉ�����Ă���
         *                false    ���̃t���[���ŉ�����Ă��Ȃ�
         */
        virtual bool IsNegativePress(const KeyType& kn) const = 0;

        /**
         * @brief        �o�^����Ă���L�[�z��
         * @return        �L�[�̎��ʔz��
         */
        virtual std::vector<KeyType> GetKeyList() const = 0;
    };
    //�|�C���^�u������
    using InputPtr = std::shared_ptr<IInput>;
    using InputList = std::vector<InputPtr>;

}