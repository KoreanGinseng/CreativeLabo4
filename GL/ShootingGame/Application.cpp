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

using namespace Sample;

//�`��֘A
CameraPtr camera;

//���֘A
SoundPtr sound;

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

    //�V�F�[�_�[�ǂݍ���
    spriteShader_ = std::make_shared<Shader>("Sprite.vert", "Sprite.frag");
    GraphicsController::GetInstance().SpriteShader(spriteShader_);

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
}

/**
 * @brief        �`��
 */
void Application::Render() {

    auto render_task = sip::RenderManager::CreateTask<sip::RenderCommandTask>(1);

    
    RenderManagerInstance.Push(render_task);
}