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
        /// アニメーションデータをファイルから読み込みする処理。
        /// </summary>
        /// <param name="fileName">ファイル名</param>
        /// <returns>正常に読み込めた場合 true それ以外 false </returns>
        /// <created>いのうえ,2020/04/26</created>
        /// <changed>いのうえ,2020/04/26</changed>
        // ********************************************************************************
        bool Load(LPCMofChar fileName);

        // ********************************************************************************
        /// <summary>
        /// アニメーションデータの解放。
        /// </summary>
        /// <created>いのうえ,2020/04/26</created>
        /// <changed>いのうえ,2020/04/26</changed>
        // ********************************************************************************
        void Release(void);

        // ********************************************************************************
        /// <summary>
        /// アニメーション構造体のポインタ取得。
        /// </summary>
        /// <returns>アニメーション構造体のポインタ</returns>
        /// <created>いのうえ,2020/04/26</created>
        /// <changed>いのうえ,2020/04/26</changed>
        // ********************************************************************************
        SpriteAnimationCreate* GetAnim(void);

        // ********************************************************************************
        /// <summary>
        /// アニメーションの数を取得する。
        /// </summary>
        /// <returns>アニメーションの数</returns>
        /// <created>いのうえ,2020/04/26</created>
        /// <changed>いのうえ,2020/04/26</changed>
        // ********************************************************************************
        int GetAnimationCount(void) const;

        // ********************************************************************************
        /// <summary>
        /// アニメーションに対応した画像ファイル名を取得する。
        /// </summary>
        /// <returns>画像ファイル名</returns>
        /// <created>いのうえ,2020/04/26</created>
        /// <changed>いのうえ,2020/04/26</changed>
        // ********************************************************************************
        std::string GetTextureFileName(void) const;
    };
}

#endif __MOFLIB