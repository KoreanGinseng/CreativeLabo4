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
m_Actor(std::make_shared<Sample::Actor>()) ,
m_Move() ,
m_SrcRect() ,
m_pEffectManager(NULL) ,
m_pEndEffect(NULL) ,
m_pInput() ,
m_StateMachine() ,
m_HP(),
m_DamageWait(),
m_bEnd() ,
m_bGoal() {
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
	//パラメーターを生成
	m_Actor->CreateParameterMap<Sample::ReactiveParameter<int>, int, bool>();
	m_Actor->SetParameter<Sample::ReactiveParameter<int>>("HP", 100);
	m_Actor->SetParameter<int>("DamageWait", 0);
	m_Actor->SetParameter<bool>("End", false);
	m_Actor->SetParameter<bool>("Goal", false);
	m_HP = m_Actor->GetParameter<Sample::ReactiveParameter<int>>("HP");
	m_DamageWait = m_Actor->GetParameter<int>("DamageWait");
	m_bEnd = m_Actor->GetParameter<bool>("End");
	m_bGoal = m_Actor->GetParameter<bool>("Goal");
	//アニメーションを作成
	m_Motion = animCreator->Create();
	m_Actor->SetAnimationState(m_Motion);
	//ステートを作成
	m_StateMachine = std::make_shared<Sample::StateMachine>();
	m_StateMachine->AddState(Sample::State::Create<Sample::IdleState>(m_Actor, m_pInput));
	m_StateMachine->AddState(Sample::State::Create<Sample::MoveState>(m_Actor, m_pInput));
	m_StateMachine->AddState(Sample::State::Create<Sample::JumpState>(m_Actor, m_pInput));
	m_StateMachine->AddState(Sample::State::Create<Sample::AttackState>(m_Actor, m_pInput));
	m_StateMachine->AddState(Sample::State::Create<Sample::DamageState>(m_Actor, m_pInput));
	m_StateMachine->AddState(Sample::State::Create<Sample::LandingState>(m_Actor, m_pInput));
	//アクションを作成
	m_Move = Sample::Action::Create<Sample::MoveAction>();
	m_Actor->AddAction(m_Move);
	return true;
}

/**
 * 初期化
 * パラメーターや座標を初期化する。
 * プレイヤーの位置など状態を初期化したいときに実行する。
 */
void CPlayer::Initialize(void){
	m_Actor->SetPosition(200,0);
	m_Move->Reset();
	m_HP = 100;
	m_DamageWait = 0;
	m_bEnd = false;
	m_bGoal = false;
	m_pEndEffect = NULL;
	m_StateMachine->ChangeState("Idle");
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
	//ステート更新
	m_StateMachine->InputExec();
	m_StateMachine->Exec();
	//実際に座標を移動させる
	m_Move->Exec();
	//画面外で落下としてHPを０にする
	if(m_Actor->GetPositionY() >= g_pGraphics->GetTargetHeight() && m_HP > 0)
	{
		m_HP = 0;
		//爆発エフェクトを発生させる
		m_pEndEffect = m_pEffectManager->Start(m_Actor->GetPositionX() + m_SrcRect.GetWidth() * 0.5f,m_Actor->GetPositionY() + m_SrcRect.GetHeight() * 0.5f,EFC_EXPLOSION02);
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
 * ステージとの当たり
 *
 * 引数
 * [in]			ox					X埋まり量
 * [in]			oy					Y埋まり量
 */
void CPlayer::CollisionStage(float ox,float oy){
	m_Actor->GetTransform()->Move(ox, oy);
	//落下中の下埋まり、ジャンプ中の上埋まりの場合は移動を初期化する。
	if (oy < 0 && m_Move->GetSpeedY() > 0)
	{
		m_Move->SetSpeedY(0);
		m_StateMachine->CollisionEvent(Ground, nullptr);
	}
	else if (oy > 0 && m_Move->GetSpeedY() < 0)
	{
		m_Move->SetSpeedY(0);
		m_StateMachine->CollisionEvent(Ceiling, nullptr);
	}
	//左移動中の左埋まり、右移動中の右埋まりの場合は移動を初期化する。
	if (ox < 0 && m_Move->GetSpeedX() > 0)
	{
		m_Move->SetSpeedX(0);
		m_StateMachine->CollisionEvent(Wall, nullptr);
	}
	else if (ox > 0 && m_Move->GetSpeedX() < 0)
	{
		m_Move->SetSpeedX(0);
		m_StateMachine->CollisionEvent(Wall, nullptr);
	}
}

void CPlayer::Damage(int dmg, int wait, bool back) {
	m_HP -= dmg;
	m_DamageWait = wait;
	if (back)
	{
		m_Move->SetSpeed(-5.0f, false);
	}
	else
	{
		m_Move->SetSpeed(5.0f, true);
	}
	m_StateMachine->ChangeState("Damage");
	if (m_HP <= 0)
	{
		//爆発エフェクトを発生させる
		m_pEndEffect = m_pEffectManager->Start(m_Actor->GetPositionX() + m_SrcRect.GetWidth() * 0.5f, m_Actor->GetPositionY() + m_SrcRect.GetHeight() * 0.5f, EFC_EXPLOSION02);
	}
	else
	{
		//ダメージエフェクトを発生させる
		m_pEffectManager->Start(m_Actor->GetPositionX() + m_SrcRect.GetWidth() * 0.5f, m_Actor->GetPositionY() + m_SrcRect.GetHeight() * 0.5f, EFC_DAMAGE);
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
