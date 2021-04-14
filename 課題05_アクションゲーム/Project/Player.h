#pragma once

#include	"Mof.h"
#include	"GameDefine.h"
#include	"Enemy.h"
#include	"EffectManager.h"
#include	"Item.h"
#include    "PlayerDefine.h"
#include    "Character.h"

class CPlayer : public CCharacter {
private:
	CSpriteMotionController	m_Motion;
	bool					m_bMove;
	bool					m_bJump;
	bool					m_bReverse;
	CRectangle				m_SrcRect;
	
	CEffectManager*			m_pEffectManager;
	
	CEffect*				m_pEndEffect;
	bool					m_bEnd;

	bool					m_bGoal;

	//ÉÇÅ[ÉVÉáÉìéÌóﬁíËã`
	enum tag_MOTION {
		MOTION_WAIT,
		MOTION_MOVE,
		MOTION_JUMPSTART,
		MOTION_JUMPEND,
		MOTION_ATTACK,
		MOTION_DAMAGE,

		MOTION_COUNT,
	};
public:
	CPlayer();
	~CPlayer();
    bool Load(void);
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void UpdateKey(void) override;
	virtual void UpdateMove(void) override;
	void CollisionStage(float ox,float oy);
	bool CollisionEnemy(CEnemy& ene);
	bool CollisionItem(CItem& itm);
	virtual void Render(float wx,float wy);
	void RenderDebug(float wx,float wy);
	void Release(void);
	bool IsAttack(){ return m_Motion.GetMotionNo() == MOTION_ATTACK; }
	virtual CRectangle GetRect(void) override {
		if(IsAttack())
		{
			return CRectangle(
                m_Pos.x + PLAYER_RECTDECREASE,
                m_Pos.y + PLAYER_RECTDECREASE,
                m_Pos.x + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE - PLAYER_ATTACKWIDTH,
                m_Pos.y + m_SrcRect.GetHeight()
            );
		}
		return CRectangle(
            m_Pos.x + PLAYER_RECTDECREASE,
            m_Pos.y + PLAYER_RECTDECREASE,
            m_Pos.x + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE,
            m_Pos.y + m_SrcRect.GetHeight()
        );
	}
	CRectangle GetAttackRect(void) {
		//îΩì]íÜ
		if(m_bReverse)
		{
			return CRectangle(
                m_Pos.x - PLAYER_ATTACKWIDTH,
                m_Pos.y,
                m_Pos.x + PLAYER_RECTDECREASE,
                m_Pos.y + m_SrcRect.GetHeight()
            );
		}
		return CRectangle(
            m_Pos.x + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE - PLAYER_ATTACKWIDTH,
            m_Pos.y,
            m_Pos.x + m_SrcRect.GetWidth(),
            m_Pos.y + m_SrcRect.GetHeight()
        );
	}
	void SetEffectManager(CEffectManager* pmng){ m_pEffectManager = pmng; }
	bool IsEnd(void){ return m_bEnd; }
	bool IsGoal(void){ return m_bGoal; }
};