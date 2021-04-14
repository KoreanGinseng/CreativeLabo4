#include "Character.h"

CCharacter::CCharacter(void) {
}

CCharacter::~CCharacter(void) {
}

void CCharacter::Initialize(void) {
}

void CCharacter::UpdateKey(void) {
}

void CCharacter::UpdateMove(void) {
}

void CCharacter::Update(void) {
    m_Pos += m_Move;
}

void CCharacter::Render(void) {
    if (m_pTexture == nullptr) {
        return;
    }
    m_pTexture->Render(m_Pos.x, m_Pos.y);
}

std::string CCharacter::GetName(void) {
    return "Character";
}

void CCharacter::SetTexture(std::shared_ptr<CTexture>& ptr) {
    m_pTexture = ptr;
}

CRectangle CCharacter::GetRect(void) {
    return CRectangle();
}

CRectangle CCharacter::GetAttackRect(void) {
    return CRectangle();
}

void CCharacter::Damage(int dmg) {
    m_HP = MOF_MAX((m_HP - dmg), 0);
}

int CCharacter::GetHP(void) const {
    return m_HP;
}

bool CCharacter::IsDamage(void) const {
    return m_DamageWait > 0;
}
