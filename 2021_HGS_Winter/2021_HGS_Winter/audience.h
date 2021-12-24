#ifndef _AUDIENCE_H_
#define _AUDIENCE_H_
//=============================================================================
//
// 観客クラス [audience.h]
// Author : Masuzawa Mirai
//
//=============================================================================

//=========================================================================
// インクルード
//=========================================================================
#include "scene2d.h"

//=========================================================================
// 前方宣言
//=========================================================================

//=========================================================================
// クラス定義
//=========================================================================
class CAudience : public CScene2D
{
public:
    enum AUDIENCE_PARTS
    {
        PARTS_BACK = 0,
        PARTS_FRONT,
        PARTS_MAX
    };

    CAudience(PRIORITY = PRIORITY_UI); // コンストラクタ
    ~CAudience();                     // デストラクタ

    static CAudience *Create();   // インスタンス生成
    HRESULT Init();            // 初期化処理
    void Uninit();             // 終了処理
    void Update();             // 更新処理
    void Draw();               // 描画

    void SetUpFrag(bool bUp) { m_bUp = bUp; }
private:

    const static D3DXVECTOR3 m_aUpPos[PARTS_MAX];
    CScene2D *m_apPolygon[PARTS_MAX];
    D3DXVECTOR3 m_basePos[PARTS_MAX];
    D3DXVECTOR3 m_aOffsetPos[PARTS_MAX];
    float       m_afMoveY[PARTS_MAX];
    bool m_bUp;
    int m_nCntUp;

};

#endif