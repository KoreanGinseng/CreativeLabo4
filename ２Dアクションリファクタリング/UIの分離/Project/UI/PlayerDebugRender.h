#pragma once

#include	"../Player.h"

namespace Sample {

	/**
	 * @brief		プレイヤーデバッグ描画
	 */
	class PlayerDebugRender
	{
	public:
		/**
		 * @brief		状態描画
		 */
		static void RenderState(CPlayer* pl, float wx, float wy, RenderCommandTaskPtr& task) {
			//位置の描画
			task->Push(Sample::StringRenderCommand::Create(wx, wy, "プレイヤー位置 X : %.0f , Y : %.0f プレイヤーHP : %d", pl->GetPosX(), pl->GetPosY(), pl->GetHP()), 0);
		}

		/**
		 * @brief		当たり判定描画
		 */
		static void RenderCollision(CPlayer* pl, float wx, float wy, RenderCommandTaskPtr& task) {
			//当たり判定の表示
			CRectangle hr = pl->GetRect();
			task->Push(Sample::RectRenderCommand::Create(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, 0xFF00FF00), 0);
			//攻撃の当たり判定表示
			if (pl->IsAttack())
			{
				CRectangle hr = pl->GetAttackRect();
				task->Push(Sample::RectRenderCommand::Create(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, 0xFFFF0000), 0);
			}
		}
	};

}