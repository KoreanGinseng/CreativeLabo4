#pragma once
#include "Mof.h"

class CGameObject {
protected:

    Vector2 m_Pos{ 0.0f, 0.0f };

public:

    CGameObject(void) = default;
    ~CGameObject(void) = default;

    virtual void Initialize(void) = 0;
    virtual void Update(void) = 0;
    virtual std::string GetName(void) = 0;
    virtual CRectangle GetRect(void) = 0;
};

