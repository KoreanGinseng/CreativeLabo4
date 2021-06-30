#pragma once

#include	"Application.h"

using namespace Sample;

//�`��֘A
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

//���֘A
SoundPtr sound;

//�L�����N�^�[���W
Vector3F position(0,0,0);

/**
 * @brief		�R���X�g���N�^
 */
Application::Application()
: Framework() {
}

/**
 * @brief		�f�X�g���N�^
 */
Application::~Application() {
}

/**
 * @brief		������
 */
void Application::Initialize() {
	//���\�[�X�f�B���N�g����f�ޔz�u��Ɏw��
	::SetCurrentDirectory(L"Resources");

	//TODO:
	//�A�v���̏������������L�q

	//�摜�ǂݍ���
	texture = std::make_shared<Texture>("title.png");
	lineTexture = std::make_shared<Texture>("beam01.png");

	//�V�F�[�_�[�ǂݍ���
	shader = std::make_shared<Shader>("Sprite.vert", "Sprite.frag");
	shaderBatch = std::make_shared<Shader>("SpriteBatch.vert", "SpriteBatch.frag");

	//�`��p�X�v���C�g����
	sprite = std::make_shared<Sprite>();
	sprite->Create(texture, shader);
	spriteBatch = std::make_shared<SpriteBatch>();
	spriteBatch->Create(shaderBatch, 10000);

	//�|�����C������
	pline = std::make_shared<PolyLine>();
	pline->Create(lineTexture, shaderBatch);

	//�t�H���g����
	fontAtlas = std::make_shared<FontAtlas>();
	fontAtlas->Create("Stick-Regular.ttf", 32, 1024);
	fontRender = std::make_shared<FontRender>();
	fontRender->Create(shaderBatch);

	//�J�����ݒ�
	camera = std::make_shared<Camera>();
	camera->Create2D(1024, 768);
	GraphicsController::GetInstance().Camera(camera);

	//�t���[���o�b�t�@����
	frameBuffer = std::make_shared<FrameBuffer>();
	frameBuffer->Create(GraphicsController::GetInstance().ScreenWidth(),
		GraphicsController::GetInstance().ScreenHeight());
	frameSprite = frameBuffer->CreateSprite(shader);

	//�T���v������
	sampler = std::make_shared<Sampler>();
	sampler->Create();
	sampler->WrapMode(Sampler::Wrap::Clamp);
	sampler->FilterMode(Sampler::Filter::Nearest, Sampler::Filter::Nearest);

	//���ʂ������ėV��
	waveShader = std::make_shared<Shader>("wave.vert", "wave.frag");
	frameSpriteWave = frameBuffer->CreateSprite(waveShader);
	frameSpriteWave->Sampler(sampler);
	waveTimeBind = std::make_shared<ShaderParameterBind1F>(waveShader, "time");

	//���ʂ������ėV��
	circleShader = std::make_shared<Shader>("circle.vert", "circle.frag");
	frameSpriteCircle = frameBuffer->CreateSprite(circleShader);
	frameSpriteCircle->Sampler(sampler);
	circleTimeBind = std::make_shared<ShaderParameterBind1F>(circleShader, "time");

	//���ǂݍ���
	sound = std::make_shared<Sound>("se_enter.wav");
}

/**
 * @brief		�X�V
 */
void Application::Update() {
	//TODO:
	//�A�v���̍X�V�������L�q
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
 * @brief		�`��
 */
void Application::Render() {
	//�t���[���o�b�t�@���p
	frameBuffer->Bind();

	//�����ݒ�Ɖ�ʃN���A
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//TODO:
	//�A�v���̕`�揈�����L�q
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
	fontRender->Render(100, 100, Vector4F(1, 0, 0,1), "�{���͂��������悭\n�����I�I", fontAtlas);
	fontRender->Render(100, 200, Vector4F(0, 1, 0, 1), "��`�̐؂蔲���ԈႦ�Ă܂���", fontAtlas);

	std::cout << timer_->Time() << std::endl;

	//�^�[�Q�b�g�̃��Z�b�g
	GraphicsController::GetInstance().ResetTarget();

	//��ʃN���A
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//���ʂ������ĕ`��
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

	//��ʂɕ\��
	glfwSwapBuffers(window_);
	glfwPollEvents();
}