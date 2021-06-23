#include "GLRenderFrameBufferBindCommand.h"

using namespace sip;

#ifdef __GLLIB

void GLRenderFrameBufferBindCommand::Exec() {
    buffer_->Bind();
}

#endif //__GLLIB
