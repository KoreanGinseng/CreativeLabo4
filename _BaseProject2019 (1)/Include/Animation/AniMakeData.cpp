#include "AniMakeData.h"

#ifdef __MOFLIB
using namespace sip;

CAniMakeData::CAniMakeData(void) :
    m_pAnim(nullptr),
    m_AnimCount(0),
    m_TextureFileName("") {
}

CAniMakeData::CAniMakeData(const CAniMakeData& obj) {
    m_pAnim = obj.m_pAnim;
    m_AnimCount = obj.m_AnimCount;
}

CAniMakeData::~CAniMakeData(void) {
    Release();
}

void CAniMakeData::operator=(const CAniMakeData& obj) {
    m_pAnim = obj.m_pAnim;
    m_AnimCount = obj.m_AnimCount;
}

// ********************************************************************************
/// <summary>
/// アニメーションデータをファイルから読み込みする処理。
/// </summary>
/// <param name="fileName">ファイル名</param>
/// <returns>正常に読み込めた場合 true それ以外 false </returns>
/// <created>いのうえ,2020/04/26</created>
/// <changed>いのうえ,2020/04/26</changed>
// ********************************************************************************
bool CAniMakeData::Load(LPCMofChar fileName) {
    FILE* filePointer = fopen(fileName, "rb");

    //ファイルが開けなかった場合、エラーで即リターン。
    if (filePointer == NULL) {
        return false;
    }

    /// ###          読み込むデータの順番は以下の通り          ###
    //     ・テクスチャのファイル名の長さ( int   )
    //     ・テクスチャのファイル名      ( char  )
    //     ・アニメーションの数          ( int   )
    /// ##ここからアニメーションの数だけループ
    //     ・アニメーション名の長さ      ( int   )
    //     ・アニメーション名            ( char  )
    //     ・オフセットX                 ( float )
    //     ・オフセットY                 ( float )
    //     ・横幅                        ( float )
    //     ・高さ                        ( float )
    //     ・ループフラグ                ( char  )
    //     ・アニメーションパターン数    ( int   )
    ///  #ここからパターンの数だけループ
    //     ・待機フレーム                ( float ) 
    //     ・No                          ( int   )
    //     ・Step                        ( int   )
    ///  #ここまでパターンの数だけループ
    /// ##ここまでアニメーションの数だけループ
    //     ・テキストファイル名の長さ    ( int   ) #読み込まない
    //     ・テキストファイル名          ( char  ) #読み込まない
    //     ・EOF
    /// ###          ここまで.animファイル                     ###


    //・テクスチャのファイル名の長さ取得。
    int textureFileNameLength;
    fread(&textureFileNameLength, sizeof(int), 1, filePointer);

    //・テクスチャのファイル名の取得。
    char* textureFileName = new char[textureFileNameLength + 1];
    fread(textureFileName, sizeof(char), textureFileNameLength, filePointer);

    //取得したら文字列終端文字をけつにつける。
    textureFileName[textureFileNameLength] = '\0';

    //メンバ変数に保存しておく。
    m_TextureFileName = textureFileName;

    //動的確保したら消すのを忘れないように。
    MOF_SAFE_DELETE_ARRAY(textureFileName);

    //・アニメーションの数取得。
    int animationCount;
    fread(&animationCount, sizeof(int), 1, filePointer);

    //メンバ変数に保存しておく。
    m_AnimCount = animationCount;

    //アニメーションの数だけ構造体を確保する。(二重で作成しないように解放処理を先にする。)
    MOF_SAFE_DELETE_ARRAY(m_pAnim);
    m_pAnim = new SpriteAnimationCreate[m_AnimCount];

    //アニメーションの数だけループする。
    for (int i = 0; i < m_AnimCount; i++) {
        //アニメーションデータの間接参照。(呼び出す回数を最小限にするため)
        SpriteAnimationCreate* pAnim = &(m_pAnim[i]);

        //アニメーション名の長さ取得。
        int animNameLength;
        fread(&animNameLength, sizeof(int), 1, filePointer);

        //アニメーション名の取得。
        char* animName = new char[animNameLength + 1];
        fread(animName, sizeof(char), animNameLength, filePointer);

        //名前を取得したらけつに文字列終端文字を付ける。
        animName[animNameLength] = '\0';

        //データにコピーする。
        pAnim->Name = animName;

        //用が終わったら早めに解放してやる。
        MOF_SAFE_DELETE_ARRAY(animName);

        //各データの取得。
        fread(&(pAnim->OffsetX), sizeof(float), 1, filePointer);
        fread(&(pAnim->OffsetY), sizeof(float), 1, filePointer);
        fread(&(pAnim->Width), sizeof(float), 1, filePointer);
        fread(&(pAnim->Height), sizeof(float), 1, filePointer);
        fread(&(pAnim->bLoop), sizeof(char), 1, filePointer);

        //アニメーションパターンの数を取得。
        int patternCount;
        fread(&patternCount, sizeof(int), 1, filePointer);

        //パターンの数だけループする。
        for (int j = 0; j < patternCount; j++) {
            //呼び出し回数をなるべく減らそう。
            SpriteAnimationCreatePattern* pPattern = &(pAnim->Pattern[j]);

            //各データの取得。
            fread(&(pPattern->Wait), sizeof(float), 1, filePointer);
            fread(&(pPattern->No), sizeof(int), 1, filePointer);
            fread(&(pPattern->Step), sizeof(int), 1, filePointer);
        }
    }

    //開けたら閉めよう。忘れるなよ。
    fclose(filePointer);

    return true;
}

// ********************************************************************************
/// <summary>
/// アニメーションデータの解放。
/// </summary>
/// <created>いのうえ,2020/04/26</created>
/// <changed>いのうえ,2020/04/26</changed>
// ********************************************************************************
void CAniMakeData::Release(void) {
    MOF_SAFE_DELETE_ARRAY(m_pAnim);
}

// ********************************************************************************
/// <summary>
/// アニメーション構造体のポインタ取得。
/// </summary>
/// <returns>アニメーション構造体のポインタ</returns>
/// <created>いのうえ,2020/04/26</created>
/// <changed>いのうえ,2020/04/26</changed>
// ********************************************************************************
SpriteAnimationCreate* CAniMakeData::GetAnim(void) {
    return m_pAnim;
}

// ********************************************************************************
/// <summary>
/// アニメーションの数を取得する。
/// </summary>
/// <returns>アニメーションの数</returns>
/// <created>いのうえ,2020/04/26</created>
/// <changed>いのうえ,2020/04/26</changed>
// ********************************************************************************
int CAniMakeData::GetAnimationCount(void) const {
    return m_AnimCount;
}

// ********************************************************************************
/// <summary>
/// アニメーションに対応した画像ファイル名を取得する。
/// </summary>
/// <returns>画像ファイル名</returns>
/// <created>いのうえ,2020/04/26</created>
/// <changed>いのうえ,2020/04/26</changed>
// ********************************************************************************
std::string CAniMakeData::GetTextureFileName(void) const {
    return m_TextureFileName;
}

#endif //__MOFLIB