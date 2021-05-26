#pragma once

#include	"RenderCommandTask.h"

namespace Sample {

	/**
	 * @brief		描画コマンド
	 */
	class __declspec(novtable) IRenderRegister
	{
	public:
		/**
		 * @brief		デストラクタ
		 */
		virtual ~IRenderRegister() = default;

		/**
		 * @brief		登録
		 */
		virtual void Register(Sample::RenderCommandTaskPtr& task) = 0;
	};
	//ポインタ置き換え
	using RenderRegisterPtr = std::shared_ptr<IRenderRegister>;
	using RenderRegisterList = std::vector<RenderRegisterPtr>;

}