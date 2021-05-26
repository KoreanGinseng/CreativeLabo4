/*************************************************************************//*!
					
					@file	GameApp.cpp
					@brief	基本ゲームアプリ。

															@author	濱田　享
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"

#include	"Resource/ResourceManager.h"
#include	"Render/TextureRenderCommand.h"
#include	"Render/RenderClearCommand.h"
#include	"Render/RenderManager.h"
#include	"Common/ReactiveParameter.h"
#include	"UI/HPGauge.h"
#include	"UI/HPRender.h"

constexpr int hpMax = 100;
Sample::ReactiveParameter<int>	hp(hpMax);
Sample::HPGaugePtr		hpGauge = std::make_shared<Sample::HPGauge>(hpMax);
Sample::HPRender		hpRender(hpGauge);

/*************************************************************************//*!
		@brief			アプリケーションの初期化
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Initialize(void){
	//リソース配置ディレクトリの設定
	CUtilities::SetCurrentDirectory("Resource");

	//リソースの読み込み
	auto pack = ResourceManagerInstance.AddPack("Test");
	auto frametex = pack->Get<Sample::Texture>()->Add("Frame");
	frametex->Load("Frame.png");
	auto hptex = pack->Get<Sample::Texture>()->Add("HP");
	hptex->Load("HP.png");
	hpRender.Load(pack);

	//通知設定
	hp.Subscribe(hpGauge);
	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの更新
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Update(void){
	//キーの更新
	g_pInput->RefreshKey();

	//HP変化
	if (g_pInput->IsKeyHold(MOFKEY_LEFT))
	{
		hp -= 1;
	}
	if (g_pInput->IsKeyHold(MOFKEY_RIGHT))
	{
		hp += 1;
	}
	if (g_pInput->IsKeyPush(MOFKEY_SPACE))
	{
		hp = hpMax;
	}

	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの描画
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Render(void){
	//タスクの生成
	auto task = Sample::RenderManager::CreateTask<Sample::RenderCommandTask>(2);

	//描画の登録
	task->Push(Sample::RenderClearCommand::Create(0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0), 0);
	hpRender.Register(task);

	//タスクの登録
	Sample::RenderManager::GetInstance().Push(task);
	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの解放
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Release(void){
	//解放
	hpRender.Release();
	Sample::RenderManager::Release();
	ResourceManagerInstance.Release();
	return TRUE;
}