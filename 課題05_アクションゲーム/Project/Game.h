#pragma once

#include	"Player.h"
#include	"Stage.h"
#include	"Enemy.h"
#include	"Item.h"
#include	"EffectManager.h"
#include    "UIPlayerStatus.h"

class CGame {
private:
	//プレイヤー
	CPlayer		m_Player;
	//ステージ
	CStage		m_Stage;
	//敵
	CEnemy*		m_EnemyArray;
	//アイテム
	CItem*		m_ItemArray;
	//エフェクト
	CEffectManager	m_EffectManager;
    CUIPlayerStatus m_UIPlayerStatus;
public:
	CGame();
	~CGame();
	bool Load(void);
	void Initialize(void);
	void Update(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
};