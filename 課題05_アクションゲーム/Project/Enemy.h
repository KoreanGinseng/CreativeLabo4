#pragma once

#include	"Mof.h"
#include	"GameDefine.h"
#include	"EffectManager.h"


//当たり判定減衰幅
#define		ENEMY_RECTDECREASE		10

class CEnemy {
private:
	CTexture*				m_pTexture;
	CSpriteMotionController	m_Motion;
	int						m_Type;
	float					m_PosX;
	float					m_PosY;
	float					m_MoveX;
	float					m_MoveY;
	bool					m_bShow;
	bool					m_bReverse;
	CRectangle				m_SrcRect;
	
	int						m_HP;
	int						m_DamageWait;
	
	CEffectManager*			m_pEffectManager;
	
	//モーション種類定義
	enum tag_MOTION {
		MOTION_MOVE,
		MOTION_DAMAGE,

		MOTION_COUNT,
	};
public:
	CEnemy();
	~CEnemy();
	void Initialize(float px,float py,int type);
	void Update(void);
	void Damage(int dmg,bool bRev);
	void CollisionStage(float ox,float oy);
	void Render(float wx,float wy);
	void RenderDebug(float wx,float wy);
	void Release(void);
	void SetTexture(CTexture* pt){ m_pTexture = pt; }
	bool GetShow(void){ return m_bShow; }
	int GetDamageWait(void){ return m_DamageWait; }
	CRectangle GetRect(){
		return CRectangle(m_PosX + ENEMY_RECTDECREASE,m_PosY + ENEMY_RECTDECREASE,m_PosX + m_SrcRect.GetWidth() - ENEMY_RECTDECREASE,m_PosY + m_SrcRect.GetHeight());
	}
	void SetEffectManager(CEffectManager* pmng){ m_pEffectManager = pmng; }
};