#include "GLRenderEndCommand.h"

using namespace sip;

GLRenderEndCommand::GLRenderEndCommand(GLFWwindow* window)
    : window_(window) {
}

void GLRenderEndCommand::Exec() {
    if (window_) {
        //画面に表示
        glfwSwapBuffers(window_);
    }
}