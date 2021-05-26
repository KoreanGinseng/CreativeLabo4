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
 * ������
 * �p�����[�^�[����W������������B
 * �v���C���[�̈ʒu�ȂǏ�Ԃ��������������Ƃ��Ɏ��s����B
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
	//�ړ��t���O�A���̃t���[���ł̈ړ�������������ۑ�
	m_bMove = false;
	//�X�e�[�g�X�V
	m_CurrentState->InputExec(this);
	m_CurrentState->Exec(this);
	//���ۂɍ��W���ړ�������
	m_PosX += m_MoveX;
	m_PosY += m_MoveY;
	//��ʊO�ŗ����Ƃ���HP���O�ɂ���
	if(m_PosY >= g_pGraphics->GetTargetHeight() && m_HP > 0)
	{
		m_HP = 0;
		//�����G�t�F�N�g�𔭐�������
		m_pEndEffect = m_pEffectManager->Start(m_PosX + m_SrcRect.GetWidth() * 0.5f,m_PosY + m_SrcRect.GetHeight() * 0.5f,EFC_EXPLOSION02);
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
 * �ړ��X�V
 *
 */
void CPlayer::UpdateMove(void){
	//���̃t���[���ł̈ړ����͂��Ȃ���Ό������������s����
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
	//�d�͂ɂ�艺�ɏ�����������
	m_MoveY += GRAVITY;
	if(m_MoveY >= 20.0f)
	{
		m_MoveY = 20.0f;
	}
}

/**
 * @brief		����
 * @param[in]	val			������
 * @param[in]	maxspeed	�ő呬�x
 * @param[in]	rev			���]�t���O
 */
void CPlayer::Acceleration(float val, float maxspeed, bool rev) {
	m_MoveX += val;
	m_MoveX = ((m_MoveX > maxspeed) ? maxspeed : ((m_MoveX < -maxspeed) ? -maxspeed : m_MoveX));
	m_bReverse = rev;
	m_bMove = true;
}

/**
 * �X�e�[�W�Ƃ̓�����
 *
 * ����
 * [in]			ox					X���܂��
 * [in]			oy					Y���܂��
 */
void CPlayer::CollisionStage(float ox,float oy){
	m_PosX += ox;
	m_PosY += oy;
	//�������̉����܂�A�W�����v���̏㖄�܂�̏ꍇ�͈ړ�������������B
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
	//���ړ����̍����܂�A�E�ړ����̉E���܂�̏ꍇ�͈ړ�������������B
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
		//�����G�t�F�N�g�𔭐�������
		m_pEndEffect = m_pEffectManager->Start(m_PosX + m_SrcRect.GetWidth() * 0.5f, m_PosY + m_SrcRect.GetHeight() * 0.5f, EFC_EXPLOSION02);
	}
	else
	{
		//�_���[�W�G�t�F�N�g�𔭐�������
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
 * ���
 *
 */
void CPlayer::Release(void){
	m_Texture.reset();
	m_Motion.reset();
}
