#pragma once
#include "GameObject.h"
#include "Character.h"

class CUIPlayerStatus : public CGameObject {
protected:

    std::shared_ptr<CTexture> m_pFrameTexture{ nullptr };
    std::shared_ptr<CTexture> m_pHPTexture{ nullptr };
    CCharacter* m_pPlayer{ nullptr };

public:

    virtual void Initialize(void) override;
    virtual void Update(void) override;
    virtual void Render(void);
    virtual std::string GetName(void) override;
    virtual CRectangle GetRect(void) override;
    void SetPlayer(CCharacter* player);
    void SetTexture(std::shared_ptr<CTexture>& frame, std::shared_ptr<CTexture>& hp);
};

