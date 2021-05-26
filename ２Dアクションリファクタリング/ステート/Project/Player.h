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

//移動速度
#define		PLAYER_SPEED			0.3f

//移動最大速度
#define		PLAYER_MAXSPEED			10.0f

//ジャンプ初速
#define		PLAYER_JUMP				-10.0f

//攻撃幅
#define		PLAYER_ATTACKWIDTH		30

//当たり判定減衰幅
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
	 * @brief		ステートの変更
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
	 * @brief		加速
	 * @param[in]	val			加速量
	 * @param[in]	maxspeed	最大速度
	 * @param[in]	rev			反転フラグ
	 */
	void Acceleration(float val, float maxspeed, bool rev);

	/**
	 * @brief		速度設定
	 * @param[in]	val		速度
	 */
	void SetSpeedX(float val) {
		m_MoveX = val;
	}

	/**
	 * @brief		速度設定
	 * @param[in]	val		速度
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
		//反転中
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
	 * @brief		入力機能設定
	 * @param[in]	ptr		利用する入力
	 */
	void SetInput(const Sample::InputPtr& ptr) {
		m_pInput = ptr;
	}

	/**
	 * @brief		HP変化通知
	 */
	Sample::IObservable<int>* GetHPSubject() { return &m_HP; }

	/**
	 * @brief		モーション情報
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