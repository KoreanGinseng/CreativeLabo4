#pragma once

#include	"../Common/Common.h"

namespace Sample {

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

}