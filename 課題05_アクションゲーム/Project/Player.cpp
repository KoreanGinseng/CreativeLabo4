#include	"Player.h"
#include    "PlayerDefine.h"

/**
 * コンストラクタ
 *
 */
CPlayer::CPlayer() :
    CCharacter(),
	m_Motion(),
	m_bMove(false),
	m_bJump(false),
	m_bReverse(false),
	m_SrcRect(),
	m_bEnd(false),
	m_pEndEffect(NULL),
	m_bGoal(false) {
}

/**
 * デストラクタ
 *
 */
CPlayer::~CPlayer() {
}

/**
 * 読み込み
 * 利用するテクスチャを読み込む。
 */
bool CPlayer::Load(void) {
	//アニメーションを作成
	SpriteAnimationCreate anim[] = {
		//待機
		{
			"待機",
			0,0,
			60,64,
			TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0},{5,6,0},{5,7,0}}
		},
		//移動
		{
			"移動",
			0,70,
			60,64,
			TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0}}
		},
		//ジャンプ
		{
			"ジャンプ開始",
			0,140,
			60,64,
			FALSE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0}}
		},
		{
			"ジャンプ終了",
			240,140,
			60,64,
			FALSE,{{2,0,0},{2,1,0}}
		},
		//攻撃
		{
			"攻撃",
			0,350,
			90,64,
			FALSE,{{2,0,0},{2,1,0},{2,2,0},{2,3,0},{2,4,0},{2,5,0},{2,6,0}}
		},
		//ダメージ
		{
			"ダメージ",
			480,0,
			60,64,
			FALSE,{{20,0,0}}
		},
	};
	m_Motion.Create(anim, MOTION_COUNT);
	return true;
}

/**
 * 初期化
 * パラメーターや座標を初期化する。
 * プレイヤーの位置など状態を初期化したいときに実行する。
 */
void CPlayer::Initialize(void) {
	m_Pos.x      = 200;
	m_Pos.y      = 0;
	m_bMove      = false;
	m_Move.x     = 0.0f;
	m_Move.y     = 0.0f;
	m_bReverse   = false;
	m_bJump      = false;
	m_HP         = 100;
	m_DamageWait = 0;
	m_bEnd       = false;
	m_pEndEffect = NULL;
	m_bGoal      = false;
	m_Motion.ChangeMotion(MOTION_WAIT);
}

/**
 * 更新
 *
 */
void CPlayer::Update(void) {
	//HPがなくなると爆発の終了を待機して終了
	if (m_HP <= 0)
	{
		if (!m_pEndEffect || !m_pEndEffect->GetShow())
		{
			m_bEnd = true;
		}
		return;
	}
	//移動フラグ、このフレームでの移動があったかを保存
	m_bMove = false;
	//攻撃中、着地の場合の動作
	if (m_Motion.GetMotionNo() == MOTION_ATTACK || m_Motion.GetMotionNo() == MOTION_JUMPEND)
	{
		//終了で待機に戻す
		if (m_Motion.IsEndMotion())
		{
			m_Motion.ChangeMotion(MOTION_WAIT);
		}
	}
	//ダメージ中の動作
	else if (m_Motion.GetMotionNo() == MOTION_DAMAGE)
	{
		//終了で待機に戻す
		if (m_Motion.IsEndMotion())
		{
			m_Motion.ChangeMotion(MOTION_WAIT);
		}
	}
	else
	{
		UpdateKey();
	}
	//移動更新
	UpdateMove();

	//実際に座標を移動させる
    CCharacter::Update();

	//画面外で落下としてHPを０にする
	if (m_Pos.y >= g_pGraphics->GetTargetHeight() && m_HP > 0)
	{
		m_HP = 0;
		//爆発エフェクトを発生させる
		m_pEndEffect = m_pEffectManager->Start(
            m_Pos.x + m_SrcRect.GetWidth() * 0.5f,
            m_Pos.y + m_SrcRect.GetHeight() * 0.5f,
            EFC_EXPLOSION02
        );
	}
	//アニメーションの更新
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
	//ダメージのインターバルを減らす
	if (m_DamageWait > 0)
	{
		m_DamageWait--;
	}
}

/**
 * キー入力による動作更新
 *
 */
