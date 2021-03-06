#include	"Player.h"

/**
 * コンストラクタ
 *
 */
CPlayer::CPlayer() :
m_Texture() ,
m_Motion() ,
m_PosX(0.0f) ,
m_PosY(0.0f) ,
m_bMove(false) ,
m_MoveX(0.0f) ,
m_MoveY(0.0f) ,
m_bJump(false) ,
m_bReverse(false) ,
m_SrcRect() ,
m_HP(100) ,
m_DamageWait(0) ,
m_FrameTexture() ,
m_HPTexture() ,
m_bEnd(false) ,
m_pEndEffect(NULL) ,
m_bGoal(false) {
}

/**
 * デストラクタ
 *
 */
CPlayer::~CPlayer(){
}

/**
 * 読み込み
 * 利用するテクスチャを読み込む。
 */
bool CPlayer::Load(Sample::ResourcePackPtr<UsedResources>& pack, const Sample::AnimationCreatorPtr& animCreator){
	//テクスチャの読み込み
	m_Texture = pack->Get<Sample::Texture>()->Get("Player");
	m_FrameTexture = pack->Get<Sample::Texture>()->Get("Frame");
	m_HPTexture = pack->Get<Sample::Texture>()->Get("HP");
	//アニメーションを作成
	m_Motion = animCreator->Create();
	return true;
}

/**
 * 初期化
 * パラメーターや座標を初期化する。
 * プレイヤーの位置など状態を初期化したいときに実行する。
 */
void CPlayer::Initialize(void){
	m_PosX = 200;
	m_PosY = 0;
	m_bMove = false;
	m_MoveX = 0.0f;
	m_MoveY = 0.0f;
	m_bReverse = false;
	m_bJump = false;
	m_HP = 100;
	m_DamageWait = 0;
	m_bEnd = false;
	m_pEndEffect = NULL;
	m_bGoal = false;
	m_Motion->ChangeMotion("Wait");
}

/**
 * 更新
 *
 */
void CPlayer::Update(void){
	//HPがなくなると爆発の終了を待機して終了
	if(m_HP <= 0)
	{
		if(!m_pEndEffect || !m_pEndEffect->GetShow())
		{
			m_bEnd = true;
		}
		return;
	}
	//移動フラグ、このフレームでの移動があったかを保存
	m_bMove = false;
	//攻撃中、着地の場合の動作
	if(m_Motion->IsMotion("Attack") || m_Motion->IsMotion("JumpEnd"))
	{
		//終了で待機に戻す
		if(m_Motion->IsEndMotion())
		{
			m_Motion->ChangeMotion("Wait");
		}
	}
	//ダメージ中の動作
	else if(m_Motion->IsMotion("Damage"))
	{
		//終了で待機に戻す
		if(m_Motion->IsEndMotion())
		{
			m_Motion->ChangeMotion("Wait");
		}
	}
	else
	{
		UpdateKey();
	}
	//移動更新
	UpdateMove();
	//実際に座標を移動させる
	m_PosX += m_MoveX;
	m_PosY += m_MoveY;
	//画面外で落下としてHPを０にする
	if(m_PosY >= g_pGraphics->GetTargetHeight() && m_HP > 0)
	{
		m_HP = 0;
		//爆発エフェクトを発生させる
		m_pEndEffect = m_pEffectManager->Start(m_PosX + m_SrcRect.GetWidth() * 0.5f,m_PosY + m_SrcRect.GetHeight() * 0.5f,EFC_EXPLOSION02);
	}
	//アニメーションの更新
	m_Motion->Update();
	m_SrcRect = m_Motion->GetSrcRect();
	//ダメージのインターバルを減らす
	if(m_DamageWait > 0)
	{
		m_DamageWait--;
	}
}

/**
 * キー入力による動作更新
 *
 */
void CPlayer::UpdateKey(void){
	//キーボードでの移動
	//入力で直接座標を動かすのではなく、速度を変化させる。
	//攻撃中は移動できないようにする
	if(m_pInput->IsNegativePress("Horizontal"))
	{
		m_MoveX -= PLAYER_SPEED;
		m_bReverse = true;
		m_bMove = true;
		if(m_MoveX < -PLAYER_MAXSPEED)
		{
			m_MoveX = -PLAYER_MAXSPEED;
		}
		if(m_Motion->IsMotion("Wait"))
		{
			m_Motion->ChangeMotion("Move");
		}
	}
	else if(m_pInput->IsPress("Horizontal"))
	{
		m_MoveX += PLAYER_SPEED;
		m_bReverse = false;
		m_bMove = true;
		if(m_MoveX > PLAYER_MAXSPEED)
		{
			m_MoveX = PLAYER_MAXSPEED;
		}
		if(m_Motion->IsMotion("Wait"))
		{
			m_Motion->ChangeMotion("Move");
		}
	}
	//上キーでジャンプ
	if(m_pInput->IsPress("Jump") && !m_bJump)
	{
		m_bJump = true;
		m_MoveY = PLAYER_JUMP;
		m_Motion->ChangeMotion("JumpStart");
	}
	//SPACEキーで攻撃
	if(m_pInput->IsPush("Attack"))
	{
		m_Motion->ChangeMotion("Attack");
	}
}

/**
 * 移動更新
 *
 */
