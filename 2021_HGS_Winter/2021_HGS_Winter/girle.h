#ifndef _GIRLE_H_
#define _GIRLE_H_
//=============================================================================
//
// 女の子クラス [girle.h]
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
class CGirle : public CScene2D
{
public:
    enum TEX_ANIM_STATE
    {
        STATE_UP = 0,
        STATE_DOWN,
        STATE_MAX
    };
    CGirle(PRIORITY = PRIORITY_CHARACTER); // コンストラクタ
    ~CGirle();                     // デストラクタ

    static CGirle *Create();   // インスタンス生成
    HRESULT Init();            // 初期化処理
    void Uninit();             // 終了処理
    void Update();             // 更新処理
    void Draw();

    void SetAnim(TEX_ANIM_STATE state) { m_nTexNum = state; }
private:
    int m_nTexNum;
    int m_nCntRhythm;
};

#endif