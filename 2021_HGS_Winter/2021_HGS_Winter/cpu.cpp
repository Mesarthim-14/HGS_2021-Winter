//=============================================================================
//
// CPUクラス [cpu.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "cpu.h"
#include "manager.h"
#include "renderer.h"
#include "resource_manager.h"
#include "library.h"
#include "scene2d.h"
#include "texture.h"
#include "game.h"
#include "player.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define POS         (D3DXVECTOR3(SCREEN_WIDTH/2 + 200.0f, SCREEN_HEIGHT/2, 0.0f))   // 座標
#define SIZE        (D3DXVECTOR3(450.0f, 450.0f, 0.0f))                             // サイズ
#define INTERVAL    (200)                                                           // 間隔

//=============================================================================
// コンストラクタ
//=============================================================================
CCpu::CCpu(PRIORITY Priority) : CJudge(Priority)
{
    m_nCounter = 0;
    m_bJudge = false;
    m_Correct = CORRECT_TYPE_NONE;
}

//=============================================================================
// デストラクタ
//=============================================================================
CCpu::~CCpu()
{

}

//=============================================================================
// インスタンス生成
//=============================================================================
CCpu * CCpu::Create()
{
    // メモリ確保
    CCpu *pTestModel = new CCpu(PRIORITY_1);

    // !nullcheck
    if (pTestModel)
    {
        // 初期化処理
        pTestModel->Init();

        return pTestModel;
    }

    return nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCpu::Init()
{

    return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CCpu::Uninit()
{
    Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CCpu::Update()
{
    if (m_nCounter >= INTERVAL - 15)
    {
        CScene2D* pScene = GetScene();
        if (pScene)
        {
            pScene->ScaleUp(-0.02f);
        }
    }

    if (CLibrary::CounterLimit(INTERVAL, m_nCounter))
    {
        SelectJudge();
    }
}

//=============================================================================
// 描画処理
//=============================================================================
void CCpu::Draw()
{

}

//=============================================================================
// 手を選ぶ
//=============================================================================
void CCpu::SelectJudge()
{
    if (!m_bJudge)
    {
        CPlayer* pPlayer = CManager::GetInstance()->GetGame()->GetPlayer();
        if (pPlayer)
        {
            pPlayer->EndCombo();
        }
    }
    m_nCounter = 0;

    HAND_TYPE nHand = (HAND_TYPE)CLibrary::Random(0, 2);    // 出し手
    m_Correct = (CORRECT_TYPE)CLibrary::Random(0, 0);       // 正解の手
    CScene2D* pScene2D = CScene2D::Create(POS, SIZE);
    CTexture* pTexture = GET_TEXTURE_PTR;
    switch (nHand)
    {
        // グー
    case HAND_TYPE_GU:
        pScene2D->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_CPU_GU));
        break;
    case HAND_TYPE_CHOKI:
        pScene2D->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_CPU_CHOKI));
        break;
    case HAND_TYPE_PA:
        pScene2D->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_CPU_PA));
        break;
    default:
        break;
    }

    BindScene2D(pScene2D);
    SetHand(nHand);

    m_bJudge = false;
}
