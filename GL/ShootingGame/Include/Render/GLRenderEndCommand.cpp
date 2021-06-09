#include "GLRenderEndCommand.h"

using namespace sip;

GLRenderEndCommand::GLRenderEndCommand(GLFWwindow* window)
    : window_(window) {
}

void GLRenderEndCommand::Exec() {
    //��ʂɕ\��
    glfwSwapBuffers(window_);
}