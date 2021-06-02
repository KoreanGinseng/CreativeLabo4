/*************************************************************************//*!

                    @file	GameApp.cpp
                    @brief	��{�Q�[���A�v���B

                                                            @author	�_�c�@��
                                                            @date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"

//Input
#include    "../Include/Input/InputManager.h"
#include    "../Include/Input/LogInput.h"
#include    "../Include/Input/MofInput.h"

//Resource
#include    "../Include/Resource/ResourceManager.h"

//Render
#include    "../Include/Render/RenderManager.h"
#include    "../Include/Render/RenderClearCommand.h"
#include    "../Include/Render/RenderStartCommand.h"
#include    "../Include/Render/RenderEndCommand.h"
#include    "../Include/Render/TextureRenderCommand.h"
#include    "../Include/Render/StringRenderCommand.h"

//Animation
#include    "../Include/Animation/AnimationState.h"
#include    "../Include/Animation/AniMakeAnimationCreator.h"

//Scene
#include    "../Include/Scene/SceneManager.h"
#include    "../Include/Scene/Scene.h"

class GameScene : public sip::Scene {
public:
    explicit GameScene(sip::Scene::InitData init) 
    : sip::Scene(init) {
    }

    /**
    * @bref �`�揈��
    */
    virtual void Render(sip::RenderCommandTaskPtr& render_task) override {
        render_task->Push(std::make_shared<detail::StringRenderCommand>(0, 0, "game"), 0);
    }
};
class TestScene : public sip::Scene {
public:
    explicit TestScene(sip::Scene::InitData init)
        : sip::Scene(init) {
    }

    /**
    * @bref �`�揈��
    */
    virtual void Render(sip::RenderCommandTaskPtr& render_task) override {
        render_task->Push(std::make_shared<detail::StringRenderCommand>(0, 0, "test"), 0);
    }
};

sip::TexturePtr        g_Texture  = nullptr;
sip::TexturePtr        g_Texture2 = nullptr;
sip::InputPtr          g_Input    = nullptr;
sip::AnimationStatePtr g_anim     = nullptr;
float                  g_PosX     = 0.0f;

/*************************************************************************//*!
        @brief			�A�v���P�[�V�����̏�����
        @param			None

        @return			TRUE		����<br>
                        ����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Initialize(void) {

    CUtilities::SetCurrentDirectory("Resource");

    sip::SceneManager<sip::SceneData>::GetInstance().AddScene<GameScene>("game");
    sip::SceneManager<sip::SceneData>::GetInstance().AddScene<TestScene>("test");

    // Input
    auto input = InputManagerInstance.AddInput<sip::LogInput>()->CreateInput<sip::MofInput>();
    input->AddKeyboardKey("Horizontal", MOFKEY_RIGHT, MOFKEY_LEFT);
    input->AddKeyboardKey("Jump", MOFKEY_UP);
    input->AddKeyboardKey("Attack", MOFKEY_SPACE);
    
    g_Input = input;

    // Resource
    auto& player_pack = ResourceManagerInstance.LoadPack("player", "player_resources.json");
    auto& enemy_pack  = ResourceManagerInstance.LoadPack("enemy" , "enemy_resources.json");
    
    g_Texture  = player_pack->Get<sip::Texture>()->Get("Player");
    g_Texture2 = enemy_pack->Get<sip::Texture>()->Get("Enemy");

    auto& creator = sip::AniMakeAnimationCreator::Create("example.anim");
    g_anim = creator->Create();

    return TRUE;
}
/*************************************************************************//*!
        @brief			�A�v���P�[�V�����̍X�V
        @param			None

        @return			TRUE		����<br>
                        ����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Update(void) {
    //�L�[�̍X�V
    g_pInput->RefreshKey();
    //���͍X�V
    InputManagerInstance.Update();

    if (g_pInput->IsKeyPush(MOFKEY_F1)) {
        sip::SceneManager<sip::SceneData>::GetInstance().ChangeScene("test", 3.0f);
    }
    if (g_pInput->IsKeyPush(MOFKEY_F2)) {
        sip::SceneManager<sip::SceneData>::GetInstance().ChangeScene("game", 3.0f);
    }
    sip::SceneManager<sip::SceneData>::GetInstance().Update();

    g_anim->Update();

    if (float move = g_Input->GetAxis("Horizontal")) {
        g_PosX += move;
    }

    return TRUE;
}
/*************************************************************************//*!
        @brief			�A�v���P�[�V�����̕`��
        @param			None

        @return			TRUE		����<br>
                        ����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Render(void) {

    // Render
    auto& render_task = sip::RenderManager::CreateTask<sip::RenderCommandTask>(2);

    render_task->Push(sip::RenderClearCommand::Create(0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f), 0);
    render_task->Push(sip::TextureRenderCommand::Create(g_PosX, 300, g_Texture), 1);
    render_task->Push(sip::TextureRenderCommand::Create(g_PosX, 100, g_anim->GetSrcRect(), g_Texture2), 1);

    sip::SceneManager<sip::SceneData>::GetInstance().Render(render_task);

    sip::RenderManager::GetInstance().Push(render_task);

    return TRUE;
}
/*************************************************************************//*!
        @brief			�A�v���P�[�V�����̉��
        @param			None

        @return			TRUE		����<br>
                        ����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Release(void) {
    g_anim.reset();
    g_Input    = nullptr;
    g_Texture  = nullptr;
    g_Texture2 = nullptr;
    g_anim     = nullptr;
    InputManagerInstance.Release();
    ResourceManagerInstance.Release();
    sip::RenderManager::Release();

    return TRUE;
}