#include "GLRenderClearCommand.h"

using namespace sip;

#ifdef __GLLIB

void GLRenderClearCommand::Exec() {
    //�����ݒ�Ɖ�ʃN���A
    glClearColor(R_, G_, B_, A_);
    glClearDepth(D_);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

#endif //__GLLIB