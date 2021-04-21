#pragma once

#include	"../Common/Common.h"
#include	"../Common/Singleton.h"

namespace Sample {

	/**
	 * @brief		インプットマネージャー
	 */
	class InputManager : public Singleton<InputManager>
	{
		friend class Singleton<InputManager>;
	private:
		//キー
		using KeyType = std::string;

		/** キー状態 */
		struct KeyData {
			enum class Type {
				Keyboard,
				Mouse,

				JoyStickHorizontal,

				JoyStickVertical,

				JoyPad,
			};
			struct Key {
				int				positiveNo;
				int				negativeNo;
				int				padNo;
				Type			type;
			};
			std::vector<Key>	key;
			float				prevValue;
			float				nowValue;
			float				inputValue;

			KeyData()
				: key()
				, prevValue(0)
				, nowValue(0)
				, inputValue(0.5f) {
			}
		};
		using KeyMap = std::unordered_map<KeyType, KeyData >;
		KeyMap					keyMap_;

		/**
		 * @brief		コンストラクタ
		 */
		InputManager()
			: Singleton<InputManager>()
			, keyMap_()
		{ }

		/**
		 * @brief		キーボードキーの取得
		 * @param[in]	positive		＋方向のキー
		 * @param[in]	negative		−方向のキー
		 * @return		キー入力の値
		 */
		float GetKeyboardKeyState(int positive, int negative) const {
			if (positive >= 0 && g_pInput->IsKeyHold(positive)) { return 1.0f; }
			if (negative >= 0 && g_pInput->IsKeyHold(negative)) { return -1.0f; }
			return 0;
		}


		/**
		 * @brief		マウスキーの取得
		 * @param[in]	positive		＋方向のキー
		 * @param[in]	negative		−方向のキー
		 * @return		キー入力の値
		 */
		float GetMouseKeyState(int positive, int negative) const {
			if (positive >= 0 && g_pInput->IsMouseKeyHold(positive)) { return 1.0f; }
			if (negative >= 0 && g_pInput->IsMouseKeyHold(negative)) { return -1.0f; }
			return 0;
		}

		/**
		 * @brief		ジョイパッドキーの取得
		 * @param[in]	padNo			パッド番号
		 * @param[in]	positive		＋方向のキー
		 * @param[in]	negative		−方向のキー
		 * @return		キー入力の値
		 */
		float GetJoypadKeyState(int padNo, int positive, int negative) const {
			LPGamePad pad = g_pInput->GetGamePad(padNo);
			if (pad == nullptr)
			{
				return 0;
			}
			if (positive >= 0 && pad->IsKeyHold(positive)) { return 1.0f; }
			if (negative >= 0 && pad->IsKeyHold(negative)) { return -1.0f; }
			return 0;
		}

		/**
		 * @brief		ジョイパッドスティックの取得
		 * @param[in]	padNo			パッド番号
		 * @return		キー入力の値
		 */
		float GetJoypadStickHorizontal(int padNo) const {
			LPGamePad pad = g_pInput->GetGamePad(padNo);
			if (pad == nullptr)
			{
				return 0;
			}
			return pad->GetStickHorizontal();
		}

		/**
		 * @brief		ジョイパッドスティックの取得
		 * @param[in]	padNo			パッド番号
		 * @return		キー入力の値
		 */
		float GetJoypadStickVertical(int padNo) const {
			LPGamePad pad = g_pInput->GetGamePad(padNo);
			if (pad == nullptr)
			{
				return 0;
			}
			return pad->GetStickVertical();
		}

	public:

		/**
		 * @brief		登録キーの追加
		 * @param[in]	kn				登録キー名
		 * @param[in]	key				登録キー
		 */
		void AddKeyboardKey(const KeyType& kn, int key) {
			auto km = keyMap_.find(kn);
			if (km != keyMap_.end())
			{
				km->second.key.push_back({ key, -1, -1, KeyData::Type::Keyboard });
			}
			else
			{
				keyMap_[kn].key.push_back({ key, -1, -1, KeyData::Type::Keyboard });
			}
		}

		/**
		 * @brief		登録キーの追加
		 * @param[in]	kn				登録キー名
		 * @param[in]	positiveKey		+方向の登録キー
		 * @param[in]	negativeKey		-方向の登録キー
		 */
		void AddKeyboardKey(const KeyType& kn, int positiveKey, int negativeKey) {
			auto km = keyMap_.find(kn);
			if (km != keyMap_.end())
			{
				km->second.key.push_back({ positiveKey, negativeKey, -1, KeyData::Type::Keyboard });
			}
			else
			{
				keyMap_[kn].key.push_back({ positiveKey, negativeKey, -1, KeyData::Type::Keyboard });
			}
		}

