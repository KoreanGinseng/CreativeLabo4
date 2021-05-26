#pragma once

#ifdef __MOFLIB
#include <Mof.h>

namespace sip {
    class CAniMakeData {
    private:

        SpriteAnimationCreate* m_pAnim;

        int                    m_AnimCount;

        std::string            m_TextureFileName;

    public:

        CAniMakeData(void);

        CAniMakeData(const CAniMakeData& obj);

        ~CAniMakeData(void);

        void operator= (const CAniMakeData& obj);

        // ********************************************************************************
        /// <summary>
        /// �A�j���[�V�����f�[�^���t�@�C������ǂݍ��݂��鏈���B
        /// </summary>
        /// <param name="fileName">�t�@�C����</param>
        /// <returns>����ɓǂݍ��߂��ꍇ true ����ȊO false </returns>
        /// <created>���̂���,2020/04/26</created>
        /// <changed>���̂���,2020/04/26</changed>
        // ********************************************************************************
        bool Load(LPCMofChar fileName);

        // ********************************************************************************
        /// <summary>
        /// �A�j���[�V�����f�[�^�̉���B
        /// </summary>
        /// <created>���̂���,2020/04/26</created>
        /// <changed>���̂���,2020/04/26</changed>
        // ********************************************************************************
        void Release(void);

        // ********************************************************************************
        /// <summary>
        /// �A�j���[�V�����\���̂̃|�C���^�擾�B
        /// </summary>
        /// <returns>�A�j���[�V�����\���̂̃|�C���^</returns>
        /// <created>���̂���,2020/04/26</created>
        /// <changed>���̂���,2020/04/26</changed>
        // ********************************************************************************
        SpriteAnimationCreate* GetAnim(void);

        // ********************************************************************************
        /// <summary>
        /// �A�j���[�V�����̐����擾����B
        /// </summary>
        /// <returns>�A�j���[�V�����̐�</returns>
        /// <created>���̂���,2020/04/26</created>
        /// <changed>���̂���,2020/04/26</changed>
        // ********************************************************************************
        int GetAnimationCount(void) const;

        // ********************************************************************************
        /// <summary>
        /// �A�j���[�V�����ɑΉ������摜�t�@�C�������擾����B
        /// </summary>
        /// <returns>�摜�t�@�C����</returns>
        /// <created>���̂���,2020/04/26</created>
        /// <changed>���̂���,2020/04/26</changed>
        // ********************************************************************************
        std::string GetTextureFileName(void) const;
    };
}

#endif __MOFLIB