//=============================================================================
// テスト[test_character.cpp]
// Author : Konishi Yuuto
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "test_character.h"
#include "manager.h"
#include "keyboard.h"
#include "renderer.h"
#include "input.h"
#include "joypad.h"
#include "camera.h"
#include "game.h"
#include "sound.h"
#include "time.h"
#include "fade.h"
#include "texture.h"
#include "resource_manager.h"
#include "motion.h"
#include "game.h"

//=============================================================================
// マクロ定義
// Author : Konishi Yuuto
//=============================================================================
#define PLAYER_SPEED            (10.0f)                                 // プレイヤーの移動量
#define PLAYER_ROT_SPEED        (0.1f)                                  // キャラクターの回転する速度
#define SIZE                    (D3DXVECTOR3(1200.0f,1000.0f,1200.0f))  // サイズ

//=============================================================================
// 生成処理関数
// Author : Konishi Yuuto
//=============================================================================
CTestCharacter *CTestCharacter::Create(const D3DXVECTOR3 &pos)
{
    CTestCharacter *pPlayer = new CTestCharacter;

    // !nullcheck
    if (pPlayer)
    {
        // 初期化処理
        pPlayer->SetCharacterInfo(pos, ZeroVector3);
        pPlayer->Init();

        return pPlayer;
    }

    return nullptr;
}

//=============================================================================
// コンストラクタ
// Author : Konishi Yuuto
//=============================================================================
CTestCharacter::CTestCharacter(PRIORITY Priority) : CCharacter(Priority)
{
    m_rotDest = ZeroVector3;
    m_bMove = false;
}

//=============================================================================
// デストラクタ
// Author : Konishi Yuuto
//=============================================================================
CTestCharacter::~CTestCharacter()
{
}

//=============================================================================
// 初期化処理関数
// Author : Konishi Yuuto
//=============================================================================
HRESULT CTestCharacter::Init()
{
    // CXfile取得
    CXfile *pXfile = CManager::GetInstance()->GetResourceManager()->GetXfileClass();

    // !nullcheck
    if (pXfile)
    {
        ModelCreate(CXfile::HIERARCHY_XFILE_NUM_TEST);  // モデルの生成
        SetShadowRotCalculation();                      // 影の向き
    }

    // 初期化処理
    CCharacter::Init();

    // 初期化
    m_rotDest = GetRot();   // 向き
    SetSize(SIZE);          // サイズ設定
    SetSpeed(PLAYER_SPEED); // スピード設定

    return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Konishi Yuuto
//=============================================================================
void CTestCharacter::Uninit()
{
    CCharacter::Uninit();
}

//=============================================================================
// 更新関数処理関数
// Author : Konishi Yuuto
//=============================================================================
void CTestCharacter::Update()
{

}

//=============================================================================
// 描画処理関数
// Author : Konishi Yuuto
//=============================================================================
void CTestCharacter::Draw()
{
    // 描画
    CCharacter::Draw();
}

//=============================================================================
// 状態更新
// Author : Konishi Yuuto
//=============================================================================
void CTestCharacter::UpdateState()
{

}