		/**
		 * @brief		登録キーの追加
		 * @param[in]	kn		登録キー名
		 * @param[in]	Key		登録キー
		 */
		void AddMouseKey(const KeyType& kn, int Key) {
			auto km = keyMap_.find(kn);
			if (km != keyMap_.end())
			{
				km->second.key.push_back({ Key, -1, -1, KeyData::Type::Mouse });
			}
			else
			{
				keyMap_[kn].key.push_back({ Key, -1, -1, KeyData::Type::Mouse });
			}
		}

		/**
		 * @brief		登録キーの追加
		 * @param[in]	kn				登録キー名
		 * @param[in]	pad				登録パッド
		 * @param[in]	key				登録キー
		 */
		void AddJoypadKey(const KeyType& kn, int pad, int key) {
			auto km = keyMap_.find(kn);
			if (km != keyMap_.end())
			{
				km->second.key.push_back({ key, -1, pad, KeyData::Type::JoyPad });
			}
			else
			{
				keyMap_[kn].key.push_back({ key, -1, pad, KeyData::Type::JoyPad });
			}
		}

		/**
		 * @brief		登録キーの追加
		 * @param[in]	kn				登録キー名
		 * @param[in]	pad				登録パッド
		 */
		void AddJoyStickHorizontal(const KeyType& kn, int pad) {
			auto km = keyMap_.find(kn);
			if (km != keyMap_.end())
			{
				km->second.key.push_back({ -1, -1, pad, KeyData::Type::JoyStickHorizontal });
			}
			else
			{
				keyMap_[kn].key.push_back({ -1, -1, pad, KeyData::Type::JoyStickHorizontal });
			}
		}

		/**
		 * @brief		登録キーの追加
		 * @param[in]	kn				登録キー名
		 * @param[in]	pad				登録パッド
		 */
		void AddJoyStickVertical(const KeyType& kn, int pad) {
			auto km = keyMap_.find(kn);
			if (km != keyMap_.end())
			{
				km->second.key.push_back({ -1, -1, pad, KeyData::Type::JoyStickVertical });
			}
			else
			{
				keyMap_[kn].key.push_back({ -1, -1, pad, KeyData::Type::JoyStickVertical });
			}
		}

		/**
		 * @brief		更新
		 */
		void Update() {
			for (auto k = keyMap_.begin(); k != keyMap_.end(); ++k)
			{
				k->second.prevValue = k->second.nowValue;
				k->second.nowValue = 0;
				for (auto& key : k->second.key)
				{
					switch (key.type)
					{
						//キーボード
					case KeyData::Type::Keyboard:
						k->second.nowValue += GetKeyboardKeyState(key.positiveNo, key.negativeNo);
						break;

						//マウス
					case KeyData::Type::Mouse:
						k->second.nowValue += GetMouseKeyState(key.positiveNo, key.negativeNo);
						break;

						//ジョイパッド
					case KeyData::Type::JoyPad:
						k->second.nowValue += GetJoypadKeyState(key.padNo, key.positiveNo, key.negativeNo);
						break;

						//ジョイスティック
					case KeyData::Type::JoyStickHorizontal:
						k->second.nowValue += GetJoypadStickHorizontal(key.padNo);
						break;

						//ジョイスティック
					case KeyData::Type::JoyStickVertical:
						k->second.nowValue += GetJoypadStickVertical(key.padNo);
						break;

					}
				}
				//-1〜+1でクリップ
				if (k->second.nowValue > 1) { k->second.nowValue = 1; }
				else if (k->second.nowValue < -1) { k->second.nowValue = -1; }
			}
		}

		/**
		 * @brief		指定名称の登録キーの入力値を取得
		 * @param[in]	kn		登録キー名
		 * @return		キー入力の値
		 */
		float GetAxis(const KeyType& kn) const {
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
		bool IsPush(const KeyType& kn) const {
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
		bool IsNegativePush(const KeyType& kn) const {
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
		bool IsPull(const KeyType& kn) const {
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
		bool IsNegativePull(const KeyType& kn) const {
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
		bool IsPress(const KeyType& kn) const {
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
		bool IsNegativePress(const KeyType& kn) const {
			const auto& v = keyMap_.find(kn);
			if (v == keyMap_.end()) { return 0; }
			const KeyData& kd = v->second;
			return kd.nowValue < -kd.inputValue;
		}

		/**
		 * @brief		登録されているキー配列
		 * @return		キーの識別配列
		 */
		std::vector<KeyType> GetKeyList() const {
			std::vector<KeyType> keys;
			for (auto& key : keyMap_)
			{
				keys.push_back(key.first);
			}
			return keys;
		}
	};

}
//簡易アクセス用
#define InputManagerInstance	Sample::InputManager::GetInstance()