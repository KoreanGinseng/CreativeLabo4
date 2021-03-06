#include "EffectManager.h"


/**
 * コンストラクタ
 */
CEffectManager::CEffectManager(){
	//初期化
	for(int i = 0; i < EMITTERTYPE_MAX; i++)
	{
		m_LifeTime[i] = 0;
		CEmitter<MINMAXPARAMETER>::CREATEINFO& cinfo = m_CreateInfo[i];
		cinfo.ParameterBehavior.Existence.SetDefaultParameter(0);
		cinfo.ParameterBehavior.Blending = BLEND_NORMAL;
		cinfo.ParameterBehavior.Flag = 0;
		cinfo.ParameterBehavior.pTexture = NULL;
		cinfo.ParameterBehavior.pMesh = NULL;
		cinfo.CreateBehavior.Time = 0;
		cinfo.CreateBehavior.Count = 0;
	}
}

/**
 * デストラクタ
 */
CEffectManager::~CEffectManager(){
	Release();
}

/**
 * リソースの読み込み
 */
bool CEffectManager::Load(){
	if(!m_BlueFlash.Load("BlueFlash.png"))
	{
		return false;
	}
	if(!m_WhiteFlash.Load("WhiteFlash.png"))
	{
		return false;
	}
	if(!m_Smoke.Load("Smoke.png"))
	{
		return false;
	}
	if(!m_Fire.Load("Fire.png"))
	{
		return false;
	}
	if(!m_RedFlash.Load("RedFlash.png"))
	{
		return false;
	}
	if(!m_PlayerMesh.Load("player.mom"))
	{
		return false;
	}
	m_PlayerMesh.GetGeometry(0)->GetMaterial()->SetBlending(BLEND_USER);
	if(!m_Particle.Load("Particle.png"))
	{
		return false;
	}
		
	InitCreateInfo();
	return true;
}

/**
 * 課題　エミッターの動作パラメーター設定
 */
