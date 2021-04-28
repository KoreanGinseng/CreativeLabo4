#pragma once

#include	"IInput.h"

namespace Sample {

	/**
	 * @brief		���̓N���X
	 */
	class LogInput : public IInput
	{
	protected:
		/** ���̓N���X */
		InputPtr				input_;

		/** �t�@�C���X�g���[�� */
		std::ofstream			file_;

		/**
		 * @brief		���O�̖��O���쐬
		 * @return		���O�̖��O
		 */
		std::string CreateLogName() {
			time_t t = time(nullptr);
			const tm* localTime = localtime(&t);
			std::stringstream s;
			s << "Log/";
			s << std::setw(4) << std::setfill('0') << localTime->tm_year + 1900;
			s << std::setw(2) << std::setfill('0') << localTime->tm_mon + 1;
			s << std::setw(2) << std::setfill('0') << localTime->tm_mday;
			s << std::setw(2) << std::setfill('0') << localTime->tm_hour;
			s << std::setw(2) << std::setfill('0') << localTime->tm_min;
			s << std::setw(2) << std::setfill('0') << localTime->tm_sec;
			s << ".dat";
			return s.str();
		}

		/**
		 * @brief		�t�@�C���ւ̃L�[�o��
		 */
		template < typename T = KeyType >
		void WriteKey(const T& key) {
			unsigned char size = sizeof(key);
			file_.write((char*)&size, 1);
			file_.write((char*)&key, size);
		}

		/**
		 * @brief		�t�@�C���ւ̃L�[�o��
		 */
		template < >
		inline void WriteKey<std::string>(const std::string& key) {
			unsigned char size = (unsigned char)key.size();
			file_.write((char*)&size, 1);
			file_.write(key.c_str(), size);
		}

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		LogInput()
			: input_()
		{
			if (!filesystem::exists("Log"))
			{
				filesystem::create_directory("Log");
			}
			const std::string name = CreateLogName();
			file_.open(name, std::ios::out | std::ios::binary | std::ios::trunc);
		}
		/**
		 * @brief		�f�X�g���N�^
		 */
		~LogInput() {
			file_.close();
		}

		/**
		 * @brief		���͔F���̓o�^
		 */
		template< class T >
		std::shared_ptr<T> CreateInput() {
			auto ptr = std::make_shared<T>();
			input_ = ptr;
			return ptr;
		}

		/**
		 * @brief		�X�V
		 */
		void Update() override {
			input_->Update();

			//���O�ɏo��
			for (auto& type : input_->GetKeyList())
			{
				float v = GetAxis(type);
				if (v != 0)
				{
					WriteKey(type);
					file_.write((char*)&v, sizeof(v));
				}
			}
			unsigned char size = 0xFF;
			file_.write((char*)&size, 1);
		}

		/**
		 * @brief		�w�薼�̂̓o�^�L�[�̓��͒l���擾
		 * @param[in]	kn		�o�^�L�[��
		 * @return		�L�[���͂̒l
		 */
		float GetAxis(const KeyType& kn) const override {
			return input_->GetAxis(kn);
		}

		/**
		 * @brief		�w�薼�̂̓o�^�L�[�����̃t���[���ɉ����ꂽ���ǂ���
		 * @param[in]	kn		�o�^�L�[��
		 * @return		true	���̃t���[���ŉ����ꂽ
		 *				false	���̃t���[���ł͉�����Ă��Ȃ�
		 */
		bool IsPush(const KeyType& kn) const override {
			return input_->IsPush(kn);
		}

		/**
		 * @brief		�w�薼�̂̓o�^�L�[�����̃t���[���ɉ����ꂽ���ǂ���
		 * @param[in]	kn		�o�^�L�[��
		 * @return		true	���̃t���[���ŉ����ꂽ
		 *				false	���̃t���[���ł͉�����Ă��Ȃ�
		 */
		bool IsNegativePush(const KeyType& kn) const override {
			return input_->IsNegativePush(kn);
		}

		/**
		 * @brief		�w�薼�̂̓o�^�L�[�����̃t���[���ɗ����ꂽ���ǂ���
		 * @param[in]	kn		�o�^�L�[��
		 * @return		true	���̃t���[���ŗ����ꂽ
		 *				false	���̃t���[���ł͗�����Ă��Ȃ�
		 */
		bool IsPull(const KeyType& kn) const override {
			return input_->IsPull(kn);
		}

		/**
		 * @brief		�w�薼�̂̓o�^�L�[�����̃t���[���ɗ����ꂽ���ǂ���
		 * @param[in]	kn		�o�^�L�[��
		 * @return		true	���̃t���[���ŗ����ꂽ
		 *				false	���̃t���[���ł͗�����Ă��Ȃ�
		 */
		bool IsNegativePull(const KeyType& kn) const override {
			return input_->IsNegativePull(kn);
		}

		/**
		 * @brief		�w�薼�̂̓o�^�L�[��������Ă��邩�ǂ���
		 * @param[in]	kn		�o�^�L�[��
		 * @return		true	���̃t���[���ŉ�����Ă���
		 *				false	���̃t���[���ŉ�����Ă��Ȃ�
		 */
		bool IsPress(const KeyType& kn) const override {
			return input_->IsPress(kn);
		}

		/**
		 * @brief		�w�薼�̂̓o�^�L�[��������Ă��邩�ǂ���
		 * @param[in]	kn		�o�^�L�[��
		 * @return		true	���̃t���[���ŉ�����Ă���
		 *				false	���̃t���[���ŉ�����Ă��Ȃ�
		 */
		bool IsNegativePress(const KeyType& kn) const override {
			return input_->IsNegativePress(kn);
		}

		/**
		 * @brief		�o�^����Ă���L�[�z��
		 * @return		�L�[�̎��ʔz��
		 */
		std::vector<KeyType> GetKeyList() const override {
			return input_->GetKeyList();
		}
	};

}