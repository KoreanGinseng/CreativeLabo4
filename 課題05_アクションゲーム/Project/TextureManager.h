#pragma once
#include "Mof.h"
#include <memory>
#include <unordered_map>

/// <summary>
/// �摜�Ǘ��N���X
/// </summary>
class CTextureManager
{
private:

	//! �Ǘ����
	std::unordered_map <std::string, std::shared_ptr<CTexture>> m_Manager;

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
	std::shared_ptr<CTexture>& Get(const std::string& key);

	/// <summary>
	/// �摜�̓o�^
	/// </summary>
	/// <param name="key">�o�^�L�[</param>
	/// <param name="file">�o�^����摜�t�@�C���p�X</param>
	/// <returns>true : ����, false : ���s</returns>
	bool Register(const std::string& key, const std::string& file);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="key"></param>
	/// <returns></returns>
	bool Release(const std::string& key = "");
};

#define g_TextureManager CTextureManager::GetInstance()