void CPlayer::UpdateKey(void) {
	//キーボードでの移動
	//入力で直接座標を動かすのではなく、速度を変化させる。
	//攻撃中は移動できないようにする
	if (g_pInput->IsKeyHold(MOFKEY_LEFT))
	{
		m_Move.x -= PLAYER_SPEED;
		m_bReverse = true;
		m_bMove = true;
		if (m_Move.x < -PLAYER_MAXSPEED)
		{
			m_Move.x = -PLAYER_MAXSPEED;
		}
		if (m_Motion.GetMotionNo() == MOTION_WAIT)
		{
			m_Motion.ChangeMotion(MOTION_MOVE);
		}
	}
	else if (g_pInput->IsKeyHold(MOFKEY_RIGHT))
	{
		m_Move.x += PLAYER_SPEED;
		m_bReverse = false;
		m_bMove = true;
		if (m_Move.x > PLAYER_MAXSPEED)
		{
			m_Move.x = PLAYER_MAXSPEED;
		}
		if (m_Motion.GetMotionNo() == MOTION_WAIT)
		{
			m_Motion.ChangeMotion(MOTION_MOVE);
		}
	}
	//上キーでジャンプ
	if (g_pInput->IsKeyHold(MOFKEY_UP) && !m_bJump)
	{
		m_bJump = true;
		m_Move.y = PLAYER_JUMP;
		m_Motion.ChangeMotion(MOTION_JUMPSTART);
	}
	//SPACEキーで攻撃
	if (g_pInput->IsKeyPush(MOFKEY_SPACE))
	{
		m_Motion.ChangeMotion(MOTION_ATTACK);
	}
}

/**
 * 移動更新
 *
 */
void CPlayer::UpdateMove(void) {
	//このフレームでの移動入力がなければ減速処理を実行する
	if (!m_bMove)
	{
		if (m_Move.x > 0)
		{
			m_Move.x -= PLAYER_SPEED;
			if (m_Move.x <= 0)
			{
				m_Move.x = 0;
			}
		}
		else if (m_Move.x < 0)
		{
			m_Move.x += PLAYER_SPEED;
			if (m_Move.x >= 0)
			{
				m_Move.x = 0;
			}
		}
		else if (m_Motion.GetMotionNo() == MOTION_MOVE)
		{
			m_Motion.ChangeMotion(MOTION_WAIT);
		}
	}
	//重力により下に少しずつ下がる
	m_Move.y += GRAVITY;
	if (m_Move.y >= 20.0f)
	{
		m_Move.y = 20.0f;
	}
}

/**
 * ステージとの当たり
 *
 * 引数
 * [in]			ox					X埋まり量
 * [in]			oy					Y埋まり量
 */
void CPlayer::CollisionStage(float ox, float oy) {
	m_Pos.x += ox;
	m_Pos.y += oy;
	//落下中の下埋まり、ジャンプ中の上埋まりの場合は移動を初期化する。
	if (oy < 0 && m_Move.y > 0)
	{
		m_Move.y = 0;
		if (m_bJump)
		{
			m_bJump = false;
			m_Motion.ChangeMotion(MOTION_JUMPEND);
		}
	}
	else if (oy > 0 && m_Move.y < 0)
	{
		m_Move.y = 0;
	}
	//左移動中の左埋まり、右移動中の右埋まりの場合は移動を初期化する。
	if (ox < 0 && m_Move.x > 0)
	{
		m_Move.x = 0;
	}
	else if (ox > 0 && m_Move.x < 0)
	{
		m_Move.x = 0;
	}
}

/**
 * 当たり判定
 * 引数の敵に対して矩形同士の当たり判定を実行する。
 * 当たっていた場合はプレイヤーの状態を変更する
 *
 * 引数
 * [in]			ene				判定を行う敵
 *
 * 戻り値
 * 当たっている場合はtrue、当たっていなければfalseを返す
 */
