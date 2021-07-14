#pragma once
#include "GameObject.h"

class Stage {
private:

    int stageNo_;

    SpritePtr backGroundSprite_;

    int scroll_;

public:
    
    Stage();

    ~Stage();

    void Initialize(int stageNo);

    void Update();

    void Render(sip::RenderCommandTaskPtr& render_task);

    int Scroll() const { return scroll_; }
}; 

