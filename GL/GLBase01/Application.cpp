#pragma once

#include	"Application.h"

using namespace Sample;

//描画関連
ShaderPtr shader;
TexturePtr texture;
SpritePtr sprite;
CameraPtr camera;

//音関連
SoundPtr sound;

//キャラクター座標
Vector3F position(0,0,0);

/**
 * @brief		コンストラクタ
 */
Application::Application()
: Framework() {
}

/**
 * @brief		デストラクタ
 */
Application::~Application() {
}

/**
 * @brief		初期化
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
}

/**
 * @brief		更新
 */
void Application::Update() {
	//TODO:
	//アプリの更新処理を記述
	if (input_->GetKeyState(GLFW_KEY_ENTER))
	{
		sound->Play();
	}
	if (input_->GetKeyState(GLFW_KEY_LEFT))
	{
		position.x--;
	}
	if (input_->GetKeyState(GLFW_KEY_RIGHT))
	{
		position.x++;
	}
}

/**
 * @brief		描画
 */
void Application::Render() {
	//初期設定と画面クリア
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//TODO:
	//アプリの描画処理を記述
	sprite->Position(position);
	sprite->RefreshMatrix();
	sprite->Render();

	//画面に表示
	glfwSwapBuffers(window_);
	glfwPollEvents();
}