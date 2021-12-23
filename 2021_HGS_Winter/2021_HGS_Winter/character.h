#ifndef _CHARACTER_H_
#define _CHARACTER_H_
//=============================================================================
//
// キャラクタークラスヘッダ  [character.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//インクルード
//=============================================================================
#include "main.h"
#include "scene.h"
#include "modelanime.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CMotion;

//=============================================================================
// キャラクターのクラス
//=============================================================================
class CCharacter : public CScene
{
public:
    //=============================================================================
    // キャラクターの状態
    //=============================================================================
    enum STATE
    {
        STATE_NORMAL = 0,
        STATE_MAX
    };

    //=============================================================================
    // キャラクターの種類
    //=============================================================================
    enum CHARACTER_TYPE
    {
        CHARACTER_TYPE_NONE = -1,    // 初期値
        CHARACTER_TYPE_PLAYER,        // プレイヤー
        CHARACTER_TYPE_MAX            // 最大値
    };

    CCharacter(PRIORITY Priority = PRIORITY_CHARACTER); // コンストラクタ
    virtual ~CCharacter();                              // デストラクタ

    virtual HRESULT Init();             // 初期化処理
    virtual void Uninit();              // 終了処理
    virtual void Update();              // 更新処理
    virtual void Draw();                // 描画処理
    void Landing(const float &fHeight); // 着地
    void Fall();                        // 落下

    // Get関数
    D3DXVECTOR3 GetPos()const                            { return m_pos; }                       // 現在の座標情報
    D3DXVECTOR3 GetOldPos()const                         { return m_posOld; }                    // 古い座標情報
    D3DXVECTOR3 GetRot()const                            { return m_rot; }                       // 角度情報
    D3DXVECTOR3 GetMove()const                           { return m_move; }                      // 移動量の情報
    D3DXVECTOR3 GetSize()const                           { return m_size; }                      // サイズ取得
    CModelAnime *GetModelAnime(const int &nCount)const   { return m_apModelAnime.at(nCount); }   // モーションのカウント情報
    CMotion *GetMotion()const                            { return m_pMotion; }                   // モーションのポインタ情報
    int GetStateCounter()const                           { return m_nStateCounter; }             // 状態カウンターの情報
    int GetPartsNum()const                               { return m_apModelAnime.size(); }       // パーツ数取得
    float &GetSpeed()                                    { return m_fSpeed; }                    // スピードの情報
    STATE GetState()const                                { return m_State; }                     // 状態取得
    CHARACTER_TYPE GetType() const                       { return m_type; }                      // 種類
    vector<CModelAnime*> GetModelAnimeVec()const         { return m_apModelAnime; }              // ポインタ全ての取得
    D3DXMATRIX GetMtxWorld()const                        { return m_mtxWorld; }                  // マトリクスワールド

    void SetPos(const D3DXVECTOR3 &pos)      { m_pos = pos; }            // 座標の設定
    void SetLanding(const bool &bLanding)    { m_bLanding = bLanding; }  // 着地
    bool GetLanding()                        { return m_bLanding; }      // 着地判定取得

protected:
    void SetCharacterInfo(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);  // キャラクターの基本情報
    void ModelCreate(const CXfile::HIERARCHY_XFILE_NUM &FileNum);           // モデルの生成
    void SetShadowRotCalculation();                                         // 影を回す

    // Set関数
    void SetPosOld(const D3DXVECTOR3 &posOld)    { m_posOld = posOld; }      // 座標の設定
    void SetMove(const D3DXVECTOR3 &move)        { m_move = move; }          // 移動量の設定
    void SetRot(const D3DXVECTOR3 &rot)          { m_rot = rot; }            // 角度の設定
    void SetSize(const D3DXVECTOR3 &size)        { m_size = size; }          // サイズ設定
    void SetSpeed(const float &fSpeed)           { m_fSpeed = fSpeed; }      // 速度の設定
    void SetState(const STATE &state)            { m_State = state; }        // 状態設定
    void SetGravityFlag(const bool &bFlag)       { m_bGravity = bFlag; }     // 重力のフラグ
    void SetType(const CHARACTER_TYPE &type)     { m_type = type; }          // 種類

private:
    // private関数
    void ModelAnimeUpdate();                    // モデルアニメーション
    void Gravity();                             // 重力
    void SetMotion(const int &nMotionState);    // モーションの設定

    // 純粋仮想関数
    virtual void UpdateState() = 0;             // キャラクター状態

    // メンバ変数
    vector<CModelAnime*> m_apModelAnime;    // モデルパーツ用ポインタ
    CMotion *m_pMotion;                     // モーションクラスのポインタ
    D3DXVECTOR3 m_pos;                      // 座標
    D3DXVECTOR3 m_posOld;                   // 古い座標
    D3DXVECTOR3 m_move;                     // 移動量
    D3DXVECTOR3 m_rot;                      // 現在の回転
    D3DXVECTOR3 m_size;                     // サイズ
    D3DXMATRIX m_mtxWorld;                  // ワールドマトリックス
    STATE m_State;                          // 状態
    CHARACTER_TYPE m_type;                  // 種類
    int m_nStateCounter;                    // 状態のカウンター
    int m_nParts;                           // パーツ数
    float m_fSpeed;                         // 移動量
    bool m_bLanding;                        // 着地フラグ
    bool m_bGravity;                        // 重力をかけるフラグ
};
#endif
