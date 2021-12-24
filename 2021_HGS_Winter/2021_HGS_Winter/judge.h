#ifndef _JUDGE_H_
#define _JUDGE_H_
//=============================================================================
//
// CPUクラス [cpu.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// インクルード
//=========================================================================
#include "model.h"

//=========================================================================
// 前方宣言
//=========================================================================
class CScene2D;

//=========================================================================
// クラス定義
//=========================================================================
class CJudge : public CScene
{
public:
    enum HAND_TYPE
    {
        HAND_TYPE_NONE = -1,  // 初期値
        HAND_TYPE_GU,         // グー
        HAND_TYPE_CHOKI,      // チョキ
        HAND_TYPE_PA,         // パー
        HAND_TYPE_MAX         // 最大値
    };
    enum CORRECT_TYPE
    {
        CORRECT_TYPE_NONE = -1,  // 初期値
        CORRECT_TYPE_WIN,        // 勝ち
        CORRECT_TYPE_DRAW,       // 引き分け
        CORRECT_TYPE_LOSE,       // 負け
        CORRECT_TYPE_MAX         // 最大値
    };

    CJudge(PRIORITY = PRIORITY_MODEL);    // コンストラクタ
    ~CJudge();                              // デストラクタ

    static CJudge *Create();    // インスタンス生成
    virtual HRESULT Init();     // 初期化処理
    virtual void Uninit();      // 終了処理
    virtual void Update();      // 更新処理
    void Draw() {}

    // Set関数
    void SetHand(HAND_TYPE Num) { m_Hand = Num; }
    void BindScene2D(CScene2D* pScene);

    // Get関数
    HAND_TYPE GetHand()const    { return m_Hand; }
    CScene2D* GetScene()const   { return m_pScene2D; }

private:
    HAND_TYPE m_Hand;       // 出す手
    CScene2D* m_pScene2D;   // 画像
};

#endif