void CEffectManager::InitCreateInfo(){
	
	//プレイヤー弾発射エフェクト
	{
		m_LifeTime[EMITTER_SHOT] = 1;	//エミッターの寿命
		CEmitter<MINMAXPARAMETER>::CREATEINFO& cinfo = m_CreateInfo[EMITTER_SHOT];

		cinfo.UpdateBehavior.Color.SetDefaultParameter(CVector4(0,0,0,-1.0f/7));
		cinfo.UpdateBehavior.Scale.SetDefaultParameter(CVector3(-1.0f / 7,-1.0f/ 7,-1.0f/ 7));
		cinfo.UpdateBehavior.Move.SetParameter(CVector3(-0.1f,-0.1f,-0.1f),CVector3(0.1f,0.1f,0.1f));

		cinfo.ParameterBehavior.Existence.SetDefaultParameter(7);
		cinfo.ParameterBehavior.Blending = BLEND_ADD;
		cinfo.ParameterBehavior.Flag = CParticle::BILLBOARD;
		cinfo.ParameterBehavior.pTexture = &m_BlueFlash;
		cinfo.ParameterBehavior.pMesh = NULL;

		cinfo.CreateBehavior.Position.SetDefaultParameter(CVector3(0,0,0.5f));
		cinfo.CreateBehavior.Color.SetDefaultParameter(CVector4(1,1,1,1));
		cinfo.CreateBehavior.Scale.SetDefaultParameter(CVector3(1.0f,1.0f,1.0f));
		cinfo.CreateBehavior.Time = 0;
		cinfo.CreateBehavior.Count = 4;
	}

	//課題１　プレイヤー弾ヒットエフェクト
	{
		m_LifeTime[EMITTER_HIT] = 1;	//エミッターの寿命
		CEmitter<MINMAXPARAMETER>::CREATEINFO& cinfo = m_CreateInfo[EMITTER_HIT];
		cinfo.UpdateBehavior.Color.SetDefaultParameter(CVector4(0, 0, 0, 0));
		cinfo.UpdateBehavior.Scale.SetDefaultParameter(CVector3(-1.0f / 7, -1.0f / 7, -1.0f / 7));
		cinfo.UpdateBehavior.Move.SetParameter(CVector3(-0.3f, -0.1f, -0.5f), CVector3(0.3f, 0.1f, -0.3f));

		cinfo.ParameterBehavior.Existence.SetDefaultParameter(7);
		cinfo.ParameterBehavior.Blending = BLEND_ADD;
		cinfo.ParameterBehavior.Flag     = CParticle::BILLBOARD;
		cinfo.ParameterBehavior.pTexture = &m_BlueFlash;
		cinfo.ParameterBehavior.pMesh    = NULL;

		cinfo.CreateBehavior.Position.SetDefaultParameter(CVector3(0, 0, -0.5f));
		cinfo.CreateBehavior.Color.SetDefaultParameter(CVector4(1, 1, 1, 1));
		cinfo.CreateBehavior.Scale.SetDefaultParameter(CVector3(1.0f, 1.0f, 1.0f));
		cinfo.CreateBehavior.Time  = 0;
		cinfo.CreateBehavior.Count = 2;

	}
	
	//課題２　爆発エフェクト(フラッシュ)
	{
		m_LifeTime[EMITTER_EXPLOTION_FLASH] = 1;	//エミッターの寿命
		CEmitter<MINMAXPARAMETER>::CREATEINFO& cinfo = m_CreateInfo[EMITTER_EXPLOTION_FLASH];
		cinfo.UpdateBehavior.Color.SetDefaultParameter(CVector4(0, 0, 0, -1.0f / 5));
		cinfo.UpdateBehavior.Scale.SetDefaultParameter(CVector3(1.0f, 1.0f, 1.0f));
		cinfo.UpdateBehavior.Move.SetParameter(CVector3(-0.01f, -0.01f, -0.01f), CVector3(0.01f, 0.01f, 0.01f));

		cinfo.ParameterBehavior.Existence.SetDefaultParameter(3);
		cinfo.ParameterBehavior.Blending = BLEND_ADD;
		cinfo.ParameterBehavior.Flag     = CParticle::BILLBOARD;
		cinfo.ParameterBehavior.pTexture = &m_WhiteFlash;
		cinfo.ParameterBehavior.pMesh    = NULL;

		cinfo.CreateBehavior.Position.SetDefaultParameter(CVector3(0, 0, 0.5f));
		cinfo.CreateBehavior.Color.SetDefaultParameter(CVector4(1, 1, 1, 1));
		cinfo.CreateBehavior.Scale.SetDefaultParameter(CVector3(7.0f, 7.0f, 7.0f));
		cinfo.CreateBehavior.Time  = 0;
		cinfo.CreateBehavior.Count = 1;

	}
	//課題２　爆発エフェクト(煙)
	{
		m_LifeTime[EMITTER_EXPLOTION_SMOKE] = 1;	//エミッターの寿命
		CEmitter<MINMAXPARAMETER>::CREATEINFO& cinfo = m_CreateInfo[EMITTER_EXPLOTION_SMOKE];
		cinfo.UpdateBehavior.Color.SetDefaultParameter(CVector4(0, 0, 0, -1.0f / 120));
		cinfo.UpdateBehavior.Scale.SetDefaultParameter(CVector3(1.0f / 120, 1.0f / 120, 1.0f / 120));
		cinfo.UpdateBehavior.Move.SetParameter(CVector3(-0.005f, -0.005f, -0.005f), CVector3(0.005f, 0.005f, 0.005f));

		cinfo.ParameterBehavior.Existence.SetDefaultParameter(120);
		cinfo.ParameterBehavior.Blending = BLEND_NORMAL;
		cinfo.ParameterBehavior.Flag     = CParticle::BILLBOARD;
		cinfo.ParameterBehavior.pTexture = &m_Smoke;
		cinfo.ParameterBehavior.pMesh    = NULL;

		cinfo.EnvironmentBehavior.Gravity = CVector3(0, -0.00001f, 0);

		cinfo.CreateBehavior.Position.SetDefaultParameter(CVector3(0, 0, 0.2f));
		cinfo.CreateBehavior.Color.SetDefaultParameter(CVector4(1, 1, 1, 0.5f));
		cinfo.CreateBehavior.Scale.SetDefaultParameter(CVector3(3.0f, 3.0f, 3.0f));
		cinfo.CreateBehavior.Time  = 1;
		cinfo.CreateBehavior.Count = 3;

	}
	//課題２　爆発エフェクト(炎)
	{
		m_LifeTime[EMITTER_EXPLOTION_FIRE] = 9;	//エミッターの寿命
		CEmitter<MINMAXPARAMETER>::CREATEINFO& cinfo = m_CreateInfo[EMITTER_EXPLOTION_FIRE];
		cinfo.UpdateBehavior.Color.SetDefaultParameter(CVector4(0, 0, 0, -1.0f / 15));
		cinfo.UpdateBehavior.Scale.SetDefaultParameter(CVector3(-2.0f / 15, -2.0f / 15, -2.0f / 15));
		cinfo.UpdateBehavior.Move.SetParameter(CVector3(-0.05f, -0.05f, -0.05f), CVector3(0.05f, 0.05f, 0.05f));

		cinfo.ParameterBehavior.Existence.SetDefaultParameter(15);
		cinfo.ParameterBehavior.Blending = BLEND_ADD;
		cinfo.ParameterBehavior.Flag     = CParticle::BILLBOARD;
		cinfo.ParameterBehavior.pTexture = &m_Fire;
		cinfo.ParameterBehavior.pMesh    = NULL;

		cinfo.CreateBehavior.Position.SetParameter(CVector3(-0.5f, 0, 0.2f), CVector3(0.5f, 0, 0.2f));
		cinfo.CreateBehavior.Color.SetDefaultParameter(CVector4(1, 1, 1, 1));
		cinfo.CreateBehavior.Scale.SetDefaultParameter(CVector3(2.0f, 2.0f, 2.0f));
		cinfo.CreateBehavior.Time  = 0;
		cinfo.CreateBehavior.Count = 3;

	}
	//課題２　爆発エフェクト(火の粉)
	{
		m_LifeTime[EMITTER_EXPLOTION_SPARK] = 9;	//エミッターの寿命
		CEmitter<MINMAXPARAMETER>::CREATEINFO& cinfo = m_CreateInfo[EMITTER_EXPLOTION_SPARK];
		cinfo.UpdateBehavior.Color.SetDefaultParameter(CVector4(0, 0, 0, -1.0f / 20));
		cinfo.UpdateBehavior.Scale.SetDefaultParameter(CVector3(-0.7f / 20, -0.7f / 20, -0.7f / 20));
		cinfo.UpdateBehavior.Move.SetParameter(CVector3(-0.3f, -0.2f, -0.3f), CVector3(0.3f, 0.02f, 0.3f));

		cinfo.ParameterBehavior.Existence.SetDefaultParameter(20);
		cinfo.ParameterBehavior.Blending = BLEND_ADD;
		cinfo.ParameterBehavior.Flag     = CParticle::BILLBOARD;
		cinfo.ParameterBehavior.pTexture = &m_RedFlash;
		cinfo.ParameterBehavior.pMesh    = NULL;

		cinfo.EnvironmentBehavior.Gravity = Vector3(0, -0.015f, 0);

		cinfo.CreateBehavior.Position.SetDefaultParameter(CVector3(0, 0, 0.1f));
		cinfo.CreateBehavior.Color.SetDefaultParameter(CVector4(1, 1, 1, 1));
		cinfo.CreateBehavior.Scale.SetDefaultParameter(CVector3(0.7f, 0.7f, 0.7f));
		cinfo.CreateBehavior.Time  = 0;
		cinfo.CreateBehavior.Count = 5;

	}
	
	//課題３　プレイヤーの残像
	{
		m_LifeTime[EMITTER_AFTERIMAGE] = -1;	//エミッターの寿命
		CEmitter<MINMAXPARAMETER>::CREATEINFO& cinfo = m_CreateInfo[EMITTER_AFTERIMAGE];
		cinfo.UpdateBehavior.Color.SetDefaultParameter(CVector4(0, 0, 0, -1.0f / 60));
		cinfo.UpdateBehavior.Scale.SetDefaultParameter(CVector3());
		cinfo.UpdateBehavior.Move.SetDefaultParameter(CVector3());

		cinfo.ParameterBehavior.Existence.SetDefaultParameter(60);
		cinfo.ParameterBehavior.Blending = BLEND_ADD;
		cinfo.ParameterBehavior.pTexture = NULL;
		cinfo.ParameterBehavior.pMesh = &m_PlayerMesh;

		cinfo.CreateBehavior.Position.SetDefaultParameter(CVector3(0, 0, 0));
		cinfo.CreateBehavior.Color.SetDefaultParameter(CVector4(1, 0, 0, 1));
		cinfo.CreateBehavior.Scale.SetDefaultParameter(CVector3(1, 1, 1));
		cinfo.CreateBehavior.Time  = 0;
		cinfo.CreateBehavior.Count = 1;

	}
	//課題３　プレイヤーの残像粒子
	{
		m_LifeTime[EMITTER_AFTERIMAGE_PARTICLE] = -1;	//エミッターの寿命
		CEmitter<MINMAXPARAMETER>::CREATEINFO& cinfo = m_CreateInfo[EMITTER_AFTERIMAGE_PARTICLE];
		cinfo.UpdateBehavior.Color.SetDefaultParameter(CVector4(0, 0, 0, 0));
		cinfo.UpdateBehavior.Scale.SetDefaultParameter(CVector3(-1 / 30, -1 / 30, -1 / 30));
		cinfo.UpdateBehavior.Move.SetParameter(CVector3(-0.05f, -0.02f, -0.05f), CVector3(0.05f, -0.01f, 0.05f));

		cinfo.ParameterBehavior.Existence.SetDefaultParameter(30);
		cinfo.ParameterBehavior.Blending = BLEND_ADD;
		cinfo.ParameterBehavior.pTexture = &m_Particle;
		cinfo.ParameterBehavior.pMesh = NULL;

		cinfo.CreateBehavior.Position.SetParameter(CVector3(-0.05f, -0.05f, -0.05f), CVector3(0.05f, -0.01f, 0.05f));
		cinfo.CreateBehavior.Color.SetDefaultParameter(CVector4(1, 1, 1, 1));
		cinfo.CreateBehavior.Scale.SetDefaultParameter(CVector3(1, 1, 1));
		cinfo.CreateBehavior.Time = 0;
		cinfo.CreateBehavior.Count = 1;
	}
}

