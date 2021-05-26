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

#include	"State/StateMachine.h"

#include	"Common/Transform.h"
#include	"Action/MoveAction.h"

#include	"Actor/Actor.h"

class CPlayer {
private:
	Sample::TexturePtr			m_Texture;
	Sample::AnimationStatePtr	m_Motion;
	Sample::ActorPtr			m_Actor;
	Sample::MoveActionPtr		m_Move;
	Sample::Rectangle			m_SrcRect;

	CEffectManager*				m_pEffectManager;
	
	CEffect*					m_pEndEffect;

	Sample::InputPtr			m_pInput;

	Sample::StateMachinePtr		m_StateMachine;

	Sample::ParameterHandle< Sample::ReactiveParameter<int> > m_HP;
	Sample::ParameterHandle< int > m_DamageWait;
	Sample::ParameterHandle< bool > m_bEnd;
	Sample::ParameterHandle< bool > m_bGoal;
public:
	CPlayer();
	~CPlayer();
	bool Load(Sample::ResourcePackPtr<UsedResources>& pack, const Sample::AnimationCreatorPtr& animCreator);
	void Initialize(void);
	void Update(void);

	void CollisionStage(float ox,float oy);

	void Damage(int dmg, int wait, bool back);
	void Heal(int val);

	void Release(void);
	bool IsAttack(){ return m_Motion->IsMotion("Attack"); }
	Sample::Rectangle GetRect(){
		if(IsAttack())
		{
			return Sample::Rectangle(m_Actor->GetPositionX() + PLAYER_RECTDECREASE,m_Actor->GetPositionY() + PLAYER_RECTDECREASE,m_Actor->GetPositionX() + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE - PLAYER_ATTACKWIDTH,m_Actor->GetPositionY() + m_SrcRect.GetHeight());
		}
		return Sample::Rectangle(m_Actor->GetPositionX() + PLAYER_RECTDECREASE,m_Actor->GetPositionY() + PLAYER_RECTDECREASE,m_Actor->GetPositionX() + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE,m_Actor->GetPositionY() + m_SrcRect.GetHeight());
	}
	Sample::Rectangle GetAttackRect(){
		//反転中
		if(m_Move->IsReverse())
		{
			return Sample::Rectangle(m_Actor->GetPositionX() - PLAYER_ATTACKWIDTH,m_Actor->GetPositionY(),m_Actor->GetPositionX() + PLAYER_RECTDECREASE,m_Actor->GetPositionY() + m_SrcRect.GetHeight());
		}
		return Sample::Rectangle(m_Actor->GetPositionX() + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE - PLAYER_ATTACKWIDTH,m_Actor->GetPositionY(),m_Actor->GetPositionX() + m_SrcRect.GetWidth(),m_Actor->GetPositionY() + m_SrcRect.GetHeight());
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
	Sample::IObservable<int>* GetHPSubject() { return &(m_HP.Get()); }

	/**
	 * @brief		モーション情報
	 */
	Sample::AnimationStatePtr GetAnimationState() { return m_Motion; }

	/**
	 * @brief		移動取得
	 */
	Sample::MoveActionPtr GetMoveAction() { return m_Move; }

	void SetGoal(bool val) { m_bGoal = val; }


	float GetPosX() const noexcept {
		return m_Actor->GetPositionX();
	}
	float GetPosY() const noexcept {
		return m_Actor->GetPositionY();
	}
	int GetHP() const noexcept {
		return m_HP.Get();
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
		return m_Move->IsReverse();
	}
};