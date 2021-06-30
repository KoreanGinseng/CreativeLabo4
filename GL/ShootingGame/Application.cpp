#pragma once

#include    "Application.h"

#include    "Include/Input/InputManager.h"
#include    "Include/Input/GLInput.h"
#include    "Include/Input/LogInput.h"

#include    "Include/Render/RenderManager.h"
#include    "Include/Render/RenderCommandTask.h"
#include    "Include/Render/RenderClearCommand.h"
#include    "Include/Render/SpriteRenderCommand.h"
#include    "Include/Render/RenderFrameBufferBindCommand.h"
#include    "Include/Render/RenderResetTargetCommand.h"
#include    "Include/Render/ContextGuard.h"

#include    "TitleScene.h"
#include    "GameScene.h"

using namespace Sample;

//描画関連
CameraPtr camera;

//音関連
SoundPtr sound;

/**
 * @brief        コンストラクタ
 */
Application::Application()
    : Framework() {
}

/**
 * @brief        デストラクタ
 */
Application::~Application() {
    InputManagerInstance.Release();
    RenderManagerInstance.Release();
}

/**
 * @brief        初期化
 */
void Application::Initialize() {

    //リソースディレクトリを素材配置先に指定
    ::SetCurrentDirectory(L"Resources");

    //シェーダー読み込み
    spriteShader_ = std::make_shared<Shader>("Sprite.vert", "Sprite.frag");
    GraphicsController::GetInstance().SpriteShader(spriteShader_);

    //カメラ設定
    camera = std::make_shared<Camera>();
    camera->Create2D(1024, 768);
    GraphicsController::GetInstance().Camera(camera);

    //音読み込み
    sound = std::make_shared<Sound>("se_enter.wav");

    auto sceneData = SceneManagerInstance.GetSceneData();
    auto input = InputManagerInstance.AddInput<sip::LogInput>()->CreateInput<sip::GLInput>(input_);
    input->AddKeyboardKey("test_1", GLFW_KEY_1);
    sceneData->input_ = input;

    //Scene
    SceneManagerInstance.Add<TitleScene>(SceneName::Title);
    SceneManagerInstance.Add<GameScene>(SceneName::Game);
    SceneManagerInstance.Initialize(SceneName::Title, 120);
    SceneManagerInstance.FadeColor(sip::Vector4(1.0f, 0.0f, 1.0f, 1.0f));
}

/**
 * @brief        更新
 */
void Application::Update() {
    //TODO:
    //アプリの更新処理を記述
    InputManagerInstance.Update();

    if (input_->GetKeyState(GLFW_KEY_ENTER)) {
        sound->Play();
    }

    SceneManagerInstance.Update();
}

/**
 * @brief        描画
 */
void Application::Render() {

    auto render_task = sip::RenderManager::CreateTask<sip::RenderCommandTask>(1);

    SceneManagerInstance.Render(render_task);
    
    RenderManagerInstance.Push(render_task);
}