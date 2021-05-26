#pragma once

#include	"Mof.h"
#include	"GameDefine.h"
#include	"Enemy.h"
#include	"EffectManager.h"
#include	"Item.h"

#include	"Common/ReactiveParameter.h"

#include	"Input/InputManager.h"

#include	"Animation/IAnimationState.h"
#include	"Animation/IAnimationCreator.h"

#include	"Common/Rectangle.h"

#include	"Resource/ResourceManager.h"

#include	"Render/RenderCommandTask.h"
#include	"Render/StringRenderCommand.h"
#include	"Render/RectRenderCommand.h"
#include	"Render/TextureRenderCommand.h"

#include	"State/State.h"

//�ړ����x
#define		PLAYER_SPEED			0.3f

//�ړ��ő呬�x
#define		PLAYER_MAXSPEED			10.0f

//�W�����v����
#define		PLAYER_JUMP				-10.0f

//�U����
#define		PLAYER_ATTACKWIDTH		30

//�����蔻�茸����
#define		PLAYER_RECTDECREASE		12

enum PlayerCollisionType {
	Ground,
	Wall,
	Ceiling,
};

class CPlayer {
private:
	Sample::TexturePtr			m_Texture;
	Sample::AnimationStatePtr	m_Motion;
	float					m_PosX;
	float					m_PosY;
	bool					m_bMove;
	float					m_MoveX;
	float					m_MoveY;

	bool					m_bReverse;
	Sample::Rectangle		m_SrcRect;

	Sample::ReactiveParameter<int>		m_HP;
	int						m_DamageWait;
	
	CEffectManager*			m_pEffectManager;
	
	CEffect*				m_pEndEffect;
	bool					m_bEnd;

	bool					m_bGoal;

	Sample::InputPtr					m_pInput;

	std::unordered_map<std::string, Sample::StatePtr>		m_StateMap;
	Sample::StatePtr										m_CurrentState;
public:
	CPlayer();
	~CPlayer();
	bool Load(Sample::ResourcePackPtr<UsedResources>& pack, const Sample::AnimationCreatorPtr& animCreator);
	void Initialize(void);
	void Update(void);

	/**
	 * @brief		�X�e�[�g�̕ύX
	 */
	void ChangeState(const Sample::StateKeyType& key)
	{
		if (m_CurrentState)
		{
			m_CurrentState->End(this);
		}
		m_CurrentState = m_StateMap[key];
		m_CurrentState->Start(this);
	}

	void UpdateMove(void);

	/**
	 * @brief		����
	 * @param[in]	val			������
	 * @param[in]	maxspeed	�ő呬�x
	 * @param[in]	rev			���]�t���O
	 */
	void Acceleration(float val, float maxspeed, bool rev);

	/**
	 * @brief		���x�ݒ�
	 * @param[in]	val		���x
	 */
	void SetSpeedX(float val) {
		m_MoveX = val;
	}

	/**
	 * @brief		���x�ݒ�
	 * @param[in]	val		���x
	 */
	void SetSpeedY(float val) {
		m_MoveY = val;
	}

	void CollisionStage(float ox,float oy);

	void Damage(int dmg, int wait, bool back);
	void Heal(int val);

	void Release(void);
	bool IsAttack(){ return m_Motion->IsMotion("Attack"); }
	Sample::Rectangle GetRect(){
		if(IsAttack())
		{
			return Sample::Rectangle(m_PosX + PLAYER_RECTDECREASE,m_PosY + PLAYER_RECTDECREASE,m_PosX + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE - PLAYER_ATTACKWIDTH,m_PosY + m_SrcRect.GetHeight());
		}
		return Sample::Rectangle(m_PosX + PLAYER_RECTDECREASE,m_PosY + PLAYER_RECTDECREASE,m_PosX + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE,m_PosY + m_SrcRect.GetHeight());
	}
	Sample::Rectangle GetAttackRect(){
		//���]��
		if(m_bReverse)
		{
			return Sample::Rectangle(m_PosX - PLAYER_ATTACKWIDTH,m_PosY,m_PosX + PLAYER_RECTDECREASE,m_PosY + m_SrcRect.GetHeight());
		}
		return Sample::Rectangle(m_PosX + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE - PLAYER_ATTACKWIDTH,m_PosY,m_PosX + m_SrcRect.GetWidth(),m_PosY + m_SrcRect.GetHeight());
	}
	void SetEffectManager(CEffectManager* pmng){ m_pEffectManager = pmng; }
	bool IsEnd(void){ return m_bEnd; }
	bool IsGoal(void){ return m_bGoal; }


	/**
	 * @brief		���͋@�\�ݒ�
	 * @param[in]	ptr		���p�������
	 */
	void SetInput(const Sample::InputPtr& ptr) {
		m_pInput = ptr;
	}

	/**
	 * @brief		HP�ω��ʒm
	 */
	Sample::IObservable<int>* GetHPSubject() { return &m_HP; }

	/**
	 * @brief		���[�V�������
	 */
	Sample::AnimationStatePtr GetAnimationState() { return m_Motion; }

	void SetGoal(bool val) { m_bGoal = val; }


	float GetPosX() const noexcept {
		return m_PosX;
	}
	float GetPosY() const noexcept {
		return m_PosY;
	}
	int GetHP() const noexcept {
		return m_HP;
	}
	int GetDamageWait() const noexcept {
		return m_DamageWait;
	}
	const Sample::Rectangle& GetSrcRect() const noexcept {
		return m_SrcRect;
	}
	const Sample::TexturePtr& GetTexture() const noexcept {
		return m_Texture;
	}
	bool IsReverse() const noexcept {
		return m_bReverse;
	}
};