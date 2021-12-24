#ifndef _PLAYER_H_
#define _PLAYER_H_
//=============================================================================
//
// プレイヤークラスヘッダー [player.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "judge.h"

//=============================================================================
// クラス定義
//=============================================================================
class CNumber2d;

//=============================================================================
// プレイヤークラス
//=============================================================================
class CPlayer : public CJudge
{
public:
    CPlayer(PRIORITY Priority = PRIORITY_CHARACTER);    // コンストラクタ
    ~CPlayer();                                         // デストラクタ

    static CPlayer*Create();    // クリエイト

    HRESULT Init();         // 初期化処理
    void Uninit();          // 終了処理
    void Update();          // 更新処理
    void EndCombo();        // コンボ終了
    void CreateEffect();    // 演出の生成

    // Get関数
    int GetCombo()const { return m_nCombo; }

private:
    void SelectHand();  // 手を選ぶ
    void Judge();       // 判定
    void AddCombo();    // コンボの加算
    void CreateCombo(); // コンボUI生成

    HAND_TYPE m_Correct;            // 正解
    vector<CNumber2d*> m_apCombo;   // コンボ用ポインタ
    int m_nCombo;                   // コンボ
    bool m_bCombo;                  // コンボを使用しているか
};
#endif