#pragma once

#include	"Application.h"

using namespace Sample;

//描画関連
ShaderPtr shader;
ShaderPtr shaderBatch;
TexturePtr texture;
SamplerPtr sampler;
SpritePtr sprite;
SpriteBatchPtr spriteBatch;
CameraPtr camera;

FontAtlasPtr fontAtlas;
FontRenderPtr fontRender;

FrameBufferPtr frameBuffer;
SpritePtr frameSprite;

ShaderPtr waveShader;
SpritePtr frameSpriteWave;
ShaderParameterBind1FPtr waveTimeBind;

ShaderPtr circleShader;
SpritePtr frameSpriteCircle;
ShaderParameterBind1FPtr circleTimeBind;

TexturePtr lineTexture;
PolyLinePtr pline;
PolyLine::LineArray lines;

float gTime = 0;

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
	lineTexture = std::make_shared<Texture>("beam01.png");

	//シェーダー読み込み
	shader = std::make_shared<Shader>("Sprite.vert", "Sprite.frag");
	shaderBatch = std::make_shared<Shader>("SpriteBatch.vert", "SpriteBatch.frag");

	//描画用スプライト生成
	sprite = std::make_shared<Sprite>();
	sprite->Create(texture, shader);
	spriteBatch = std::make_shared<SpriteBatch>();
	spriteBatch->Create(shaderBatch, 10000);

	//ポリライン生成
	pline = std::make_shared<PolyLine>();
	pline->Create(lineTexture, shaderBatch);

	//フォント生成
	fontAtlas = std::make_shared<FontAtlas>();
	fontAtlas->Create("Stick-Regular.ttf", 32, 1024);
	fontRender = std::make_shared<FontRender>();
	fontRender->Create(shaderBatch);

	//カメラ設定
	camera = std::make_shared<Camera>();
	camera->Create2D(1024, 768);
	GraphicsController::GetInstance().Camera(camera);

	//フレームバッファ生成
	frameBuffer = std::make_shared<FrameBuffer>();
	frameBuffer->Create(GraphicsController::GetInstance().ScreenWidth(),
		GraphicsController::GetInstance().ScreenHeight());
	frameSprite = frameBuffer->CreateSprite(shader);

	//サンプラ生成
	sampler = std::make_shared<Sampler>();
	sampler->Create();
	sampler->WrapMode(Sampler::Wrap::Clamp);
	sampler->FilterMode(Sampler::Filter::Nearest, Sampler::Filter::Nearest);

	//効果をかけて遊ぶ
	waveShader = std::make_shared<Shader>("wave.vert", "wave.frag");
	frameSpriteWave = frameBuffer->CreateSprite(waveShader);
	frameSpriteWave->Sampler(sampler);
	waveTimeBind = std::make_shared<ShaderParameterBind1F>(waveShader, "time");

	//効果をかけて遊ぶ
	circleShader = std::make_shared<Shader>("circle.vert", "circle.frag");
	frameSpriteCircle = frameBuffer->CreateSprite(circleShader);
	frameSpriteCircle->Sampler(sampler);
	circleTimeBind = std::make_shared<ShaderParameterBind1F>(circleShader, "time");

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

	double mx = input_->GetMouseX();
	double my = input_->GetMouseY();
	if (lines.size() > 0)
	{
		PolyLine::Line& line = lines[0];
		line.front.x = mx - line.pos.x;
		line.front.y = my - line.pos.y;
		line.front = Vector3F::Normalize(line.front);
	}
	lines.insert(lines.begin(), {Vector3F(mx,my,0), Vector3F(), 10, Vector4F(1,1,1,1)});
	while (lines.size() >= 100)
	{
		lines.pop_back();
	}
}

/**
 * @brief		描画
 */
void Application::Render() {
	//フレームバッファ利用
	frameBuffer->Bind();

	//初期設定と画面クリア
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//TODO:
	//アプリの描画処理を記述
	if (input_->GetKeyState(GLFW_KEY_A))
	{
		spriteBatch->Reset();
		for (int i = 0; i < 10; i++)
		{
			spriteBatch->RenderRegister(texture, position + Vector3F(0, i * 60, 0));
		}
		spriteBatch->RefreshVertex();
		spriteBatch->Render();
	}
	else
	{
		for (int i = 0; i < 10; i++)
		{
			sprite->Position(position + Vector3F(0, i * 60, 0));
			sprite->RefreshMatrix();
			sprite->Render();
		}
	}
	pline->RefreshVertex(lines);
	pline->Render();
	fontRender->Render(100, 100, Vector4F(1, 0, 0,1), "本日はお日柄もよく\n眠い！！", fontAtlas);
	fontRender->Render(100, 200, Vector4F(0, 1, 0, 1), "矩形の切り抜き間違えてました", fontAtlas);

	std::cout << timer_->Time() << std::endl;

	//ターゲットのリセット
	GraphicsController::GetInstance().ResetTarget();

	//画面クリア
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//効果をかけて描画
	if (input_->GetKeyState(GLFW_KEY_W))
	{
		gTime += timer_->Time();
		waveTimeBind->Value(gTime);
		frameSpriteWave->Render({ waveTimeBind });
	}
	else if (input_->GetKeyState(GLFW_KEY_C))
	{
		gTime += timer_->Time();
		circleTimeBind->Value(gTime);
		frameSpriteCircle->Render({ circleTimeBind });
	}
	else
	{
		gTime = 0;
		frameSprite->Render();
	}

	//画面に表示
	glfwSwapBuffers(window_);
	glfwPollEvents();
}