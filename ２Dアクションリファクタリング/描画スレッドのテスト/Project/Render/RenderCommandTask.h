#pragma once

#include	"IRenderCommand.h"

namespace Sample {

	/**
	 * @brief		描画コマンドタスク
	 */
	class RenderCommandTask : public ICommand
	{
	protected:
		/** コマンドリスト */
		std::vector< RenderCommandList >		commands_;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		RenderCommandTask(size_t layerCount)
			: commands_(layerCount)
		{
		}

		/**
		 * @brief		コマンドの登録
		 * @param[in]	cmd		コマンド
		 * @param[in]	layer	描画レイヤー
		 * @return		true	成功
		 *				false	失敗
		 */
		bool Push(const RenderCommandPtr& cmd, int layer) {
			if (layer >= commands_.size())
			{
				return false;
			}
			commands_[layer].push_back(cmd);
			return true;
		}

		/**
		 * @biref		実行
		 */
		void Exec() override {
			for (auto& layer : commands_)
			{
				for (auto& cmd : layer)
				{
					cmd->Exec();
				}
			}
		}

		/**
		 * @biref		レイヤー数取得
		 */
		int GetLayerCount() {
			return commands_.size();
		}
	};

	//ポインタ置き換え
	using RenderCommandTaskPtr = std::shared_ptr<RenderCommandTask>;
	using RenderCommandTaskQueue = std::queue<RenderCommandTaskPtr>;
	using RenderCommandTaskList = std::vector<RenderCommandTaskPtr>;

}