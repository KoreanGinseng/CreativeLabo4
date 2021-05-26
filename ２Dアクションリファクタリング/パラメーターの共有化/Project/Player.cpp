#include	"Player.h"
#include	"State/IdleState.h"
#include	"State/MoveState.h"
#include	"State/JumpState.h"
#include	"State/AttackState.h"
#include	"State/DamageState.h"
#include	"State/LandingState.h"

/**
 * �R���X�g���N�^
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
 * �f�X�g���N�^
 *
 */
CPlayer::~CPlayer(){
}

/**
 * �ǂݍ���
 * ���p����e�N�X�`����ǂݍ��ށB
 */
bool CPlayer::Load(Sample::ResourcePackPtr<UsedResources>& pack, const Sample::AnimationCreatorPtr& animCreator){
	//�e�N�X�`���̓ǂݍ���
	m_Texture = pack->Get<Sample::Texture>()->Get("Player");
	//�p�����[�^�[�𐶐�
	m_Actor->CreateParameterMap<Sample::ReactiveParameter<int>, int, bool>();
	m_Actor->SetParameter<Sample::ReactiveParameter<int>>("HP", 100);
	m_Actor->SetParameter<int>("DamageWait", 0);
	m_Actor->SetParameter<bool>("End", false);
	m_Actor->SetParameter<bool>("Goal", false);
	m_HP = m_Actor->GetParameter<Sample::ReactiveParameter<int>>("HP");
	m_DamageWait = m_Actor->GetParameter<int>("DamageWait");
	m_bEnd = m_Actor->GetParameter<bool>("End");
	m_bGoal = m_Actor->GetParameter<bool>("Goal");
	//�A�j���[�V�������쐬
	m_Motion = animCreator->Create();
	m_Actor->SetAnimationState(m_Motion);
	//�X�e�[�g���쐬
	m_StateMachine = std::make_shared<Sample::StateMachine>();
	m_StateMachine->AddState(Sample::State::Create<Sample::IdleState>(m_Actor, m_pInput));
	m_StateMachine->AddState(Sample::State::Create<Sample::MoveState>(m_Actor, m_pInput));
	m_StateMachine->AddState(Sample::State::Create<Sample::JumpState>(m_Actor, m_pInput));
	m_StateMachine->AddState(Sample::State::Create<Sample::AttackState>(m_Actor, m_pInput));
	m_StateMachine->AddState(Sample::State::Create<Sample::DamageState>(m_Actor, m_pInput));
	m_StateMachine->AddState(Sample::State::Create<Sample::LandingState>(m_Actor, m_pInput));
	//�A�N�V�������쐬
	m_Move = Sample::Action::Create<Sample::MoveAction>();
	m_Actor->AddAction(m_Move);
	return true;
}

/**
 * ������
 * �p�����[�^�[����W������������B
 * �v���C���[�̈ʒu�ȂǏ�Ԃ��������������Ƃ��Ɏ��s����B
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
 * �X�V
 *
 */
void CPlayer::Update(void){
	//HP���Ȃ��Ȃ�Ɣ����̏I����ҋ@���ďI��
	if(m_HP <= 0)
	{
		if(!m_pEndEffect || !m_pEndEffect->GetShow())
		{
			m_bEnd = true;
		}
		return;
	}
	//�X�e�[�g�X�V
	m_StateMachine->InputExec();
	m_StateMachine->Exec();
	//���ۂɍ��W���ړ�������
	m_Move->Exec();
	//��ʊO�ŗ����Ƃ���HP���O�ɂ���
	if(m_Actor->GetPositionY() >= g_pGraphics->GetTargetHeight() && m_HP > 0)
	{
		m_HP = 0;
		//�����G�t�F�N�g�𔭐�������
		m_pEndEffect = m_pEffectManager->Start(m_Actor->GetPositionX() + m_SrcRect.GetWidth() * 0.5f,m_Actor->GetPositionY() + m_SrcRect.GetHeight() * 0.5f,EFC_EXPLOSION02);
	}
	//�A�j���[�V�����̍X�V
	m_Motion->Update();
	m_SrcRect = m_Motion->GetSrcRect();
	//�_���[�W�̃C���^�[�o�������炷
	if(m_DamageWait > 0)
	{
		m_DamageWait--;
	}
}

/**
 * �X�e�[�W�Ƃ̓�����
 *
 * ����
 * [in]			ox					X���܂��
 * [in]			oy					Y���܂��
 */
void CPlayer::CollisionStage(float ox,float oy){
	m_Actor->GetTransform()->Move(ox, oy);
	//�������̉����܂�A�W�����v���̏㖄�܂�̏ꍇ�͈ړ�������������B
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
	//���ړ����̍����܂�A�E�ړ����̉E���܂�̏ꍇ�͈ړ�������������B
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
		//�����G�t�F�N�g�𔭐�������
		m_pEndEffect = m_pEffectManager->Start(m_Actor->GetPositionX() + m_SrcRect.GetWidth() * 0.5f, m_Actor->GetPositionY() + m_SrcRect.GetHeight() * 0.5f, EFC_EXPLOSION02);
	}
	else
	{
		//�_���[�W�G�t�F�N�g�𔭐�������
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
 * ���
 *
 */
void CPlayer::Release(void){
	m_Texture.reset();
	m_Motion.reset();
}
