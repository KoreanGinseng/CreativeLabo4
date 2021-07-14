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
#include    "Include/Resource/ResourceManager.h"

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
    glfwMakeContextCurrent(window_);

    //リソースディレクトリを素材配置先に指定
    ::SetCurrentDirectory(L"Resources");

    //シェーダー読み込み
    spriteShader_ = std::make_shared<Shader>("Sprite.vert", "Sprite.frag");
    GraphicsController::GetInstance().SpriteShader(spriteShader_);

    //カメラ設定
    camera = std::make_shared<Camera>();
    camera->Create2D(width_, height_);
    GraphicsController::GetInstance().Camera(camera);

    //音読み込み
    sound = std::make_shared<Sound>("se_enter.wav");

    auto sceneData = SceneManagerInstance.GetSceneData();
    auto debug_input0 = InputManagerInstance.AddInput<sip::LogInput>()->CreateInput<sip::GLInput>(input_);
    debug_input0->AddKeyboardKey("test_1", GLFW_KEY_1);
    sceneData->input_ = debug_input0;
    auto player_input1 = InputManagerInstance.AddInput<sip::LogInput>()->CreateInput<sip::GLInput>(input_);
    player_input1->AddKeyboardKey("Horizontal", GLFW_KEY_RIGHT, GLFW_KEY_LEFT);
    player_input1->AddKeyboardKey("Vertical"  , GLFW_KEY_DOWN , GLFW_KEY_UP  );

    //画像読み込み
    ResourceManagerInstance.LoadPack("Title", "TitleResources.json");
    ResourceManagerInstance.LoadPack("Stage1", "Stage1Resources.json");
    ResourceManagerInstance.LoadPack("Player1", "Player1Resources.json");

    //Scene
    SceneManagerInstance.FrameBufferCreate();
    SceneManagerInstance.Add<TitleScene>(SceneName::Title);
    SceneManagerInstance.Add<GameScene>(SceneName::Game);
    SceneManagerInstance.Initialize(SceneName::Title, 120);
    SceneManagerInstance.FadeColor(sip::Vector4(1.0f, 0.0f, 1.0f, 1.0f));

    glfwMakeContextCurrent(nullptr);
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