void CPlayer::UpdateMove(void){
	//このフレームでの移動入力がなければ減速処理を実行する
	if(!m_bMove)
	{
		if(m_MoveX > 0)
		{
			m_MoveX -= PLAYER_SPEED;
			if(m_MoveX <= 0)
			{
				m_MoveX = 0;
			}
		}
		else if(m_MoveX < 0)
		{
			m_MoveX += PLAYER_SPEED;
			if(m_MoveX >= 0)
			{
				m_MoveX = 0;
			}
		}
		else if(m_Motion->IsMotion("Move"))
		{
			m_Motion->ChangeMotion("Wait");
		}
	}
	//重力により下に少しずつ下がる
	m_MoveY += GRAVITY;
	if(m_MoveY >= 20.0f)
	{
		m_MoveY = 20.0f;
	}
}

/**
 * ステージとの当たり
 *
 * 引数
 * [in]			ox					X埋まり量
 * [in]			oy					Y埋まり量
 */
void CPlayer::CollisionStage(float ox,float oy){
	m_PosX += ox;
	m_PosY += oy;
	//落下中の下埋まり、ジャンプ中の上埋まりの場合は移動を初期化する。
	if(oy < 0 && m_MoveY > 0)
	{
		m_MoveY = 0;
		if(m_bJump)
		{
			m_bJump = false;
			m_Motion->ChangeMotion("JumpEnd");
		}
	}
	else if(oy > 0 && m_MoveY < 0)
	{
		m_MoveY = 0;
	}
	//左移動中の左埋まり、右移動中の右埋まりの場合は移動を初期化する。
	if(ox < 0 && m_MoveX > 0)
	{
		m_MoveX = 0;
	}
	else if(ox > 0 && m_MoveX < 0)
	{
		m_MoveX = 0;
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
bool CPlayer::CollisionEnemy(CEnemy& ene){
	if(!ene.GetShow())
	{
		return false;
	}
	//HPがなくなると当たり判定しない
	if(m_HP <= 0)
	{
		return false;
	}
	//ダメージ中のため当たり判定をおこなわない
	if(m_DamageWait > 0 || ene.GetDamageWait() > 0)
	{
		return false;
	}
	//敵の矩形と自分の矩形でダメージ
	Sample::Rectangle prec = GetRect();
	Sample::Rectangle erec = ene.GetRect();
	if(prec.CollisionRect(erec))
	{
		m_HP -= 5;
		m_DamageWait = 60;
		if(prec.Left < erec.Left)
		{
			m_MoveX = -5.0f;
			m_bReverse = false;
		}
		else
		{
			m_MoveX = 5.0f;
			m_bReverse = true;
		}
		m_Motion->ChangeMotion("Damage");
		if(m_HP <= 0)
		{
			//爆発エフェクトを発生させる
			m_pEndEffect = m_pEffectManager->Start(m_PosX + m_SrcRect.GetWidth() * 0.5f,m_PosY + m_SrcRect.GetHeight() * 0.5f,EFC_EXPLOSION02);
		}
		else
		{
			//ダメージエフェクトを発生させる
			m_pEffectManager->Start(m_PosX + m_SrcRect.GetWidth() * 0.5f,m_PosY + m_SrcRect.GetHeight() * 0.5f,EFC_DAMAGE);
		}
		return true;
	}
	//攻撃中の場合のみ攻撃との当たり判定を実行
	if(!m_Motion->IsMotion("Attack"))
	{
		return false;
	}
	//敵の矩形と自分の攻撃矩形で敵がダメージ
	prec = GetAttackRect();
	if(prec.CollisionRect(erec))
	{
		ene.Damage(5,m_bReverse);
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
bool CPlayer::CollisionItem(CItem& itm){
	if(!itm.GetShow())
	{
		return false;
	}
	//アイテムの矩形と自分の矩形で当たり判定
	Sample::Rectangle prec = GetRect();
	Sample::Rectangle irec = itm.GetRect();
	if(prec.CollisionRect(irec))
	{
		itm.SetShow(false);
		switch(itm.GetType())
		{
			case ITEM_RECOVER:
				m_HP += 30;
				if(m_HP >= 100)
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
 * ステータス描画
 *
 */
void CPlayer::RenderStatus(Sample::RenderCommandTaskPtr& task){
	//HPに応じて矩形の幅を変化させる
	Sample::Rectangle rec(0,0,532 * (m_HP * 0.01f),64);
	task->Push(Sample::TextureRenderCommand::Create(248, 20, rec, m_HPTexture), 1);
	task->Push(Sample::TextureRenderCommand::Create(0, 0, m_FrameTexture), 1);
}

/**
 * デバッグ描画
 *
 * 引数
 * [in]			wx					ワールドの変化
 * [in]			wy					ワールドの変化
 */
void CPlayer::RenderDebug(float wx,float wy, Sample::RenderCommandTaskPtr& task){
	//位置の描画
	task->Push(Sample::StringRenderCommand::Create(wx, wy, "プレイヤー位置 X : %.0f , Y : %.0f プレイヤーHP : %d", m_PosX, m_PosY, m_HP), 0);
	//当たり判定の表示
	Sample::Rectangle hr = GetRect();
	task->Push(Sample::RectRenderCommand::Create(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, 0xFF00FF00), 0);
	//攻撃の当たり判定表示
	if(IsAttack())
	{
		Sample::Rectangle hr = GetAttackRect();
		task->Push(Sample::RectRenderCommand::Create(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, 0xFFFF0000), 0);
	}
}

/**
 * 解放
 *
 */
void CPlayer::Release(void){
	m_Texture.reset();
	m_Motion.reset();
	m_FrameTexture.reset();
	m_HPTexture.reset();
}
