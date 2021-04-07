#pragma once
#include "Mof.h"
#include <memory>
#include <unordered_map>

/// <summary>
/// 画像管理クラス
/// </summary>
class CTextureManager
{
private:

	//! 管理やつ
	std::unordered_map <std::string, std::shared_ptr<CTexture>> m_Manager;

	/// <summary>
	/// コンストラクタ
	/// </summary>
	CTextureManager(void);

public:

	/// <summary>
	/// デストラクタ
	/// </summary>
	~CTextureManager(void);

	/// <summary>
	/// インスタンスの取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static CTextureManager& GetInstance(void);

	/// <summary>
	/// 画像の取得
	/// </summary>
	/// <param name="key">登録キー</param>
	/// <returns>画像</returns>
	std::shared_ptr<CTexture>& Get(const std::string& key);

	/// <summary>
	/// 画像の登録
	/// </summary>
	/// <param name="key">登録キー</param>
	/// <param name="file">登録する画像ファイルパス</param>
	/// <returns>true : 成功, false : 失敗</returns>
	bool Register(const std::string& key, const std::string& file);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="key"></param>
	/// <returns></returns>
	bool Release(const std::string& key = "");
};

#define g_TextureManager CTextureManager::GetInstance()
