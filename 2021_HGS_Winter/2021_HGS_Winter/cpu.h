#ifndef _CPU_H_
#define _CPU_H_
//=============================================================================
//
// CPUクラス [cpu.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// インクルード
//=========================================================================
#include "judge.h"

//=========================================================================
// 前方宣言
//=========================================================================
class CScene2D;
class CPlayer;

//=========================================================================
// クラス定義
//=========================================================================
class CCpu : public CJudge
{
public:
    CCpu(PRIORITY = PRIORITY_MODEL);    // コンストラクタ
    ~CCpu();                            // デストラクタ

    static CCpu *Create();  // インスタンス生成
    HRESULT Init();         // 初期化処理
    void Uninit();          // 終了処理
    void Update();          // 更新処理
    void Draw();            // 描画

    void SetJudge(const bool& bFlag)    { m_bJudge = bFlag; }  // ジャッジ
    bool GetJudge()const                { return m_bJudge; }
    CORRECT_TYPE GetCorrect()const      { return m_Correct; }

private:
    void SelectJudge(); // 手を選ぶ
    void SubInter(CPlayer* &pPlayer);    // 間隔の減算

    CORRECT_TYPE m_Correct; // 正解の手
    int m_nCounter;         // かうんたー
    int m_nInterval;        // インターバル
    int m_nSubInter;        // インターバルの減算値
    bool m_bJudge;          // ジャッジ
};

#endif