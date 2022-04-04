#pragma once
#include "SceneManager.h"
#include "Include/Input/Input.h"

struct GameSceneData : public EmptyData {
    sip::InputPtr input_;
};

enum class SceneName {
    Title,
    Game,
    GameClear,
    GameOver,
};

#define SceneManagerInstance SceneManager<SceneName, GameSceneData>::GetInstance()