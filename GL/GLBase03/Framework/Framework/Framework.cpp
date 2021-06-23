#include	"Framework.h"

using namespace Sample;

/**
 * @brief		エラー発生時に呼び出されるコールバック
 */
void ErrorCallback(int error, const char* desc)
{
	ERROR_LOG(desc);
}

/**
 * @brief		コンストラクタ
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
 * @brief		デストラクタ
 */
Framework::~Framework() {
	glfwTerminate();
}

/**
 * @brief		フレームワークの生成
 * @param[in]	w		画面の幅
 * @param[in]	h		画面の高さ
 * @param[in]	title	ウインドウタイトル
 */
bool Framework::Create(int w, int h, const char* title) {
	//GLFWの初期化
	glfwSetErrorCallback(ErrorCallback);
	if (glfwInit() != GL_TRUE)
	{
		return false;
	}

	//GLバージョンやプロファイルの設定
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	//ウインドウの生成
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

	//GLEWの初期化
	if (glewInit() != GLEW_OK)
	{
		ERROR_LOG("GLEWの初期化に失敗しました");
		return false;
	}

	//Audio初期化
	audio_->Initialize();

	//入力の生成
	input_ = std::make_shared<Input>(window_);

	//GraphicsController初期化
	GraphicsController::GetInstance().Initialize(window_);

	//初期化終了
	INFO_LOG("Frameworkの初期化終了...");
	return true;
}

/**
 * @brief		フレームワークの実行
 */
void Framework::Run() {
	//初期化
	Initialize();

	//アプリループ
	while (!glfwWindowShouldClose(window_))
	{
		//タイマー処理
		timer_->Refresh();
		timer_->Sleep();

		//入力の更新
		input_->Refresh();

		//アプリの更新
		Update();

		//アプリの描画
		Render();
	}

	//アプリ終了
	INFO_LOG("Frameworkの終了...");
	audio_.reset();
	glfwDestroyWindow(window_);
}