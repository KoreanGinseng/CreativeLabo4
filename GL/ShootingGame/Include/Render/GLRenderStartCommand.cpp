#include "GLRenderStartCommand.h"

using namespace sip;

void GLRenderStartCommand::Exec() {
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}