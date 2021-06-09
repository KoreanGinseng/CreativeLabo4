#include        "Application.h"
#include        "FrameWorkManager.h"

int main(void) {
    Sample::Framework* fw = new Sample::Application();
    FrameWorkManagerInstance.SetFramework(fw);
    fw->Create(1024, 768, "Sample");
    fw->Run();
    delete fw;
    return 0;
}
