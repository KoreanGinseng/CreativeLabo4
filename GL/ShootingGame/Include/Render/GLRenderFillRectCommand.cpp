#include "GLRenderFillRectCommand.h"
#include "../../Framework/Common/Common.h"

using namespace sip;

void GLRenderFillRectCommand::Exec() {
    glColor4f(color_.r, color_.g, color_.b, color_.a);
    glBegin(GL_QUADS);
    int w = 1024;
    int h = 768;
    
    if (w == 0.0f || h == 0.0f) {
        glEnd();
        return;
    }
    float x1 = (rect_.Left   - w * 0.5f) / w * 0.5f;
    float x2 = (rect_.Right  - w * 0.5f) / w * 0.5f;
    float y1 = (rect_.Top    - h * 0.5f) / h * 0.5f;
    float y2 = (rect_.Bottom - h * 0.5f) / h * 0.5f;
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
}