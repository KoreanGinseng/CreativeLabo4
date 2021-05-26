#pragma once

#include	"IRenderRegister.h"
#include	"TextureRenderCommand.h"
#include	"../Player.h"

namespace Sample {

	/**
	 * @brief		描画コマンド登録
	 */
	class PlayerRender : public IRenderRegister
	{
	private:
		/** プレイヤー */
		CPlayer*			player_;
		/** スクロール値 */
		float				scrollX_;
		/** スクロール値 */
		float				scrollY_;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		PlayerRender(CPlayer* pl)
			: player_(pl)
			, scrollX_(0)
			, scrollY_(0)
		{
		}

		/**
		 * @brief		登録
		 */
		void Register(Sample::RenderCommandTaskPtr& task) override {
			Register(player_, scrollX_, scrollY_, task);
		}

		/**
		 * @brief		登録
		 */
		static void Register(CPlayer* pl, float wx, float wy, Sample::RenderCommandTaskPtr& task) {
			//インターバル2フレームごとに描画をしない
			if (pl->GetDamageWait() % 4 >= 2)
			{
				return;
			}
			//HPがなくなると描画しない
			if (pl->GetHP() <= 0)
			{
				return;
			}
			//描画矩形
			Sample::Rectangle dr = pl->GetSrcRect();
			//描画位置
			float px = pl->GetPosX() - wx;
			float py = pl->GetPosY() - wy;
			//反転フラグがONの場合描画矩形を反転させる
			if (pl->IsReverse())
			{
				dr = dr.Reverse();
				if (pl->IsAttack())
				{
					px -= PLAYER_ATTACKWIDTH;
				}
			}
			//テクスチャの描画
			task->Push(Sample::TextureRenderCommand::Create(px, py, dr, pl->GetTexture()), 1);
		}
	};

}