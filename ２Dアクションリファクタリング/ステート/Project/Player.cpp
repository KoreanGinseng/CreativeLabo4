#include	"Player.h"
#include	"State/IdleState.h"
#include	"State/MoveState.h"
#include	"State/JumpState.h"
#include	"State/AttackState.h"
#include	"State/DamageState.h"
#include	"State/LandingState.h"

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
m_bReverse(false) ,
m_SrcRect() ,
m_HP(100) ,
m_DamageWait(0) ,
m_pEffectManager(NULL) ,
m_bEnd(false) ,
m_pEndEffect(NULL) ,
m_bGoal(false) ,
m_pInput() ,
m_StateMap() ,
m_CurrentState() {
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
	//ステートを作成
	auto& idleState = Sample::State::Create<Sample::IdleState>(m_pInput);
	m_StateMap[idleState->GetKey()] = idleState;
	auto& moveState = Sample::State::Create<Sample::MoveState>(m_pInput);
	m_StateMap[moveState->GetKey()] = moveState;
	auto& jumpState = Sample::State::Create<Sample::JumpState>(m_pInput);
	m_StateMap[jumpState->GetKey()] = jumpState;
	auto& attackState = Sample::State::Create<Sample::AttackState>(m_pInput);
	m_StateMap[attackState->GetKey()] = attackState;
	auto& damageState = Sample::State::Create<Sample::DamageState>(m_pInput);
	m_StateMap[damageState->GetKey()] = damageState;
	auto& landingState = Sample::State::Create<Sample::LandingState>(m_pInput);
	m_StateMap[landingState->GetKey()] = landingState;
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
	m_HP = 100;
	m_DamageWait = 0;
	m_bEnd = false;
	m_pEndEffect = NULL;
	m_bGoal = false;
	ChangeState("Idle");
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
	//ステート更新
	m_CurrentState->InputExec(this);
	m_CurrentState->Exec(this);
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
			ChangeState("Idle");
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
 * @brief		加速
 * @param[in]	val			加速量
 * @param[in]	maxspeed	最大速度
 * @param[in]	rev			反転フラグ
 */
void CPlayer::Acceleration(float val, float maxspeed, bool rev) {
	m_MoveX += val;
	m_MoveX = ((m_MoveX > maxspeed) ? maxspeed : ((m_MoveX < -maxspeed) ? -maxspeed : m_MoveX));
	m_bReverse = rev;
	m_bMove = true;
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
		m_CurrentState->CollisionEvent(this, Ground, nullptr);
	}
	else if(oy > 0 && m_MoveY < 0)
	{
		m_MoveY = 0;
		m_CurrentState->CollisionEvent(this, Ceiling, nullptr);
	}
	//左移動中の左埋まり、右移動中の右埋まりの場合は移動を初期化する。
	if(ox < 0 && m_MoveX > 0)
	{
		m_MoveX = 0;
		m_CurrentState->CollisionEvent(this, Wall, nullptr);
	}
	else if(ox > 0 && m_MoveX < 0)
	{
		m_MoveX = 0;
		m_CurrentState->CollisionEvent(this, Wall, nullptr);
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
	ChangeState("Damage");
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
