#pragma once

#include	"IRenderCommand.h"

namespace Sample {

	/**
	 * @brief		�`��R�}���h�^�X�N
	 */
	class RenderCommandTask : public ICommand
	{
	protected:
		/** �R�}���h���X�g */
		std::vector< RenderCommandList >		commands_;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		RenderCommandTask(size_t layerCount)
			: commands_(layerCount)
		{
		}

		/**
		 * @brief		�R�}���h�̓o�^
		 * @param[in]	cmd		�R�}���h
		 * @param[in]	layer	�`�惌�C���[
		 * @return		true	����
		 *				false	���s
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
		 * @biref		���s
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
		 * @biref		���C���[���擾
		 */
		int GetLayerCount() {
			return commands_.size();
		}
	};

	//�|�C���^�u������
	using RenderCommandTaskPtr = std::shared_ptr<RenderCommandTask>;
	using RenderCommandTaskQueue = std::queue<RenderCommandTaskPtr>;
	using RenderCommandTaskList = std::vector<RenderCommandTaskPtr>;

}