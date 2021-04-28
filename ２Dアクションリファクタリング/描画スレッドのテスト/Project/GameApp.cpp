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

//描画位置
float px = 0;
float py = 0;
//画像
Sample::TexturePtr tex;

//描画の登録フラグ
bool bRender = true;
//描画の過去フレーム数
int prevCount = 0;

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
	tex = pack->Get<Sample::Texture>()->Add("Test");
	tex->Load("texture.png");
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
	//描画実行の場合
	if (bRender)
	{
		//移動処理
		px += 5;
		if (g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			bRender = false;
		}
	}
	else
	{
		if (g_pInput->IsKeyPush(MOFKEY_LEFT))
		{
			if (prevCount < Sample::RenderManager::ExecutedQueueCount)
			{
				prevCount++;
			}
		}
		if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
		{
			if (prevCount > 0)
			{
				prevCount--;
			}
		}
		if (g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			bRender = true;
		}
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
	//描画実行の場合
	if (bRender)
	{
		//タスクの生成
		auto task = Sample::RenderManager::CreateTask<Sample::RenderCommandTask>(1);

		//描画の登録
		task->Push(Sample::RenderClearCommand::Create(0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0), 0);
		task->Push(Sample::TextureRenderCommand::Create(px, py, tex), 0);

		//タスクの登録
		Sample::RenderManager::GetInstance().Push(task);
	}
	else
	{
		//過去のタスク取得
		auto task = Sample::RenderManager::GetInstance().GetExecutedTask(prevCount);
		if (task)
		{
			//実行
			task->Exec();
		}
	}
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
	Sample::RenderManager::Release();
	ResourceManagerInstance.Release();
	tex.reset();
	return TRUE;
}