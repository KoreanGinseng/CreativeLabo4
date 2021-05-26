#pragma once

#include	"IInput.h"

namespace Sample {

	/**
	 * @brief		入力クラス
	 */
	class LogInput : public IInput
	{
	protected:
		/** 入力クラス */
		InputPtr				input_;

		/** ファイルストリーム */
		std::ofstream			file_;

		/**
		 * @brief		ログの名前を作成
		 * @return		ログの名前
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
		 * @brief		ファイルへのキー出力
		 */
		template < typename T = KeyType >
		void WriteKey(const T& key) {
			unsigned char size = sizeof(key);
			file_.write((char*)&size, 1);
			file_.write((char*)&key, size);
		}

		/**
		 * @brief		ファイルへのキー出力
		 */
		template < >
		inline void WriteKey<std::string>(const std::string& key) {
			unsigned char size = (unsigned char)key.size();
			file_.write((char*)&size, 1);
			file_.write(key.c_str(), size);
		}

	public:
		/**
		 * @brief		コンストラクタ
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
		 * @brief		デストラクタ
		 */
		~LogInput() {
			file_.close();
		}

		/**
		 * @brief		入力認識の登録
		 */
		template< class T >
		std::shared_ptr<T> CreateInput() {
			auto ptr = std::make_shared<T>();
			input_ = ptr;
			return ptr;
		}

		/**
		 * @brief		更新
		 */
		void Update() override {
			input_->Update();

			//ログに出力
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
		 * @brief		指定名称の登録キーの入力値を取得
		 * @param[in]	kn		登録キー名
		 * @return		キー入力の値
		 */
		float GetAxis(const KeyType& kn) const override {
			return input_->GetAxis(kn);
		}

		/**
		 * @brief		指定名称の登録キーがこのフレームに押されたかどうか
		 * @param[in]	kn		登録キー名
		 * @return		true	このフレームで押された
		 *				false	このフレームでは押されていない
		 */
		bool IsPush(const KeyType& kn) const override {
			return input_->IsPush(kn);
		}

		/**
		 * @brief		指定名称の登録キーがこのフレームに押されたかどうか
		 * @param[in]	kn		登録キー名
		 * @return		true	このフレームで押された
		 *				false	このフレームでは押されていない
		 */
		bool IsNegativePush(const KeyType& kn) const override {
			return input_->IsNegativePush(kn);
		}

		/**
		 * @brief		指定名称の登録キーがこのフレームに離されたかどうか
		 * @param[in]	kn		登録キー名
		 * @return		true	このフレームで離された
		 *				false	このフレームでは離されていない
		 */
		bool IsPull(const KeyType& kn) const override {
			return input_->IsPull(kn);
		}

		/**
		 * @brief		指定名称の登録キーがこのフレームに離されたかどうか
		 * @param[in]	kn		登録キー名
		 * @return		true	このフレームで離された
		 *				false	このフレームでは離されていない
		 */
		bool IsNegativePull(const KeyType& kn) const override {
			return input_->IsNegativePull(kn);
		}

		/**
		 * @brief		指定名称の登録キーが押されているかどうか
		 * @param[in]	kn		登録キー名
		 * @return		true	このフレームで押されている
		 *				false	このフレームで押されていない
		 */
		bool IsPress(const KeyType& kn) const override {
			return input_->IsPress(kn);
		}

		/**
		 * @brief		指定名称の登録キーが押されているかどうか
		 * @param[in]	kn		登録キー名
		 * @return		true	このフレームで押されている
		 *				false	このフレームで押されていない
		 */
		bool IsNegativePress(const KeyType& kn) const override {
			return input_->IsNegativePress(kn);
		}

		/**
		 * @brief		登録されているキー配列
		 * @return		キーの識別配列
		 */
		std::vector<KeyType> GetKeyList() const override {
			return input_->GetKeyList();
		}
	};

}