#pragma once

#include    "Application.h"

#include    "Include/Input/InputManager.h"
#include    "Include/Input/GLInput.h"
#include    "Include/Input/LogInput.h"

#include    "Include/Render/RenderManager.h"
#include    "Include/Render/RenderCommandTask.h"
#include    "Include/Render/RenderClearCommand.h"
#include    "Include/Render/SpriteRenderCommand.h"

using namespace Sample;

//�`��֘A
ShaderPtr shader;
TexturePtr texture;
SpritePtr sprite;
CameraPtr camera;

//���֘A
SoundPtr sound;

//�L�����N�^�[���W
Vector3F position(0, 0, 0);

/**
 * @brief        �R���X�g���N�^
 */
Application::Application()
    : Framework() {
}

/**
 * @brief        �f�X�g���N�^
 */
Application::~Application() {
    InputManagerInstance.Release();
    RenderManagerInstance.Release();
}

/**
 * @brief        ������
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

    InputManagerInstance.AddInput<sip::LogInput>()->CreateInput<sip::GLInput>(input_);
    glfwMakeContextCurrent(nullptr);
}

/**
 * @brief        �X�V
 */
void Application::Update() {
    //TODO:
    //�A�v���̍X�V�������L�q
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
 * @brief        �`��
 */
void Application::Render() {

    auto render_task = sip::RenderManager::CreateTask<sip::RenderCommandTask>(1);

    render_task->Push(sip::RenderClearCommand::Create(0, 1, 1, 0, 1, 0), 0);

    //TODO:
    //�A�v���̕`�揈�����L�q
    sprite->Position(position);
    render_task->Push(sip::SpriteRenderCommand::Create(sprite), 0);

    RenderManagerInstance.Push(render_task);
}