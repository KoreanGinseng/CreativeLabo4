#pragma once

#include	"../../Framework/Common/Common.h"

namespace sip {

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
#ifdef __GLLIB
#include "../../Framework/Graphics/Texture.h"
    using Texture    = Sample::Texture;
    using TexturePtr = Sample::TexturePtr;
#endif // __GLLIB
}