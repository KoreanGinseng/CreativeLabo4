#pragma once

#include	"IRenderRegister.h"
#include	"TextureRenderCommand.h"
#include	"../Player.h"

namespace Sample {

	/**
	 * @brief		�`��R�}���h�o�^
	 */
	class PlayerRender : public IRenderRegister
	{
	private:
		/** �v���C���[ */
		CPlayer*			player_;
		/** �X�N���[���l */
		float				scrollX_;
		/** �X�N���[���l */
		float				scrollY_;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		PlayerRender(CPlayer* pl)
			: player_(pl)
			, scrollX_(0)
			, scrollY_(0)
		{
		}

		/**
		 * @brief		�o�^
		 */
		void Register(Sample::RenderCommandTaskPtr& task) override {
			Register(player_, scrollX_, scrollY_, task);
		}

		/**
		 * @brief		�o�^
		 */
		static void Register(CPlayer* pl, float wx, float wy, Sample::RenderCommandTaskPtr& task) {
			//�C���^�[�o��2�t���[�����Ƃɕ`������Ȃ�
			if (pl->GetDamageWait() % 4 >= 2)
			{
				return;
			}
			//HP���Ȃ��Ȃ�ƕ`�悵�Ȃ�
			if (pl->GetHP() <= 0)
			{
				return;
			}
			//�`���`
			Sample::Rectangle dr = pl->GetSrcRect();
			//�`��ʒu
			float px = pl->GetPosX() - wx;
			float py = pl->GetPosY() - wy;
			//���]�t���O��ON�̏ꍇ�`���`�𔽓]������
			if (pl->IsReverse())
			{
				dr = dr.Reverse();
				if (pl->IsAttack())
				{
					px -= PLAYER_ATTACKWIDTH;
				}
			}
			//�e�N�X�`���̕`��
			task->Push(Sample::TextureRenderCommand::Create(px, py, dr, pl->GetTexture()), 1);
		}
	};

}