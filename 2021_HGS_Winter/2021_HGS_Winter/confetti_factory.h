//=============================================================================
//
// confetti_factoryヘッダ [confetti_factory.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _CONFETTI_FACTORY_H_
#define _CONFETTI_FACTORY_H_

//*****************************
//インクルード
//*****************************
#include "scene_base.h"

//*****************************
//クラス定義
//*****************************

// 紙吹雪ファクトリークラス
class CConfettiFactory : public CScene
{
public:
    //============
    // メンバ関数
    //============
    CConfettiFactory();
    ~CConfettiFactory();

    static CConfettiFactory *Create(D3DXCOLOR col, int nLife = -1); // クラス生成

    HRESULT Init(); // 初期化
    void Uninit();  // 終了処理
    void Update();  // 更新
    void Draw();    // 描画
private:
    //============
    // メンバ変数
    //============
    int m_nLife;
    int m_nCntConfetti;
    D3DXCOLOR m_col;
};

#endif