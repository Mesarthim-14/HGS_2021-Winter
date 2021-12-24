#ifndef _TEXTURE_H_
#define _TEXTURE_H_
//=============================================================================
//
// テクスチャの管理ヘッダー [texture.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"

//=============================================================================
//クラス宣言
//=============================================================================
class CTexture
{
public:
    // テクスチャの種類
    enum TEXTURE_TYPE_NUM
    {
        TEXTURE_TYPE_NUM_NONE = -1,         // 初期値
        TEXTURE_TYPE_NUM_NORMAL,            // 通常テクスチャ
        TEXTURE_TYPE_NUM_SEPARATE,          // 分割テクスチャ
        TEXTURE_TYPE_NUM_VOLUME,            // ボリュームテクスチャ
        TEXTURE_TYPE_NUM_CUBE,              // キューブテクスチャ
        TEXTURE_TYPE_NUM_MAX                // 最大値
    };

    // テクスチャの番号の列挙型
    enum TEXTURE_TYPE
    {
        TEXTURE_NUM_NONE = -1,  // 初期値 使うとき-1にしてください
        TEXTURE_NUM_TEST,       // テストテクスチャ
        TEXTURE_NUM_CPU_GU,     // グー
        TEXTURE_NUM_CPU_CHOKI,  // チョキ
        TEXTURE_NUM_CPU_PA,     // パー
        TEXTURE_NUM_GU,         // グー
        TEXTURE_NUM_CHOKI,      // チョキ
        TEXTURE_NUM_PA,         // パー
        TEXTURE_NUM_NUMBER,     // 数字
        TEXTURE_NUM_AUDIENCE1,  // 観客テクスチャ1
        TEXTURE_NUM_AUDIENCE2,  // 観客テクスチャ2
        TEXTURE_NUM_WIN,        // 勝ち
        TEXTURE_NUM_DRAW,       // 引き分け
        TEXTURE_NUM_LOSE,       // 負け
        TEXTURE_NUM_GIRLE,      // 女の子
        TEXTURE_NUM_PRESENT_BOX,      // プレゼントボックス
        TEXTURE_NUM_TITLE,      // タイトル
        TEXTURE_NUM_TUTORIAL,   // チュートリアル
        TEXTURE_NUM_GAME,       // ゲーム
        TEXTURE_NUM_RESULT,     // リザルト
        TEXTURE_NUM_MAX
    };

    // アニメーションを行うテクスチャの列挙型
    enum SEPARATE_TEX_TYPE
    {
        SEPARATE_TEX_NONE = -1,     // 初期値 使うとき-1にしてください
        SEPARATE_TEX_TEST,          // テストアニメーション
        SEPARATE_TEX_MAX            // 最大値
    };

    // アニメーションを行うテクスチャの構造体情報
    struct SEPARATE_TEX_INFO
    {
        LPDIRECT3DTEXTURE9 pSeparateTexture;    // 分割テクスチャへのポインタ
        SEPARATE_TEX_TYPE type;                 // テクスチャの種類
        INT_VERTEX_2D m_TexInfo;                // テクスチャの分割数、速さ
        bool bLoop;                             // ループするか
    };

    // ボリュームテクスチャの列挙型
    enum VOLUME_TEX_TYPE
    {
        VOLUME_TEX_NONE = 0,    // 初期値 使うとき-1にしてください
        VOLUME_TEX_MAX          // 最大値
    };

    // キューブテクスチャの列挙型
    enum CUBE_TEX_TYPE
    {
        CUBE_TEX_NONE = 0,      // 初期値 使うとき-1にしてください
        CUBE_TEX_MAX            // 最大値
    };

    CTexture();     // コンストラクタ
    ~CTexture();    // デストラクタ

    static CTexture *Create();  // インスタンス生成
    void LoadAll();             // 全てのロード
    void UnLoadAll();           // 全てのアンロード

    LPDIRECT3DTEXTURE9 GetTexture(const TEXTURE_TYPE &Tex_Type);                    // テクスチャの情報
    LPDIRECT3DTEXTURE9 GetSeparateTexture(const SEPARATE_TEX_TYPE &SepaTex_Type);   // 分割テクスチャ情報
    INT_VERTEX_2D GetSparateTexInfo(const SEPARATE_TEX_TYPE &SepaTex_Type);         // 分割テクスチャ　UVの枚数取得
    bool GetSparateTexLoop(const SEPARATE_TEX_TYPE &SepaTex_Type);                  // ループするか
    LPDIRECT3DVOLUMETEXTURE9 GetVolumeTexture(const VOLUME_TEX_TYPE &Tex_Type);     // ボリュームテクスチャの情報
    LPDIRECT3DCUBETEXTURE9 GetCubeTexture(const CUBE_TEX_TYPE &Tex_Type);           // キューブテクスチャの情報

private:
    // private関数
    HRESULT SetTextureName();   // テクスチャ名の設定

    // 通常テクスチャ
    HRESULT NormalTexLoad();    // テクスチャロード
    void NormalTexUnLoad();     // テクスチャアンロード
    // 分割テクスチャ
    HRESULT SeparateTexLoad();  // 分割テクスチャロード
    void SeparateTexUnLoad();   // 分割テクスチャアンロード
    // ボリュームテクスチャ
    HRESULT VolumeTexLoad();    // ボリュームテクスチャロード
    void VolumeTexUnLoad();     // ボリュームテクスチャアンロード
    // キューブテクスチャ
    HRESULT CubeTexLoad();      // キューブテクスチャロード
    void CubeTexUnLoad();       // キューブテクスチャアンロード

    // メンバ変数
    LPDIRECT3DTEXTURE9 m_apTexture[TEXTURE_NUM_MAX];            // テクスチャのポインタ
    SEPARATE_TEX_INFO m_apSeparateTexture[SEPARATE_TEX_MAX] =
    {
        nullptr, CTexture::SEPARATE_TEX_TEST, {8, 10}, true,
    };
    LPDIRECT3DVOLUMETEXTURE9 m_pVolumeTexture[VOLUME_TEX_MAX];  // ボリュームテクスチャ
    LPDIRECT3DCUBETEXTURE9 m_pCubeTexture[CUBE_TEX_MAX];        // キューブテクスチャ
    vector<string> m_aTexFileName[TEXTURE_TYPE_NUM_MAX];        // テクスチャの名前
};
#endif