/**
 * 更新処理
 */
void CEffectManager::Update(){
	//エミッターの更新
	for(EmitterList::iterator it = m_EmitterList.begin(); it != m_EmitterList.end();)
	{
		if ((*it)->GetLifeTime() != 0)
		{
			(*it)->Update(&m_ParticleList);
		}
		//終了したエミッターの削除
		else
		{
			delete (*it);
			it =m_EmitterList.erase(it);
			continue;
		}
		++it;
	}
	//パーティクルの更新
	for (std::list< CParticle* >::iterator it = m_ParticleList.begin(); it != m_ParticleList.end(); )
	{
		(*it)->Update();
		//終了したパーティクルの削除
		if ((*it)->IsEnd())
		{
			delete (*it);
			it =m_ParticleList.erase(it);
			continue;
		}
		++it;
	}
}

/**
 * 描画処理
 */
void CEffectManager::Render(){
	//ソートの実行
	for (std::list< CParticle* >::iterator it = m_ParticleList.begin(); it != m_ParticleList.end(); ++it)
	{
		(*it)->UpdateViewPosition();
	}
	m_ParticleList.sort(CParticle::ViewComp);
	//パーティクルの描画
	for (std::list< CParticle* >::iterator it = m_ParticleList.begin(); it != m_ParticleList.end(); ++it)
	{
		(*it)->Render();
	}
	g_pGraphics->SetBlending(BLEND_NORMAL);
}

