#pragma once

#include	"Player.h"
#include	"Stage.h"
#include	"Enemy.h"
#include	"Item.h"
#include	"EffectManager.h"

#include	"Input/MofInput.h"
#include	"Input/WinApiInput.h"

#include	"Animation/PlayerAnimationCreator.h"
#include	"Animation/JsonAnimationCreator.h"

#include	"Resource/ResourceManager.h"

#include	"Render/PlayerRender.h"

class CGame {
private:
	//�v���C���[
	CPlayer		m_Player;
	//�X�e�[�W
	CStage		m_Stage;
	//�G
	CEnemy*		m_EnemyArray;
	//�A�C�e��
	CItem*		m_ItemArray;
	//�G�t�F�N�g
	CEffectManager	m_EffectManager;
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