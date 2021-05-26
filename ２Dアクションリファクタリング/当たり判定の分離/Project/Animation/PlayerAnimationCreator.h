#pragma once

#include	"IAnimationCreator.h"
#include	"MofAnimationState.h"

namespace Sample {

	/**
	 * @brief		アニメーションインターフェイス
	 */
	class PlayerAnimationCreator : public IAnimationCreator
	{
	public:
		/**
		 * @brief		生成
		 */
		AnimationStatePtr Create() override {
			std::shared_ptr< CreateAnimationState > state = std::make_shared< CreateAnimationState >();
			//アニメーションを作成
			std::vector<AnimationState::AnimationData> anim {
				//待機
				{
					"Wait",
					0,0,
					60,64,
					TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0},{5,6,0},{5,7,0}}
				},
				//移動
				{
					"Move",
					0,70,
					60,64,
					TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0}}
				},
				//ジャンプ
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
				//攻撃
				{
					"Attack",
					0,350,
					90,64,
					FALSE,{{2,0,0},{2,1,0},{2,2,0},{2,3,0},{2,4,0},{2,5,0},{2,6,0}}
				},
				//ダメージ
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