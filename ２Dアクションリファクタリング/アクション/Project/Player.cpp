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
m_Transform(std::make_shared<Sample::Transform>()) ,
m_Move() ,
m_SrcRect() ,
m_HP(100) ,
m_DamageWait(0) ,
m_pEffectManager(NULL) ,
m_bEnd(false) ,
m_pEndEffect(NULL) ,
m_bGoal(false) ,
m_pInput() ,
m_StateMachine() {
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
	//�A�j���[�V�������쐬
	m_Motion = animCreator->Create();
	//�X�e�[�g���쐬
	m_StateMachine = std::make_shared<Sample::StateMachine>();
	m_StateMachine->AddState(Sample::State::Create<Sample::IdleState>(m_pInput));
	m_StateMachine->AddState(Sample::State::Create<Sample::MoveState>(m_pInput));
	m_StateMachine->AddState(Sample::State::Create<Sample::JumpState>(m_pInput));
	m_StateMachine->AddState(Sample::State::Create<Sample::AttackState>(m_pInput));
	m_StateMachine->AddState(Sample::State::Create<Sample::DamageState>(m_pInput));
	m_StateMachine->AddState(Sample::State::Create<Sample::LandingState>(m_pInput));
	//�A�N�V�������쐬
	m_Move = Sample::Action::Create<Sample::MoveAction>(m_Transform, m_Motion);
	return true;
}

/**
 * ������
 * �p�����[�^�[����W������������B
 * �v���C���[�̈ʒu�ȂǏ�Ԃ��������������Ƃ��Ɏ��s����B
 */
void CPlayer::Initialize(void){
	m_Transform->SetPosition(200,0);
	m_Move->Reset();
	m_HP = 100;
	m_DamageWait = 0;
	m_bEnd = false;
	m_pEndEffect = NULL;
	m_bGoal = false;
	m_StateMachine->ChangeState(this, "Idle");
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
	m_StateMachine->InputExec(this);
	m_StateMachine->Exec(this);
	//���ۂɍ��W���ړ�������
	m_Move->Exec();
	//��ʊO�ŗ����Ƃ���HP���O�ɂ���
	if(m_Transform->GetPositionY() >= g_pGraphics->GetTargetHeight() && m_HP > 0)
	{
		m_HP = 0;
		//�����G�t�F�N�g�𔭐�������
		m_pEndEffect = m_pEffectManager->Start(m_Transform->GetPositionX() + m_SrcRect.GetWidth() * 0.5f,m_Transform->GetPositionY() + m_SrcRect.GetHeight() * 0.5f,EFC_EXPLOSION02);
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
	m_Transform->Move(ox, oy);
	//�������̉����܂�A�W�����v���̏㖄�܂�̏ꍇ�͈ړ�������������B
	if (oy < 0 && m_Move->GetSpeedY() > 0)
	{
		m_Move->SetSpeedY(0);
		m_StateMachine->CollisionEvent(this, Ground, nullptr);
	}
	else if (oy > 0 && m_Move->GetSpeedY() < 0)
	{
		m_Move->SetSpeedY(0);
		m_StateMachine->CollisionEvent(this, Ceiling, nullptr);
	}
	//���ړ����̍����܂�A�E�ړ����̉E���܂�̏ꍇ�͈ړ�������������B
	if (ox < 0 && m_Move->GetSpeedX() > 0)
	{
		m_Move->SetSpeedX(0);
		m_StateMachine->CollisionEvent(this, Wall, nullptr);
	}
	else if (ox > 0 && m_Move->GetSpeedX() < 0)
	{
		m_Move->SetSpeedX(0);
		m_StateMachine->CollisionEvent(this, Wall, nullptr);
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
	m_StateMachine->ChangeState(this, "Damage");
	if (m_HP <= 0)
	{
		//�����G�t�F�N�g�𔭐�������
		m_pEndEffect = m_pEffectManager->Start(m_Transform->GetPositionX() + m_SrcRect.GetWidth() * 0.5f, m_Transform->GetPositionY() + m_SrcRect.GetHeight() * 0.5f, EFC_EXPLOSION02);
	}
	else
	{
		//�_���[�W�G�t�F�N�g�𔭐�������
		m_pEffectManager->Start(m_Transform->GetPositionX() + m_SrcRect.GetWidth() * 0.5f, m_Transform->GetPositionY() + m_SrcRect.GetHeight() * 0.5f, EFC_DAMAGE);
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
