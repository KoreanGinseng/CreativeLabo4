#pragma once

#include	"../Common/Common.h"
#include	"../Render/IRenderRegister.h"
#include	"../Resource/ResourceManager.h"

namespace Sample {

	/**
	 * @brief		UI�I�u�W�F�N�g
	 */
	class __declspec(novtable) IUIObject : public IRenderRegister
	{
	public:
		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~IUIObject() = default;

		/**
		 * @brief		�ǂݍ���
		 */
		virtual bool Load(ResourcePackPtr<UsedResources>& pack) = 0;

		/**
		 * @brief		���
		 */
		virtual void Release(void) = 0;
	};

}