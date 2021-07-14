#include "GLRenderEndCommand.h"

using namespace sip;

GLRenderEndCommand::GLRenderEndCommand(GLFWwindow* window)
    : window_(window) {
}

void GLRenderEndCommand::Exec() {
    if (window_) {
        //��ʂɕ\��
        glfwSwapBuffers(window_);
    }
}