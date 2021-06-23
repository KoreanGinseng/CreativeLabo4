#include	"Framework.h"

using namespace Sample;

/**
 * @brief		�G���[�������ɌĂяo�����R�[���o�b�N
 */
void ErrorCallback(int error, const char* desc)
{
	ERROR_LOG(desc);
}

/**
 * @brief		�R���X�g���N�^
 */
Framework::Framework()
: window_(nullptr) 
, timer_(std::make_shared<GLFrameTimer>(60))
, audio_(std::make_shared<Audio>())
, input_()
, width_(0)
, height_(0) {
}

/**
 * @brief		�f�X�g���N�^
 */
Framework::~Framework() {
	glfwTerminate();
}

/**
 * @brief		�t���[�����[�N�̐���
 * @param[in]	w		��ʂ̕�
 * @param[in]	h		��ʂ̍���
 * @param[in]	title	�E�C���h�E�^�C�g��
 */
bool Framework::Create(int w, int h, const char* title) {
	//GLFW�̏�����
	glfwSetErrorCallback(ErrorCallback);
	if (glfwInit() != GL_TRUE)
	{
		return false;
	}

	//GL�o�[�W������v���t�@�C���̐ݒ�
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	//�E�C���h�E�̐���
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_MAXIMIZED, GL_FALSE);
	window_ = glfwCreateWindow(w, h, title, nullptr, nullptr);
	if (!window_)
	{
		return false;
	}
	width_ = w;
	height_ = h;
	glfwMakeContextCurrent(window_);

	//GLEW�̏�����
	if (glewInit() != GLEW_OK)
	{
		ERROR_LOG("GLEW�̏������Ɏ��s���܂���");
		return false;
	}

	//Audio������
	audio_->Initialize();

	//���͂̐���
	input_ = std::make_shared<Input>(window_);

	//GraphicsController������
	GraphicsController::GetInstance().Initialize(window_);

	//�������I��
	INFO_LOG("Framework�̏������I��...");
	return true;
}

/**
 * @brief		�t���[�����[�N�̎��s
 */
void Framework::Run() {
	//������
	Initialize();

	//�A�v�����[�v
	while (!glfwWindowShouldClose(window_))
	{
		//�^�C�}�[����
		timer_->Refresh();
		timer_->Sleep();

		//���͂̍X�V
		input_->Refresh();

		//�A�v���̍X�V
		Update();

		//�A�v���̕`��
		Render();
	}

	//�A�v���I��
	INFO_LOG("Framework�̏I��...");
	audio_.reset();
	glfwDestroyWindow(window_);
}