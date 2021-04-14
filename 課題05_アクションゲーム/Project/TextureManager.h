#pragma once
#include "Mof.h"
#include <memory>
#include <unordered_map>

using CTexturePtr = std::shared_ptr<CTexture>;

/// <summary>
/// �摜�Ǘ��N���X
/// </summary>
class CTextureManager
{
private:

	//! �Ǘ����
	std::unordered_map <std::string, CTexturePtr> m_Manager;

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CTextureManager(void);

public:

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CTextureManager(void);

	/// <summary>
	/// �C���X�^���X�̎擾
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static CTextureManager& GetInstance(void);

	/// <summary>
	/// �摜�̎擾
	/// </summary>
	/// <param name="key">�o�^�L�[</param>
	/// <returns>�摜</returns>
    CTexturePtr& Get(const std::string& key);

	/// <summary>
	/// �摜�̓o�^
	/// </summary>
	/// <param name="key">�o�^�L�[</param>
	/// <param name="file">�o�^����摜�t�@�C���p�X</param>
	/// <returns>true : ����, false : ���s</returns>
	bool Register(const std::string& key, const std::string& file);

	/// <summary>
	/// �摜�̉��
	/// </summary>
	/// <param name="key">�o�^�L�[</param>
	/// <returns>true : ����, false : ���s</returns>
	bool Release(const std::string& key = "");
};

#define g_TextureManager CTextureManager::GetInstance()
