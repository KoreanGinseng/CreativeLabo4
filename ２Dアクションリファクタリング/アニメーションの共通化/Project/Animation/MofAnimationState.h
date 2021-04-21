#pragma once

#include	"AnimationState.h"

#ifdef __MOFLIB
#include	<Mof.h>

namespace Sample {

	/**
	 * @brief		Mof�̋@�\���g�����A�j���[�V����
	 */
	class MofAnimationState : public AnimationState
	{
	protected:
		/** Mof�̃��[�V�����R���g���[���[ */
		CSpriteMotionController		motion_;
		/** Mof�̃��[�V�����Ή� */
		using MotionMap = std::unordered_map<std::string, MofU32 >;
		MotionMap					motionMap_;

		/**
		 * @brief		�A�j���[�V�����f�[�^��Mof�ϊ�
		 */
		SpriteAnimationCreate Convert(AnimationData data) {
			SpriteAnimationCreate re{
				data.Name.c_str(),
				data.OffsetX,	data.OffsetY,
				data.Width,		data.Height,
				data.bLoop,
				{0}
			};
			for (MofU32 i = 0; i < data.Pattern.size(); i++)
			{
				re.Pattern[i].Wait = data.Pattern[i].Wait;
				re.Pattern[i].No = data.Pattern[i].No;
				re.Pattern[i].Step = data.Pattern[i].Step;
			}
			return re;
		}

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		MofAnimationState()
			: AnimationState()
			, motion_()
			, motionMap_() {
		}

		/**
		 * @brief		Mof�̃A�j���[�V�����R���g���[���[����
		 * @param[in]	pattern			�A�j���[�V�����������
		 * @return		true			����
		 *				false			���s
		 */
		bool Create(const std::vector< AnimationData >& pattern) override {
			std::vector< SpriteAnimationCreate > pac(pattern.size());
			for (MofU32 i = 0; i < pattern.size(); i++)
			{
				pac[i] = Convert(pattern[i]);
				motionMap_[pattern[i].Name] = i;
			}
			return motion_.Create(&pac[0], pattern.size());
		}

		/**
		 * @brief		�X�V
		 */
		void Update() override {
			constexpr float frameTime = 0.017f;
			motion_.AddTimer(frameTime);
			srcRect_ = motion_.GetSrcRect();
		}

		/**
		 * @brief		���݂̃��[�V������ύX
		 * @param[in]	name	�o�^���[�V������
		 * @param[in]	isSame	���ꃂ�[�V�����ł̍X�V�t���O
		 * @return		true	�w�胂�[�V�������s��
		 *				false	�Ⴄ
		 */
		bool ChangeMotion(const std::string& name, bool isSame = true) override {
			return motion_.ChangeMotion(motionMap_[name], isSame) == TRUE;
		}


		/**
		 * @brief		�w�薼�̂̓o�^���[�V���������s����Ă��邩�ǂ���
		 * @param[in]	name	�o�^���[�V������
		 * @return		true	�w�胂�[�V�������s��
		 *				false	�Ⴄ
		 */
		bool IsMotion(const std::string& name) const override {
			const auto& v = motionMap_.find(name);
			if (v == motionMap_.end()) { return false; }
			return motion_.GetMotionNo() == v->second;
		}

		/**
		 * @brief		���݂̃��[�V�������I�����Ă��邩�𔻒肷��B
		 *				���[�V���������[�v����ꍇ��TRUE�ɂȂ邱�Ƃ͂Ȃ�
		 * @return		true	�I���ς�
		 *				false	�܂��I�����Ă��Ȃ�
		 */
		bool IsEndMotion() override {
			return motion_.IsEndMotion() == TRUE;
		}
	};
	using CreateAnimationState = MofAnimationState;

}

#endif