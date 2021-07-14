#include        "Application.h"
#include        "FrameWorkManager.h"

int main(void) {
    Sample::Framework* fw = new Sample::Application();
    FrameWorkManagerInstance.SetFramework(fw);
    fw->Create(298, 768, "Shooting");
    fw->Run();
    delete fw;
    return 0;
}
