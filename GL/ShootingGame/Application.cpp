#pragma once

#include    "Application.h"

#include    "Include/Input/InputManager.h"
#include    "Include/Input/GLInput.h"
#include    "Include/Input/LogInput.h"

#include    "Include/Render/RenderManager.h"
#include    "Include/Render/RenderCommandTask.h"
#include    "Include/Render/RenderClearCommand.h"
#include    "Include/Render/SpriteRenderCommand.h"
#include    "Include/Render/RenderFillRectCommand.h"

using namespace Sample;

//描画関連
ShaderPtr shader;
TexturePtr texture;
SpritePtr sprite;
CameraPtr camera;

//音関連
SoundPtr sound;

//キャラクター座標
Vector3F position(0, 0, 0);

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

    //TODO:
    //アプリの初期化処理を記述

    //画像読み込み
    texture = std::make_shared<Texture>("title.png");

    //シェーダー読み込み
    shader = std::make_shared<Shader>("Sprite.vert", "Sprite.frag");

    //描画用スプライト生成
    sprite = std::make_shared<Sprite>();
    sprite->Create(texture, shader);

    //カメラ設定
    camera = std::make_shared<Camera>();
    camera->Create2D(1024, 768);
    GraphicsController::GetInstance().Camera(camera);

    //音読み込み
    sound = std::make_shared<Sound>("se_enter.wav");

    InputManagerInstance.AddInput<sip::LogInput>()->CreateInput<sip::GLInput>(input_);
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
    if (input_->GetKeyState(GLFW_KEY_LEFT)) {
        position.x--;
    }
    if (input_->GetKeyState(GLFW_KEY_RIGHT)) {
        position.x++;
    }
}

/**
 * @brief        描画
 */
void Application::Render() {

    auto render_task = sip::RenderManager::CreateTask<sip::RenderCommandTask>(1);

    render_task->Push(sip::RenderClearCommand::Create(0, 1, 1, 0, 1, 0), 0);

    //TODO:
    //アプリの描画処理を記述
    sprite->Position(position);
    render_task->Push(sip::SpriteRenderCommand::Create(sprite), 0);
    render_task->Push(sip::RenderFillRectCommand::Create(Rectangle(0.0f, 0.0f, 100.0f, 100.0f), Vector4(1, 1, 1, 1)), 0);
    RenderManagerInstance.Push(render_task);
}