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
#include "character.h"
#include "state_object.h"

//=========================================================================
// 前方宣言
//=========================================================================
class CState;
class CDummyModel;

//=============================================================================
// プレイヤークラス
//=============================================================================
class CPlayer : public CCharacter, public CStateObject
{
public:
    enum ACTION_STATE
    {
        ACTION_NONE = -1,
        ACTION_IDOL,
        ACTION_MAX
    };//行動状態

    enum STATE_PLAYER
    {
        STATE_PLAYER_NONE = -1,     // 初期値
        STATE_PLAYER_IDOL,          // 通常状態
        STATE_PLAYER_MAX,           // 最大値
    };

    CPlayer(PRIORITY Priority = PRIORITY_CHARACTER);    // コンストラクタ
    ~CPlayer();                                         // デストラクタ

    static CPlayer*Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);    // クリエイト

    HRESULT Init();                                 // 初期化処理
    void Uninit();                                  // 終了処理
    void Update();                                  // 更新処理
    void Draw();                                    // 描画処理
    void ChangeState(CState* pPlayerState);         // 状態チェンジ

    // Set関数
    void SetMove(const D3DXVECTOR3 &move)       { CCharacter::SetMove(move); }  // 移動量設定
    void SetRotDest(const D3DXVECTOR3& rotDest) { m_rotDest = rotDest; }        // 目的の角度
    void SetAngle(const float& fAngle)          { m_fAngle = fAngle; }          // アングル

    // Get関数
    int GetLife()const              { return m_nHP; }           // HPの情報
    float GetAngle()const           { return m_fAngle; }        // アングル
    D3DXVECTOR3 GetRotDest()const   { return m_rotDest; }       // 目的
    D3DXVECTOR3 GetInertia()const   { return m_Inertia; }       // 慣性の情報
    float GetInertiaNum()const      { return m_fInertiaNum; }   // 慣性の値

private:
    // private関数
    void UpdateState(); // プレイヤーの状態
    void UpdateRot();   // 角度の更新処理

    // メンバ変数
    D3DXVECTOR3 m_rotDest;      // 回転(目標値)
    D3DXVECTOR3 m_Inertia;      // 慣性
    float m_fInertiaNum;        // 慣性の値
    float m_fRotationSpeed;     // 回転の速度
    bool m_bMove;               // 移動のフラグ
    int m_nHP;                  // スライムHP ~100まで（パーセント）
    float m_fAngle;             // カメラ向きアングル
    float m_fAngleSpeed;        // 目標向きまで向かうスピード
    ACTION_STATE m_ActionState; // 行動状態
    CState* m_pCurrentState;    // 現在の状態ポインタ
    CState* m_pNextState;       // 次の状態ポインタ
    CDummyModel* m_pModel;
};
#endif