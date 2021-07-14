#pragma once

#include	"../../Framework/Common/Common.h"

namespace sip {

#ifdef __MOFLIB

    /**
     * MOF�̏ꍇ�͂��̂܂�CTexture�𗘗p
     */
#include	<Mof.h>
    class Texture : public CTexture {
        //CTexture�̃R���X�g���N�^�𗘗p
        using CTexture::CTexture;
    };
    //�|�C���^�u������
    using TexturePtr = std::shared_ptr<Texture>;

#endif // __MOFLIB
#ifdef __GLLIB
#include "../../Framework/Graphics/Texture.h"
    using Texture    = Sample::Texture;
    using TexturePtr = Sample::TexturePtr;
#endif // __GLLIB
}