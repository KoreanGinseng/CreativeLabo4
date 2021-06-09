#include "GLRenderEndCommand.h"

using namespace sip;

GLRenderEndCommand::GLRenderEndCommand(GLFWwindow* window)
    : window_(window) {
}

void GLRenderEndCommand::Exec() {
    //画面に表示
    glfwSwapBuffers(window_);
}