/**
 * 全てのエフェクトを削除
 */
void CEffectManager::Clear(){
	//パーティクルの解放
	for (std::list< CParticle* >::iterator it = m_ParticleList.begin(); it != m_ParticleList.end(); ++it)
	{
		MOF_SAFE_DELETE(*it);
	}
	m_ParticleList.clear();
	//エミッターの解放
	for(EmitterList::iterator it = m_EmitterList.begin(); it != m_EmitterList.end(); ++it)
	{
		MOF_SAFE_DELETE(*it);
	}
	m_EmitterList.clear();
}

/**
 * 解放処理
 */
void CEffectManager::Release(){
	Clear();
		
	m_BlueFlash.Release();
	m_WhiteFlash.Release();
	m_Smoke.Release();
	m_Fire.Release();
	m_RedFlash.Release();
	m_PlayerMesh.Release();
	m_Particle.Release();
}

/**
 * エミッターの追加
 */
CEmitter<MINMAXPARAMETER>* CEffectManager::AddEmitter(EMITTERTYPE type,const CVector3& pos){
	if(type < 0 || EMITTERTYPE_MAX <= type)
	{
		return NULL;
	}
	return AddEmitter(type,pos,m_LifeTime[type]);
}

/**
 * 寿命を指定してエミッターを追加
 */
CEmitter<MINMAXPARAMETER>* CEffectManager::AddEmitter(EMITTERTYPE type,const CVector3& pos,float LifeTime){
	if(type < 0 || EMITTERTYPE_MAX <= type)
	{
		return NULL;
	}
	CEmitter<MINMAXPARAMETER>* pEmitter = new CEmitter<MINMAXPARAMETER>();
	pEmitter->Initialize(m_CreateInfo[type],LifeTime);
	pEmitter->SetPosition(pos);
	m_EmitterList.push_back(pEmitter);
	return pEmitter;
}

/**
 * エミッターの削除
 */
void CEffectManager::DeleteEmitter(CEmitter<MINMAXPARAMETER>**ppEmitter){
	if(ppEmitter == NULL || *ppEmitter == NULL)
	{
		return;
	}
	EmitterList::iterator it = std::find(m_EmitterList.begin(),m_EmitterList.end(),*ppEmitter);
	if(it != m_EmitterList.end())
	{
		delete (*it);
		m_EmitterList.erase(it);
	}
	*ppEmitter = NULL;
}