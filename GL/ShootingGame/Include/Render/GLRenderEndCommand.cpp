#include "GLRenderEndCommand.h"

using namespace sip;

GLRenderEndCommand::GLRenderEndCommand(GLFWwindow* window)
    : window_(window) {
}

void GLRenderEndCommand::Exec() {
    if (window_) {
        //‰æ–Ê‚É•\Ž¦
        glfwSwapBuffers(window_);
    }
}