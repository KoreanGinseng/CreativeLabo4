#include	"GameDefine.h"
#include	"Game.h"

#include	"Input/InputManager.h"
#include	"Input/MofInput.h"
#include	"Input/LogInput.h"
#include	"Input/ReplayInput.h"
#include	"Input/WinApiInput.h"

//変更するシーン(外部参照、実体はGameApp.cpp)
extern int						gChangeScene;

/**
 * コンストラクタ
 *
 */
CGame::CGame(){
}

/**
 * デストラクタ
 *
 */
CGame::~CGame(){
}

/**
 * 読み込み
 * 利用するテクスチャを読み込む。
 */
bool CGame::Load(void){
	//入力作成
	/*
	auto input = InputManagerInstance.AddInput<Sample::WinApiInput>();
	input->AddKeyboardKey("Horizontal", VK_RIGHT, VK_LEFT);
	input->AddKeyboardKey("Jump", VK_UP);
	input->AddKeyboardKey("Attack", VK_SPACE);
	*/

	/*
	auto input = InputManagerInstance.AddInput<Sample::MofInput>();
	input->AddKeyboardKey("Horizontal", MOFKEY_RIGHT, MOFKEY_LEFT);
	input->AddKeyboardKey("Jump", MOFKEY_UP);
	input->AddKeyboardKey("Attack", MOFKEY_SPACE);
	*/

	auto input = InputManagerInstance.AddInput<Sample::LogInput>()->CreateInput<Sample::MofInput>();
	input->AddKeyboardKey("Horizontal", MOFKEY_RIGHT, MOFKEY_LEFT);
	input->AddKeyboardKey("Jump", MOFKEY_UP);
	input->AddKeyboardKey("Attack", MOFKEY_SPACE);

	/*
	auto input = InputManagerInstance.AddInput<Sample::ReplayInput>("Log/20210411141301.dat");
	*/

	//プレイヤーの素材読み込み
	m_Player.SetInput(input);
	m_Player.Load(Sample::JsonAnimationCreator::Create("PlayerAnimation.json"));
	//ステージの素材読み込み
	m_Stage.Load("Stage1.txt");
	//敵メモリ確保
	m_EnemyArray = new CEnemy[m_Stage.GetEnemyCount()];
	//アイテムメモリ確保
	m_ItemArray = new CItem[m_Stage.GetItemCount()];
	//エフェクトの素材読み込み
	m_EffectManager.Load();
	return true;
}

/**
 * 初期化
 * パラメーターや座標を初期化する。
 * 状態を初期化したいときに実行する。
 */
void CGame::Initialize(void){
	//プレイヤーの状態初期化
	m_Player.Initialize();
	//ステージの状態初期化
	m_Stage.Initialize(m_EnemyArray,m_ItemArray);
	//エフェクトの状態初期化
	m_EffectManager.Initialize();
	//プレイヤーと敵にエフェクトクラスの設定
	m_Player.SetEffectManager(&m_EffectManager);
	for(int i = 0;i < m_Stage.GetEnemyCount();i++)
	{
		m_EnemyArray[i].SetEffectManager(&m_EffectManager);
	}
}

/**
 * 更新
 *
 */
