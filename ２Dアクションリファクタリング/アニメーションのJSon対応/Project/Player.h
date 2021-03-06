#pragma once

#include	"Mof.h"
#include	"GameDefine.h"
#include	"Enemy.h"
#include	"EffectManager.h"
#include	"Item.h"

#include	"Input/InputManager.h"

#include	"Animation/IAnimationState.h"
#include	"Animation/IAnimationCreator.h"

#include	"Common/Rectangle.h"

//?ړ????x
#define		PLAYER_SPEED			0.3f

//?ړ??ő呬?x
#define		PLAYER_MAXSPEED			10.0f

//?W?????v????
#define		PLAYER_JUMP				-10.0f

//?U????
#define		PLAYER_ATTACKWIDTH		30

//?????蔻?茸????
#define		PLAYER_RECTDECREASE		12

class CPlayer {
private:
	CTexture				m_Texture;
	Sample::AnimationStatePtr	m_Motion;
	float					m_PosX;
	float					m_PosY;
	bool					m_bMove;
	float					m_MoveX;
	float					m_MoveY;
	bool					m_bJump;
	bool					m_bReverse;
	Sample::Rectangle		m_SrcRect;
	
	int						m_HP;
	int						m_DamageWait;
	
	CTexture				m_FrameTexture;
	CTexture				m_HPTexture;
	
	CEffectManager*			m_pEffectManager;
	
	CEffect*				m_pEndEffect;
	bool					m_bEnd;

	bool					m_bGoal;

	Sample::InputPtr					m_pInput;
public:
	CPlayer();
	~CPlayer();
	bool Load(const Sample::AnimationCreatorPtr& animCreator);
	void Initialize(void);
	void Update(void);
	void UpdateKey(void);
	void UpdateMove(void);
	void CollisionStage(float ox,float oy);
	bool CollisionEnemy(CEnemy& ene);
	bool CollisionItem(CItem& itm);
	void Render(float wx,float wy);
	void RenderStatus(void);
	void RenderDebug(float wx,float wy);
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
		//???]??
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
	 * @brief		???͋@?\?ݒ?
	 * @param[in]	ptr		???p????????
	 */
	void SetInput(const Sample::InputPtr& ptr) {
		m_pInput = ptr;
	}

};