#include	"Effect.h"

/**
 * コンストラクタ
 *
 */
CEffect::CEffect() :
m_pTexture(NULL) ,
m_Motion() ,
m_PosX(0.0f) ,
m_PosY(0.0f) ,
m_bShow(false) ,
m_SrcRect() {
}

/**
 * デストラクタ
 *
 */
CEffect::~CEffect(){
}

/**
 * 開始
 * パラメーターや座標を初期化する。
 *
 * 引数
 * [in]			type				タイプ
 */
void CEffect::Initialize(int type){
	m_PosX = 0.0f;
	m_PosY = 0.0f;
	m_bShow = false;
	switch(type)
	{
		case EFC_DAMAGE:
		{
			//アニメーションを作成
			SpriteAnimationCreate anim[] = {
				//ダメージ
				{
					"エフェクト",
					0,0,
					128,128,
					FALSE,{{2,0,0},{2,1,0},{2,2,0},{2,3,0}} 
				},
			};
			m_Motion.Create(anim,1);
			break;
		}
		case EFC_EXPLOSION01:
		{
			//アニメーションを作成
			SpriteAnimationCreate anim[] = {
				//ダメージ
				{
					"エフェクト",
					0,0,
					120,120,
					FALSE,{{3,0,0},{3,1,0},{3,2,0},{3,3,0},{3,4,0},{3,5,0},{3,6,0},{3,7,0},{3,8,0},{3,9,0},{3,10,0},{3,11,0},{3,12,0},{3,13,0},{3,14,0},{3,15,0}} 
				},
			};
			m_Motion.Create(anim,1);
			break;
		}
		case EFC_EXPLOSION02:
		{
			//アニメーションを作成
			SpriteAnimationCreate anim[] = {
				//ダメージ
				{
					"エフェクト",
					0,0,
					180,180,
					FALSE,{{3,0,0},{3,1,0},{3,2,0},{3,3,0},{3,4,0},{3,5,0},{3,6,0},{3,7,0},{3,8,0},{3,9,0},{3,10,0},
							{3,0,1},{3,1,1},{3,2,1},{3,3,1},{3,4,1},{3,5,1},{3,6,1},{3,7,1},{3,8,1},{3,9,1},{3,10,1}} 
				},
			};
			m_Motion.Create(anim,1);
			break;
		}
	}
}

/**
 * 開始
 * 座標を設定してモーションを開始する。
 *
 * 引数
 * [in]			px					X座標
 * [in]			py					Y座標
 */
void CEffect::Start(float px,float py){
	m_SrcRect = m_Motion.GetSrcRect();
	m_PosX = px - m_SrcRect.GetWidth() * 0.5f;
	m_PosY = py - m_SrcRect.GetHeight() * 0.5f;
	m_bShow = true;
	m_Motion.ChangeMotion(0);
}

/**
 * 更新
 *
 */
void CEffect::Update(void){
	//非表示
	if(!m_bShow)
	{
		return;
	}
	//アニメーションの更新
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
	//アニメーションの終了で非表示にする
	if(m_Motion.IsEndMotion())
	{
		m_bShow = false;
	}
}

/**
 * 描画
 *
 * 引数
 * [in]			wx					ワールドの変化
 * [in]			wy					ワールドの変化
 */
void CEffect::Render(float wx,float wy){
	//非表示
	if(!m_bShow)
	{
		return;
	}
	//テクスチャの描画
	m_pTexture->Render(m_PosX - wx,m_PosY - wy,m_SrcRect);
}

/**
 * デバッグ描画
 *
 * 引数
 * [in]			wx					ワールドの変化
 * [in]			wy					ワールドの変化
 */
void CEffect::RenderDebug(float wx,float wy){
	//非表示
	if(!m_bShow)
	{
		return;
	}
}

/**
 * 解放
 *
 */
void CEffect::Release(void){
	m_Motion.Release();
}