void CGame::Update(void){
	//入力更新
	InputManagerInstance.Update();
	//プレイヤーの更新
	m_Player.Update();
	//ステージとプレイヤーの当たり判定
	float ox = 0,oy = 0;
	if(m_Stage.Collision(m_Player.GetRect(),ox,oy))
	{
		m_Player.CollisionStage(ox,oy);
	}
	//敵の更新
	for(int i = 0;i < m_Stage.GetEnemyCount();i++)
	{
		if(!m_EnemyArray[i].GetShow())
		{
			continue;
		}
		m_EnemyArray[i].Update();
		float ox = 0,oy = 0;
		if(m_Stage.Collision(m_EnemyArray[i].GetRect(),ox,oy))
		{
			m_EnemyArray[i].CollisionStage(ox,oy);
		}
	}
	//アイテムの更新
	for(int i = 0;i < m_Stage.GetItemCount();i++)
	{
		if(!m_ItemArray[i].GetShow())
		{
			continue;
		}
		m_ItemArray[i].Update();
		float ox = 0,oy = 0;
		if(m_Stage.Collision(m_ItemArray[i].GetRect(),ox,oy))
		{
			m_ItemArray[i].CollisionStage(ox,oy);
		}
	}
	//当たり判定の実行
	for(int i = 0;i < m_Stage.GetEnemyCount();i++)
	{
		m_Player.CollisionEnemy(m_EnemyArray[i]);
	}
	for(int i = 0;i < m_Stage.GetItemCount();i++)
	{
		m_Player.CollisionItem(m_ItemArray[i]);
	}
	//ステージの更新
	m_Stage.Update(m_Player);
	//エフェクトの更新
	m_EffectManager.Update();

	//プレイヤーのゴールフラグでゲームクリア画面へ
	if(m_Player.IsGoal())
	{
		gChangeScene = SCENENO_GAMECLEAR;
	}
	//F2キーでゲームクリア画面へ
	if(g_pInput->IsKeyPush(MOFKEY_F2))
	{
		gChangeScene = SCENENO_GAMECLEAR;
	}
	//プレイヤーの終了フラグでゲームオーバー画面へ
	if(m_Player.IsEnd())
	{
		gChangeScene = SCENENO_GAMEOVER;
	}
	//F3キーでゲームオーバー画面へ
	if(g_pInput->IsKeyPush(MOFKEY_F3))
	{
		gChangeScene = SCENENO_GAMEOVER;
	}
}

/**
 * 描画
 *
 */
void CGame::Render(void){
	//ステージの描画
	m_Stage.Render();
	//プレイヤーの描画
	m_Player.Render(m_Stage.GetScrollX(),m_Stage.GetScrollY());
	//敵の描画
	for(int i = 0;i < m_Stage.GetEnemyCount();i++)
	{
		m_EnemyArray[i].Render(m_Stage.GetScrollX(),m_Stage.GetScrollY());
	}
	//アイテムの描画
	for(int i = 0;i < m_Stage.GetItemCount();i++)
	{
		m_ItemArray[i].Render(m_Stage.GetScrollX(),m_Stage.GetScrollY());
	}
	//エフェクトの描画
	m_EffectManager.Render(m_Stage.GetScrollX(),m_Stage.GetScrollY());

	//プレイヤーの状態描画
	m_Player.RenderStatus();

	//CGraphicsUtilities::RenderString(10,10,"ゲーム画面");
	//CGraphicsUtilities::RenderString(10,40,"F2キーでゲームクリア、F3キーでゲームオーバー");
}

/**
 * デバッグ描画
 *
 */
void CGame::RenderDebug(void){
	//ステージのデバッグ描画
	m_Stage.RenderDebug();
	//プレイヤーのデバッグ描画
	m_Player.RenderDebug(m_Stage.GetScrollX(),m_Stage.GetScrollY());
	//敵のデバッグ描画
	for(int i = 0;i < m_Stage.GetEnemyCount();i++)
	{
		m_EnemyArray[i].RenderDebug(m_Stage.GetScrollX(),m_Stage.GetScrollY());
	}
	//アイテムのデバッグ描画
	for(int i = 0;i < m_Stage.GetItemCount();i++)
	{
		m_ItemArray[i].RenderDebug(m_Stage.GetScrollX(),m_Stage.GetScrollY());
	}
	//エフェクトのデバッグ描画
	m_EffectManager.RenderDebug(m_Stage.GetScrollX(),m_Stage.GetScrollY());
}

/**
 * 解放
 *
 */
void CGame::Release(void){
	//ステージの解放
	m_Stage.Release();
	//プレイヤーの解放
	m_Player.Release();
	//敵の解放
	if(m_EnemyArray)
	{
		delete[] m_EnemyArray;
		m_EnemyArray = NULL;
	}
	//アイテムの解放
	if(m_ItemArray)
	{
		delete[] m_ItemArray;
		m_ItemArray = NULL;
	}
	//エフェクトの解放
	m_EffectManager.Release();
}