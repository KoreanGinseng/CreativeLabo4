#pragma once

#include	"../Common/Common.h"
#include	"../Render/IRenderRegister.h"
#include	"../Resource/ResourceManager.h"

namespace Sample {

	/**
	 * @brief		UIオブジェクト
	 */
	class __declspec(novtable) IUIObject : public IRenderRegister
	{
	public:
		/**
		 * @brief		デストラクタ
		 */
		virtual ~IUIObject() = default;

		/**
		 * @brief		読み込み
		 */
		virtual bool Load(ResourcePackPtr<UsedResources>& pack) = 0;

		/**
		 * @brief		解放
		 */
		virtual void Release(void) = 0;
	};

}