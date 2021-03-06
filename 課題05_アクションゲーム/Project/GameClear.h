#pragma once

class CGameClear {
private:
	CTexture				m_BackImage;
public:
	CGameClear();
	~CGameClear();
	bool Load(void);
	void Initialize(void);
	void Update(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
};