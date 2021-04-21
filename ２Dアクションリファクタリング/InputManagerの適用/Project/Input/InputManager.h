#pragma once

#include	"../Common/Common.h"
#include	"../Common/Singleton.h"

namespace Sample {

	/**
	 * @brief		�C���v�b�g�}�l�[�W���[
	 */
	class InputManager : public Singleton<InputManager>
	{
		friend class Singleton<InputManager>;
	private:
		//�L�[
		using KeyType = std::string;

		/** �L�[��� */
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
		 * @brief		�R���X�g���N�^
		 */
		InputManager()
			: Singleton<InputManager>()
			, keyMap_()
		{ }

		/**
		 * @brief		�L�[�{�[�h�L�[�̎擾
		 * @param[in]	positive		�{�����̃L�[
		 * @param[in]	negative		�|�����̃L�[
		 * @return		�L�[���͂̒l
		 */
		float GetKeyboardKeyState(int positive, int negative) const {
			if (positive >= 0 && g_pInput->IsKeyHold(positive)) { return 1.0f; }
			if (negative >= 0 && g_pInput->IsKeyHold(negative)) { return -1.0f; }
			return 0;
		}


		/**
		 * @brief		�}�E�X�L�[�̎擾
		 * @param[in]	positive		�{�����̃L�[
		 * @param[in]	negative		�|�����̃L�[
		 * @return		�L�[���͂̒l
		 */
		float GetMouseKeyState(int positive, int negative) const {
			if (positive >= 0 && g_pInput->IsMouseKeyHold(positive)) { return 1.0f; }
			if (negative >= 0 && g_pInput->IsMouseKeyHold(negative)) { return -1.0f; }
			return 0;
		}

		/**
		 * @brief		�W���C�p�b�h�L�[�̎擾
		 * @param[in]	padNo			�p�b�h�ԍ�
		 * @param[in]	positive		�{�����̃L�[
		 * @param[in]	negative		�|�����̃L�[
		 * @return		�L�[���͂̒l
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
		 * @brief		�W���C�p�b�h�X�e�B�b�N�̎擾
		 * @param[in]	padNo			�p�b�h�ԍ�
		 * @return		�L�[���͂̒l
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
		 * @brief		�W���C�p�b�h�X�e�B�b�N�̎擾
		 * @param[in]	padNo			�p�b�h�ԍ�
		 * @return		�L�[���͂̒l
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
		 * @brief		�o�^�L�[�̒ǉ�
		 * @param[in]	kn				�o�^�L�[��
		 * @param[in]	key				�o�^�L�[
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
		 * @brief		�o�^�L�[�̒ǉ�
		 * @param[in]	kn				�o�^�L�[��
		 * @param[in]	positiveKey		+�����̓o�^�L�[
		 * @param[in]	negativeKey		-�����̓o�^�L�[
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
		 * @brief		�o�^�L�[�̒ǉ�
		 * @param[in]	kn		�o�^�L�[��
		 * @param[in]	Key		�o�^�L�[
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
		 * @brief		�o�^�L�[�̒ǉ�
		 * @param[in]	kn				�o�^�L�[��
		 * @param[in]	pad				�o�^�p�b�h
		 * @param[in]	key				�o�^�L�[
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
		 * @brief		�o�^�L�[�̒ǉ�
		 * @param[in]	kn				�o�^�L�[��
		 * @param[in]	pad				�o�^�p�b�h
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
		 * @brief		�o�^�L�[�̒ǉ�
		 * @param[in]	kn				�o�^�L�[��
		 * @param[in]	pad				�o�^�p�b�h
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
		 * @brief		�X�V
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
						//�L�[�{�[�h
					case KeyData::Type::Keyboard:
						k->second.nowValue += GetKeyboardKeyState(key.positiveNo, key.negativeNo);
						break;

						//�}�E�X
					case KeyData::Type::Mouse:
						k->second.nowValue += GetMouseKeyState(key.positiveNo, key.negativeNo);
						break;

						//�W���C�p�b�h
					case KeyData::Type::JoyPad:
						k->second.nowValue += GetJoypadKeyState(key.padNo, key.positiveNo, key.negativeNo);
						break;

						//�W���C�X�e�B�b�N
					case KeyData::Type::JoyStickHorizontal:
						k->second.nowValue += GetJoypadStickHorizontal(key.padNo);
						break;

						//�W���C�X�e�B�b�N
					case KeyData::Type::JoyStickVertical:
						k->second.nowValue += GetJoypadStickVertical(key.padNo);
						break;

					}
				}
				//-1�`+1�ŃN���b�v
				if (k->second.nowValue > 1) { k->second.nowValue = 1; }
				else if (k->second.nowValue < -1) { k->second.nowValue = -1; }
			}
		}

		/**
		 * @brief		�w�薼�̂̓o�^�L�[�̓��͒l���擾
		 * @param[in]	kn		�o�^�L�[��
		 * @return		�L�[���͂̒l
		 */
		float GetAxis(const KeyType& kn) const {
			const auto& v = keyMap_.find(kn);
			if (v == keyMap_.end()) { return 0; }
			const KeyData& kd = v->second;
			return kd.nowValue;
		}

