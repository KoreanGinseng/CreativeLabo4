#include "UIPlayerStatus.h"

void CUIPlayerStatus::Initialize(void) {
}

void CUIPlayerStatus::Update(void) {
}

void CUIPlayerStatus::Render(void) {
    if (m_pFrameTexture == nullptr ||
        m_pHPTexture    == nullptr ||
        m_pPlayer       == nullptr) {
        return;
    }

    const int HP = m_pPlayer->GetHP();
    
    //HP‚É‰ž‚¶‚Ä‹éŒ`‚Ì•‚ð•Ï‰»‚³‚¹‚é
    CRectangle rec(0, 0, 532 * (HP * 0.01f), 64);
    m_pHPTexture->Render(248, 20, rec);
    //ƒtƒŒ[ƒ€‚ðã•”‚É•`‰æ
    m_pFrameTexture->Render(0, 0);
}

std::string CUIPlayerStatus::GetName(void) {
    return "UIPlayerStatus";
}

CRectangle CUIPlayerStatus::GetRect(void) {
    if (m_pFrameTexture == nullptr) {
        return CRectangle();
    }
    return CRectangle(
        m_Pos.x,
        m_Pos.y,
        m_Pos.x + m_pFrameTexture->GetWidth(),
        m_Pos.y + m_pFrameTexture->GetHeight()
    );
}

void CUIPlayerStatus::SetPlayer(CCharacter * player) {
    m_pPlayer = player;
}

void CUIPlayerStatus::SetTexture(std::shared_ptr<CTexture>& frame, std::shared_ptr<CTexture>& hp) {
    m_pFrameTexture = frame;
    m_pHPTexture = hp;
}