bool CPlayer::CollisionEnemy(CEnemy& ene) {
	if (!ene.GetShow())
	{
		return false;
	}
	//HPがなくなると当たり判定しない
	if (m_HP <= 0)
	{
		return false;
	}
	//ダメージ中のため当たり判定をおこなわない
	if (m_DamageWait > 0 || ene.GetDamageWait() > 0)
	{
		return false;
	}
	//敵の矩形と自分の矩形でダメージ
	CRectangle prec = GetRect();
	CRectangle erec = ene.GetRect();
	if (prec.CollisionRect(erec))
	{
		m_HP -= 5;
		m_DamageWait = 60;
		if (prec.Left < erec.Left)
		{
			m_Move.x = -5.0f;
			m_bReverse = false;
		}
		else
		{
			m_Move.x = 5.0f;
			m_bReverse = true;
		}
		m_Motion.ChangeMotion(MOTION_DAMAGE);
		if (m_HP <= 0)
		{
			//爆発エフェクトを発生させる
			m_pEndEffect = m_pEffectManager->Start(
                m_Pos.x + m_SrcRect.GetWidth() * 0.5f,
                m_Pos.y + m_SrcRect.GetHeight() * 0.5f,
                EFC_EXPLOSION02
            );
		}
		else
		{
			//ダメージエフェクトを発生させる
			m_pEffectManager->Start(
                m_Pos.x + m_SrcRect.GetWidth() * 0.5f,
                m_Pos.y + m_SrcRect.GetHeight() * 0.5f,
                EFC_DAMAGE
            );
		}
		return true;
	}
	//攻撃中の場合のみ攻撃との当たり判定を実行
	if (m_Motion.GetMotionNo() != MOTION_ATTACK)
	{
		return false;
	}
	//敵の矩形と自分の攻撃矩形で敵がダメージ
	prec = GetAttackRect();
	if (prec.CollisionRect(erec))
	{
		ene.Damage(5, m_bReverse);
		return true;
	}
	return false;
}

/**
 * 当たり判定
 * 引数のアイテムに対して矩形同士の当たり判定を実行する。
 * 当たっていた場合はプレイヤーの状態を変更する
 *
 * 引数
 * [in]			itm				判定を行うアイテム
 *
 * 戻り値
 * 当たっている場合はtrue、当たっていなければfalseを返す
 */
bool CPlayer::CollisionItem(CItem& itm) {
	if (!itm.GetShow())
	{
		return false;
	}
	//アイテムの矩形と自分の矩形で当たり判定
	CRectangle prec = GetRect();
	CRectangle irec = itm.GetRect();
	if (prec.CollisionRect(irec))
	{
		itm.SetShow(false);
		switch (itm.GetType())
		{
		case ITEM_RECOVER:
			m_HP += 30;
			if (m_HP >= 100)
			{
				m_HP = 100;
			}
			break;
		case ITEM_GOAL:
			m_bGoal = true;
			break;
		}
		return true;
	}
	return false;
}

/**
 * 描画
 *
 * 引数
 * [in]			wx					ワールドの変化
 * [in]			wy					ワールドの変化
 */
void CPlayer::Render(float wx, float wy) {
	//インターバル2フレームごとに描画をしない
	if (m_DamageWait % 4 >= 2)
	{
		return;
	}
	//HPがなくなると描画しない
	if (m_HP <= 0)
	{
		return;
	}
	//描画矩形
	CRectangle dr = m_SrcRect;
	//描画位置
	float px = m_Pos.x - wx;
	float py = m_Pos.y - wy;
	//反転フラグがONの場合描画矩形を反転させる
	if (m_bReverse)
	{
		float tmp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = tmp;
		if (m_Motion.GetMotionNo() == MOTION_ATTACK)
		{
			px -= PLAYER_ATTACKWIDTH;
		}
	}
	//テクスチャの描画
	m_pTexture->Render(px, py, dr);
}

/**
 * デバッグ描画
 *
 * 引数
 * [in]			wx					ワールドの変化
 * [in]			wy					ワールドの変化
 */
void CPlayer::RenderDebug(float wx, float wy) {
	//位置の描画
	CGraphicsUtilities::RenderString(10, 70, "プレイヤー位置 X : %.0f , Y : %.0f プレイヤーHP : %d",
        m_Pos.x, m_Pos.y, m_HP);
	//当たり判定の表示
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(0, 255, 0));
	//攻撃の当たり判定表示
	if (IsAttack())
	{
		CRectangle hr = GetAttackRect();
		CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(255, 0, 0));
	}
}

/**
 * 解放
 *
 */
void CPlayer::Release(void) {
	m_Motion.Release();
}
