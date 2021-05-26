#pragma once

#include	"IInput.h"

namespace Sample {

	/**
	 * @brief		入力クラス
	 */
	class ReplayInput : public IInput
	{
	protected:
		/** キー状態 */
		struct KeyData {
			float				prevValue;
			float				nowValue;
			float				inputValue;

			KeyData()
				: prevValue(0)
				, nowValue(0)
				, inputValue(0.5f) {
			}
		};
		using KeyMap = std::unordered_map<KeyType, KeyData >;
		KeyMap					keyMap_;

		/** ファイルストリーム */
		std::ifstream			file_;

		/**
		 * @brief		ファイルからのキー読み込み
		 */
		template < typename T = KeyType >
		T ReadKey(unsigned char size) {
			T key;
			file_.read((char*)&key, sizeof(T));
			return key;
		}

		/**
		 * @brief		ファイルからのキー読み込み
		 */
		template < >
		std::string ReadKey<std::string>(unsigned char size) {
			std::string key(size, '\0');
			file_.read(&key[0], size);
			return key;
		}

	public:
		/**
		 * @brief		コンストラクタ
		 */
		ReplayInput(const std::string& name)
			: keyMap_()
			, file_()
		{
			file_.open(name, std::ios::in | std::ios::binary);
		}
		/**
		 * @brief		デストラクタ
		 */
		~ReplayInput() {
			file_.close();
		}

		/**
		 * @brief		更新
		 */
		void Update() override {
			for (auto& key : keyMap_)
			{
				key.second.prevValue = key.second.nowValue;
				key.second.nowValue = 0;
			}
			while (!file_.eof())
			{
				unsigned char size = 0;
				file_.read((char*)&size, 1);
				if (size == 0xFF)
				{
					break;
				}
				KeyType key = ReadKey(size);
				float v = 0;
				file_.read((char*)&v, sizeof(v));
				keyMap_[key].nowValue = v;
			}
		}

		/**
		 * @brief		指定名称の登録キーの入力値を取得
		 * @param[in]	kn		登録キー名
		 * @return		キー入力の値
		 */
		float GetAxis(const KeyType& kn) const override {
			const auto& v = keyMap_.find(kn);
			if (v == keyMap_.end()) { return 0; }
			const KeyData& kd = v->second;
			return kd.nowValue;
		}

		/**
		 * @brief		指定名称の登録キーがこのフレームに押されたかどうか
		 * @param[in]	kn		登録キー名
		 * @return		true	このフレームで押された
		 *				false	このフレームでは押されていない
		 */
		bool IsPush(const KeyType& kn) const override {
			const auto& v = keyMap_.find(kn);
			if (v == keyMap_.end()) { return 0; }
			const KeyData& kd = v->second;
			return kd.nowValue > kd.inputValue && kd.prevValue < kd.inputValue;
		}

		/**
		 * @brief		指定名称の登録キーがこのフレームに押されたかどうか
		 * @param[in]	kn		登録キー名
		 * @return		true	このフレームで押された
		 *				false	このフレームでは押されていない
		 */
		bool IsNegativePush(const KeyType& kn) const override {
			const auto& v = keyMap_.find(kn);
			if (v == keyMap_.end()) { return 0; }
			const KeyData& kd = v->second;
			return kd.nowValue < -kd.inputValue && kd.prevValue > -kd.inputValue;
		}

		/**
		 * @brief		指定名称の登録キーがこのフレームに離されたかどうか
		 * @param[in]	kn		登録キー名
		 * @return		true	このフレームで離された
		 *				false	このフレームでは離されていない
		 */
		bool IsPull(const KeyType& kn) const override {
			const auto& v = keyMap_.find(kn);
			if (v == keyMap_.end()) { return 0; }
			const KeyData& kd = v->second;
			return kd.nowValue < kd.inputValue && kd.prevValue > kd.inputValue;
		}

		/**
		 * @brief		指定名称の登録キーがこのフレームに離されたかどうか
		 * @param[in]	kn		登録キー名
		 * @return		true	このフレームで離された
		 *				false	このフレームでは離されていない
		 */
		bool IsNegativePull(const KeyType& kn) const override {
			const auto& v = keyMap_.find(kn);
			if (v == keyMap_.end()) { return 0; }
			const KeyData& kd = v->second;
			return kd.nowValue > kd.inputValue && kd.prevValue < -kd.inputValue;
		}

		/**
		 * @brief		指定名称の登録キーが押されているかどうか
		 * @param[in]	kn		登録キー名
		 * @return		true	このフレームで押されている
		 *				false	このフレームで押されていない
		 */
		bool IsPress(const KeyType& kn) const override {
			const auto& v = keyMap_.find(kn);
			if (v == keyMap_.end()) { return 0; }
			const KeyData& kd = v->second;
			return kd.nowValue > kd.inputValue;
		}

		/**
		 * @brief		指定名称の登録キーが押されているかどうか
		 * @param[in]	kn		登録キー名
		 * @return		true	このフレームで押されている
		 *				false	このフレームで押されていない
		 */
		bool IsNegativePress(const KeyType& kn) const override {
			const auto& v = keyMap_.find(kn);
			if (v == keyMap_.end()) { return 0; }
			const KeyData& kd = v->second;
			return kd.nowValue < -kd.inputValue;
		}

		/**
		 * @brief		登録されているキー配列
		 * @return		キーの識別配列
		 */
		std::vector<KeyType> GetKeyList() const override {
			std::vector<KeyType> keys;
			for (auto& key : keyMap_)
			{
				keys.push_back(key.first);
			}
			return keys;
		}
	};

}