#pragma once

#include	"IAnimationCreator.h"
#include	"MofAnimationState.h"

namespace Sample {

	/**
	 * @brief		�A�j���[�V�����C���^�[�t�F�C�X
	 */
	class PlayerAnimationCreator : public IAnimationCreator
	{
	public:
		/**
		 * @brief		����
		 */
		AnimationStatePtr Create() override {
			std::shared_ptr< CreateAnimationState > state = std::make_shared< CreateAnimationState >();
			//�A�j���[�V�������쐬
			std::vector<AnimationState::AnimationData> anim {
				//�ҋ@
				{
					"Wait",
					0,0,
					60,64,
					TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0},{5,6,0},{5,7,0}}
				},
				//�ړ�
				{
					"Move",
					0,70,
					60,64,
					TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0}}
				},
				//�W�����v
				{
					"JumpStart",
					0,140,
					60,64,
					FALSE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0}}
				},
				{
					"JumpEnd",
					240,140,
					60,64,
					FALSE,{{2,0,0},{2,1,0}}
				},
				//�U��
				{
					"Attack",
					0,350,
					90,64,
					FALSE,{{2,0,0},{2,1,0},{2,2,0},{2,3,0},{2,4,0},{2,5,0},{2,6,0}}
				},
				//�_���[�W
				{
					"Damage",
					480,0,
					60,64,
					FALSE,{{20,0,0}}
				},
			};
			state->Create(anim);
			return state;
		}
	};

}