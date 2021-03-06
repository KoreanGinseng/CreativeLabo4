#include "GLRenderClearCommand.h"

using namespace sip;

#ifdef __GLLIB

void GLRenderClearCommand::Exec() {
    //初期設定と画面クリア
    glClearColor(R_, G_, B_, A_);
    glClearDepth(D_);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

#endif //__GLLIB