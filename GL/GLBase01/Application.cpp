#pragma once

#include	"Application.h"

using namespace Sample;

//�`��֘A
ShaderPtr shader;
TexturePtr texture;
SpritePtr sprite;
CameraPtr camera;

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

	//�V�F�[�_�[�ǂݍ���
	shader = std::make_shared<Shader>("Sprite.vert", "Sprite.frag");

	//�`��p�X�v���C�g����
	sprite = std::make_shared<Sprite>();
	sprite->Create(texture, shader);

	//�J�����ݒ�
	camera = std::make_shared<Camera>();
	camera->Create2D(1024, 768);
	GraphicsController::GetInstance().Camera(camera);

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
}

/**
 * @brief		�`��
 */
void Application::Render() {
	//�����ݒ�Ɖ�ʃN���A
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//TODO:
	//�A�v���̕`�揈�����L�q
	sprite->Position(position);
	sprite->RefreshMatrix();
	sprite->Render();

	//��ʂɕ\��
	glfwSwapBuffers(window_);
	glfwPollEvents();
}