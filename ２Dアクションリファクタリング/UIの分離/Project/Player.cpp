#include	"Player.h"

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
	m_bJump = false;
	m_HP = 100;
	m_DamageWait = 0;
	m_bEnd = false;
	m_pEndEffect = NULL;
	m_bGoal = false;
	m_Motion->ChangeMotion("Wait");
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
	//�U�����A���n�̏ꍇ�̓���
	if(m_Motion->IsMotion("Attack") || m_Motion->IsMotion("JumpEnd"))
	{
		//�I���őҋ@�ɖ߂�
		if(m_Motion->IsEndMotion())
		{
			m_Motion->ChangeMotion("Wait");
		}
	}
	//�_���[�W���̓���
	else if(m_Motion->IsMotion("Damage"))
	{
		//�I���őҋ@�ɖ߂�
		if(m_Motion->IsEndMotion())
		{
			m_Motion->ChangeMotion("Wait");
		}
	}
	else
	{
		UpdateKey();
	}
	//�ړ��X�V
	UpdateMove();
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
 * �L�[���͂ɂ�铮��X�V
 *
 */
void CPlayer::UpdateKey(void){
	//�L�[�{�[�h�ł̈ړ�
	//���͂Œ��ڍ��W�𓮂����̂ł͂Ȃ��A���x��ω�������B
	//�U�����͈ړ��ł��Ȃ��悤�ɂ���
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
	//��L�[�ŃW�����v
	if(m_pInput->IsPress("Jump") && !m_bJump)
	{
		m_bJump = true;
		m_MoveY = PLAYER_JUMP;
		m_Motion->ChangeMotion("JumpStart");
	}
	//SPACE�L�[�ōU��
	if(m_pInput->IsPush("Attack"))
	{
		m_Motion->ChangeMotion("Attack");
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
			m_Motion->ChangeMotion("Wait");
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
	//���ړ����̍����܂�A�E�ړ����̉E���܂�̏ꍇ�͈ړ�������������B
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
