#ifndef _GAME_H_
#define _GAME_H_
//=======================================================================================
//
// ゲームクラス [game.h]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// インクルードファイル
//=======================================================================================
#include "mode_base.h"

//=======================================================================================
// 前方宣言
//=======================================================================================
class CPlayer;
class CCpu;
class CAudience;
class CJudgeFlip;
class CScene2D;

//=======================================================================================
// ゲームクラス
//=======================================================================================
class CGame : public CModeBase
{
public:
    CGame();        // コンストラクタ
    ~CGame();       // デストラクタ

    HRESULT Init();     // 初期化処理
    void Uninit();      // 終了処理
    void Update();      // 更新処理
    void Draw();        // 描画処理

    CPlayer* GetPlayer()const   { return m_pPlayer; }
    CCpu* GetCpu()const         { return m_pCpu; }
    CJudgeFlip* GetFlip()const  { return m_pFlip; }
private:
    // private関数
    void CreatePlayer();    // プレイヤーの生成関数

    // メンバ変数
    CPlayer *m_pPlayer; // プレイヤーのポインタ
    CCpu* m_pCpu;       // CPU
    CAudience* m_pAudience;  // 観客
    CJudgeFlip * m_pFlip;    // フリップ
    vector<CScene2D*> m_pObject2D;    // 2Dオブジェクト
};
#endif