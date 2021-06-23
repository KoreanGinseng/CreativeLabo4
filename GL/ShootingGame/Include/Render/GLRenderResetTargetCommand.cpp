#include "GLRenderResetTargetCommand.h"

using namespace sip;

#ifdef __GLLIB
#include "../../Framework/Graphics/GraphicsController.h"

void GLRenderResetTargetCommand::Exec() {
    Sample::GraphicsController::GetInstance().ResetTarget();
}

#endif //__GLLIB