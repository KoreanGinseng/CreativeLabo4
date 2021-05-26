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

void CPlayer::Damage(int dmg, int wait, bool back) {
	m_HP -= dmg;
	m_DamageWait = wait;
	if (back)
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
	if (m_HP <= 0)
	{
		//爆発エフェクトを発生させる
		m_pEndEffect = m_pEffectManager->Start(m_PosX + m_SrcRect.GetWidth() * 0.5f, m_PosY + m_SrcRect.GetHeight() * 0.5f, EFC_EXPLOSION02);
	}
	else
	{
		//ダメージエフェクトを発生させる
		m_pEffectManager->Start(m_PosX + m_SrcRect.GetWidth() * 0.5f, m_PosY + m_SrcRect.GetHeight() * 0.5f, EFC_DAMAGE);
	}
}

void CPlayer::Heal(int val) {
	if (m_HP + val >= 100)
	{
		m_HP = 100;
	}
	else
	{
		m_HP += val;
	}
}

/**
 * 解放
 *
 */
void CPlayer::Release(void){
	m_Texture.reset();
	m_Motion.reset();
}