		/**
		 * @brief		�w�薼�̂̓o�^�L�[�����̃t���[���ɉ����ꂽ���ǂ���
		 * @param[in]	kn		�o�^�L�[��
		 * @return		true	���̃t���[���ŉ����ꂽ
		 *				false	���̃t���[���ł͉�����Ă��Ȃ�
		 */
		bool IsPush(const KeyType& kn) const {
			const auto& v = keyMap_.find(kn);
			if (v == keyMap_.end()) { return 0; }
			const KeyData& kd = v->second;
			return kd.nowValue > kd.inputValue && kd.prevValue < kd.inputValue;
		}

		/**
		 * @brief		�w�薼�̂̓o�^�L�[�����̃t���[���ɉ����ꂽ���ǂ���
		 * @param[in]	kn		�o�^�L�[��
		 * @return		true	���̃t���[���ŉ����ꂽ
		 *				false	���̃t���[���ł͉�����Ă��Ȃ�
		 */
		bool IsNegativePush(const KeyType& kn) const {
			const auto& v = keyMap_.find(kn);
			if (v == keyMap_.end()) { return 0; }
			const KeyData& kd = v->second;
			return kd.nowValue < -kd.inputValue && kd.prevValue > -kd.inputValue;
		}

		/**
		 * @brief		�w�薼�̂̓o�^�L�[�����̃t���[���ɗ����ꂽ���ǂ���
		 * @param[in]	kn		�o�^�L�[��
		 * @return		true	���̃t���[���ŗ����ꂽ
		 *				false	���̃t���[���ł͗�����Ă��Ȃ�
		 */
		bool IsPull(const KeyType& kn) const {
			const auto& v = keyMap_.find(kn);
			if (v == keyMap_.end()) { return 0; }
			const KeyData& kd = v->second;
			return kd.nowValue < kd.inputValue && kd.prevValue > kd.inputValue;
		}

		/**
		 * @brief		�w�薼�̂̓o�^�L�[�����̃t���[���ɗ����ꂽ���ǂ���
		 * @param[in]	kn		�o�^�L�[��
		 * @return		true	���̃t���[���ŗ����ꂽ
		 *				false	���̃t���[���ł͗�����Ă��Ȃ�
		 */
		bool IsNegativePull(const KeyType& kn) const {
			const auto& v = keyMap_.find(kn);
			if (v == keyMap_.end()) { return 0; }
			const KeyData& kd = v->second;
			return kd.nowValue > kd.inputValue && kd.prevValue < -kd.inputValue;
		}

		/**
		 * @brief		�w�薼�̂̓o�^�L�[��������Ă��邩�ǂ���
		 * @param[in]	kn		�o�^�L�[��
		 * @return		true	���̃t���[���ŉ�����Ă���
		 *				false	���̃t���[���ŉ�����Ă��Ȃ�
		 */
		bool IsPress(const KeyType& kn) const {
			const auto& v = keyMap_.find(kn);
			if (v == keyMap_.end()) { return 0; }
			const KeyData& kd = v->second;
			return kd.nowValue > kd.inputValue;
		}

		/**
		 * @brief		�w�薼�̂̓o�^�L�[��������Ă��邩�ǂ���
		 * @param[in]	kn		�o�^�L�[��
		 * @return		true	���̃t���[���ŉ�����Ă���
		 *				false	���̃t���[���ŉ�����Ă��Ȃ�
		 */
		bool IsNegativePress(const KeyType& kn) const {
			const auto& v = keyMap_.find(kn);
			if (v == keyMap_.end()) { return 0; }
			const KeyData& kd = v->second;
			return kd.nowValue < -kd.inputValue;
		}

		/**
		 * @brief		�o�^����Ă���L�[�z��
		 * @return		�L�[�̎��ʔz��
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
//�ȈՃA�N�Z�X�p
#define InputManagerInstance	Sample::InputManager::GetInstance()