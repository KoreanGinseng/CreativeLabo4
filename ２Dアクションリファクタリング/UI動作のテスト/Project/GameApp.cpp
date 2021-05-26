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
#include	"Common/ReactiveParameter.h"
#include	"UI/HPGauge.h"
#include	"UI/HPRender.h"

constexpr int hpMax = 100;
Sample::ReactiveParameter<int>	hp(hpMax);
Sample::HPGaugePtr		hpGauge = std::make_shared<Sample::HPGauge>(hpMax);
Sample::HPRender		hpRender(hpGauge);

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
	auto frametex = pack->Get<Sample::Texture>()->Add("Frame");
	frametex->Load("Frame.png");
	auto hptex = pack->Get<Sample::Texture>()->Add("HP");
	hptex->Load("HP.png");
	hpRender.Load(pack);

	//�ʒm�ݒ�
	hp.Subscribe(hpGauge);
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

	//HP�ω�
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
		@brief			�A�v���P�[�V�����̕`��
		@param			None
				
		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Render(void){
	//�^�X�N�̐���
	auto task = Sample::RenderManager::CreateTask<Sample::RenderCommandTask>(2);

	//�`��̓o�^
	task->Push(Sample::RenderClearCommand::Create(0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0), 0);
	hpRender.Register(task);

	//�^�X�N�̓o�^
	Sample::RenderManager::GetInstance().Push(task);
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
	hpRender.Release();
	Sample::RenderManager::Release();
	ResourceManagerInstance.Release();
	return TRUE;
}