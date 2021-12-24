#ifndef _END_H_
#define _END_H_
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
class CEnd : public CScene2D
{
public:
    CEnd(PRIORITY = PRIORITY_CHARACTER); // コンストラクタ
    ~CEnd();                     // デストラクタ

    static CEnd *Create();   // インスタンス生成
    HRESULT Init();            // 初期化処理
    void Uninit();             // 終了処理
    void Update();             // 更新処理
    void Draw();
private:
    int m_nTexNum;
    int m_nCntRhythm;
};

#endif