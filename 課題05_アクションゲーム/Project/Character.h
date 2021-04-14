#pragma once
#include "GameObject.h"

class CCharacter : public CGameObject {
protected:

    std::shared_ptr<CTexture> m_pTexture{ nullptr };

    Vector2                   m_Move{ 0.0f, 0.0f };

    int					      m_HP{ 0 };
    int						  m_DamageWait{ 0 };

public:
    
    CCharacter(void);
    ~CCharacter(void);

    virtual void Initialize(void) override;
    virtual void UpdateKey(void);
    virtual void UpdateMove(void);
    virtual void Update(void) override;
    virtual void Render(void);
    virtual std::string GetName(void) override;
    virtual CRectangle GetRect(void) override;
    void SetTexture(std::shared_ptr<CTexture>& ptr);
    virtual CRectangle GetAttackRect(void);
    virtual void Damage(int dmg);
    int GetHP(void) const;
    bool IsDamage(void) const;
};

