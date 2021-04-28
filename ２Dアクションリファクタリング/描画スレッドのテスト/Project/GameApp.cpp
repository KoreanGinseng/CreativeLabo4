/*************************************************************************//*!
					
					@file	GameApp.cpp
					@brief	��{�Q�[���A�v���B

															@author	�_�c�@��
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"

#include	"Resource/ResourceManager.h"
#include	"Render/TextureRenderCommand.h"
#include	"Render/RenderClearCommand.h"
#include	"Render/RenderManager.h"

//�`��ʒu
float px = 0;
float py = 0;
//�摜
Sample::TexturePtr tex;

//�`��̓o�^�t���O
bool bRender = true;
//�`��̉ߋ��t���[����
int prevCount = 0;

/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̏�����
		@param			None
				
		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Initialize(void){
	//���\�[�X�z�u�f�B���N�g���̐ݒ�
	CUtilities::SetCurrentDirectory("Resource");

	//���\�[�X�̓ǂݍ���
	auto pack = ResourceManagerInstance.AddPack("Test");
	tex = pack->Get<Sample::Texture>()->Add("Test");
	tex->Load("texture.png");
	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̍X�V
		@param			None
				
		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Update(void){
	//�L�[�̍X�V
	g_pInput->RefreshKey();
	//�`����s�̏ꍇ
	if (bRender)
	{
		//�ړ�����
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
		@brief			�A�v���P�[�V�����̕`��
		@param			None
				
		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Render(void){
	//�`����s�̏ꍇ
	if (bRender)
	{
		//�^�X�N�̐���
		auto task = Sample::RenderManager::CreateTask<Sample::RenderCommandTask>(1);

		//�`��̓o�^
		task->Push(Sample::RenderClearCommand::Create(0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0), 0);
		task->Push(Sample::TextureRenderCommand::Create(px, py, tex), 0);

		//�^�X�N�̓o�^
		Sample::RenderManager::GetInstance().Push(task);
	}
	else
	{
		//�ߋ��̃^�X�N�擾
		auto task = Sample::RenderManager::GetInstance().GetExecutedTask(prevCount);
		if (task)
		{
			//���s
			task->Exec();
		}
	}
	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̉��
		@param			None
				
		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Release(void){
	//���
	Sample::RenderManager::Release();
	ResourceManagerInstance.Release();
	tex.reset();
	return TRUE;
}