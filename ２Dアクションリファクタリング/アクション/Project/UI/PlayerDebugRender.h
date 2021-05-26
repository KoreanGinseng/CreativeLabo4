#pragma once

#include	"../Player.h"

namespace Sample {

	/**
	 * @brief		�v���C���[�f�o�b�O�`��
	 */
	class PlayerDebugRender
	{
	public:
		/**
		 * @brief		��ԕ`��
		 */
		static void RenderState(CPlayer* pl, float wx, float wy, RenderCommandTaskPtr& task) {
			//�ʒu�̕`��
			task->Push(Sample::StringRenderCommand::Create(wx, wy, "�v���C���[�ʒu X : %.0f , Y : %.0f �v���C���[HP : %d", pl->GetPosX(), pl->GetPosY(), pl->GetHP()), 0);
		}

		/**
		 * @brief		�����蔻��`��
		 */
		static void RenderCollision(CPlayer* pl, float wx, float wy, RenderCommandTaskPtr& task) {
			//�����蔻��̕\��
			CRectangle hr = pl->GetRect();
			task->Push(Sample::RectRenderCommand::Create(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, 0xFF00FF00), 0);
			//�U���̓����蔻��\��
			if (pl->IsAttack())
			{
				CRectangle hr = pl->GetAttackRect();
				task->Push(Sample::RectRenderCommand::Create(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, 0xFFFF0000), 0);
			}
		}
	};

}