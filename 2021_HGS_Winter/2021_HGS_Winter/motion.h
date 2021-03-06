#ifndef _MOTION_H_
#define _MOTION_H_
//=============================================================================
//
// モーションクラスヘッダー [motion.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "xfile.h"
#include "modelanime.h"

//=============================================================================
// モーションクラス
//=============================================================================
class CMotion
{
public:
    CMotion();        // コンストラクタ
    ~CMotion();        // デストラクタ

    static CMotion *Create(const string &cFileName);

    void SetMotion(const int &nMotion, const int &nMaxParts, const vector<CModelAnime*> pModelAnime);   // モーションの設定
    void UpdateMotion(const int &nMaxParts, const vector<CModelAnime*> pModelAnime);                    // モーションの更新

    // Get関数
    int GetMotionState()    { return m_nMotionState; }   // モーション状態
    int GetKey()            { return m_nKey; }           // キーの情報
    int GetCountMotion()    { return m_nCountMotion; }   // モーションのカウント

private:
    // 各要素のキー情報
    struct KEY
    {
        float fPosX;
        float fPosY;
        float fPosZ;
        float fRotX;
        float fRotY;
        float fRotZ;
    };

    //    キー情報の構造体
    struct KEY_INFO
    {
        int nFrame;         // フレーム数
        vector<KEY> aKey;   // 各パーツのキー情報
    };

    // モーション情報の構造体
    struct Motion_Info
    {
        bool bLoop;                 // ループするかどうか
        int nNumKey;                // キー数
        vector<KEY_INFO> aKeyInfo;  // キー情報
    };

    // private関数
    HRESULT ReadMotionFile(const string &cFileName);    // モーションデータを読み込む

    // モーション用変数
    vector<Motion_Info> m_Motion;   // モーション情報
    KEY_INFO *m_apKeyInfo;          // キー情報のポインタ
    int m_nMotionState;             // モーションの状態
    int m_nNumKey;                  // キーの総数
    int m_nCountMotion;             // モーションカウンター
    int m_nMotionInterval;          // モーションのインターバル
    int m_nKey;                     // 現在キーのNo
    bool m_bMotionPlaing;           // モーションの再生
    D3DXVECTOR3 m_diffPos;          // 変更座標
    D3DXVECTOR3 m_diffRot;          // 変更角度
};

#endif 