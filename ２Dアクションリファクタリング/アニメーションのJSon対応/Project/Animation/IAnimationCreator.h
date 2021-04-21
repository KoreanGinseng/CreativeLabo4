#pragma once

#include	"IAnimationState.h"

namespace Sample {

	/**
	 * @brief		�A�j���[�V�����C���^�[�t�F�C�X
	 */
	class __declspec(novtable) IAnimationCreator
	{
	public:
		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~IAnimationCreator() = default;

		/**
		 * @brief		����
		 */
		virtual AnimationStatePtr Create() = 0;
	};
	//�|�C���^�u������
	using AnimationCreatorPtr = std::shared_ptr<IAnimationCreator>;

}