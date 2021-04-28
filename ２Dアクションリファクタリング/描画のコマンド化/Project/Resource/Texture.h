#pragma once

#include	"../Common/Common.h"

namespace Sample {

#ifdef __MOFLIB

	/**
	 * MOFの場合はそのままCTextureを利用
	 */
#include	<Mof.h>
	class Texture : public CTexture {
		//CTextureのコンストラクタを利用
		using CTexture::CTexture;
	};
	//ポインタ置き換え
	using TexturePtr = std::shared_ptr<Texture>;

#endif // __MOFLIB

}