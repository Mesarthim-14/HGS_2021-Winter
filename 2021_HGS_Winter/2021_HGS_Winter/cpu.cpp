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
#include "judge_flip.h"
#include "gauge.h"
#include "girle.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define POS         (D3DXVECTOR3(SCREEN_WIDTH / 2 + 600.0f, SCREEN_HEIGHT / 2+50.0f, 0.0f))   // 座標
#define SIZE        (D3DXVECTOR3(900.0f, 700.0f, 0.0f))
#define INTERVAL    (180)                                                           // 間隔

//=============================================================================
// コンストラクタ
//=============================================================================
CCpu::CCpu(PRIORITY Priority) : CJudge(Priority)
{
    m_nCounter = 0;
    m_bJudge = true;
    m_Correct = CORRECT_TYPE_NONE;
    m_nInterval = INTERVAL;
    m_nSubInter = 0;
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
    if (!CManager::GetInstance()->GetGame()->GetPlayer()->GetEnd())
    {
        if (m_nCounter >= m_nInterval - 15)
        {
            CScene2D* pScene = GetScene();
            if (pScene)
            {
                // スケール
                pScene->ScaleUp(-0.02f);
            }
        }

        // 判定
        if (CLibrary::CounterLimit(m_nInterval, m_nCounter))
        {
            SelectJudge();
        }
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
    CPlayer* pPlayer = CManager::GetInstance()->GetGame()->GetPlayer();

    if (!m_bJudge)
    {
        if (pPlayer)
        {
            // コンボ終了
            //pPlayer->EndCombo();
            pPlayer->End();
            return;
        }
    }

    m_nCounter = 0;

    HAND_TYPE nHand = (HAND_TYPE)CLibrary::Random(0, 2);    // 出し手
    m_Correct = (CORRECT_TYPE)CLibrary::Random(0, 2);       // 正解の手
    CScene2D* pScene2D = CScene2D::Create(POS, SIZE);
    CTexture* pTexture = GET_TEXTURE_PTR;
    CJudgeFlip* pFlip = CManager::GetInstance()->GetGame()->GetFlip();
    if (pFlip)
    {
        switch (m_Correct)
        {
        case CORRECT_TYPE_WIN:
            pFlip->SetFlip((CJudgeFlip::JUDGE_FLIP_STATE)CORRECT_TYPE_WIN);
            break;
        case CORRECT_TYPE_DRAW:
            pFlip->SetFlip((CJudgeFlip::JUDGE_FLIP_STATE)CORRECT_TYPE_DRAW);
            break;
        case CORRECT_TYPE_LOSE:
            pFlip->SetFlip((CJudgeFlip::JUDGE_FLIP_STATE)CORRECT_TYPE_LOSE);
            break;
        default:
            break;
        }
        CGauge::Create(m_nInterval);
        CManager::GetInstance()->GetGame()->GetGirle()->SetAnim(CGirle::STATE_UP);
    }
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
    SubInter(pPlayer);

    BindScene2D(pScene2D);
    SetHand(nHand);

    m_bJudge = false;
}

//=============================================================================
// 間隔の減算
//=============================================================================
void CCpu::SubInter(CPlayer* &pPlayer)
{
    switch (pPlayer->GetCombo())
    {
    case 5:
        m_nInterval -= 15;
        break;

    case 10:
        m_nInterval -= 15;
        break;

    case 15:
        m_nInterval -= 15;
        break;
    case 25:
        m_nInterval -= 15;
        break;
    case 35:
        m_nInterval -= 15;
        break;
    case 45:
        m_nInterval -= 15;
        break;
    case 60:
        m_nInterval -= 15;
        break;
    case 65:
        m_nInterval -= 15;
        break;
    case 80:
        m_nInterval -= 15;
        break;
    case 100:
        m_nInterval -= 15;
        break;

    default:
        break;
    }

}
