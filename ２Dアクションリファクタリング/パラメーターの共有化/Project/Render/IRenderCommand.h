#pragma once

#include	"../Common/ICommand.h"

namespace Sample {

	/**
	 * @brief		描画コマンド
	 */
	class __declspec(novtable) IRenderCommand : public ICommand
	{
	public:
	};
	//ポインタ置き換え
	using RenderCommandPtr = std::shared_ptr<IRenderCommand>;
	using RenderCommandList = std::vector<RenderCommandPtr>;

}