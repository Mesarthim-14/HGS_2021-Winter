//=============================================================================
// プレイヤークラス [player.cpp]
// Author : Konishi Yuuto
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "player.h"
#include "manager.h"
#include "keyboard.h"
#include "renderer.h"
#include "resource_manager.h"
#include "library.h"
#include "game.h"
#include "scene2d.h"
#include "texture.h"
#include "cpu.h"
#include "number_2d.h"
#include "joypad.h"
#include "audience.h"
#include "confetti_factory.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TEX_POS     (D3DXVECTOR3(SCREEN_WIDTH / 2 - 500.0f, SCREEN_HEIGHT / 2, 0.0f))
#define TEX_SIZE    (D3DXVECTOR3(700.0f, 500.0f, 0.0f))

#define COMBO_NUMBER_INTERVAL	(80.0f)														// コンボ数の間隔

// コンボ数UIの情報
#define COMBO_NUMBER_POS_X  (1100.0f)											// コンボ数の座標
#define COMBO_NUMBER_POS_Y	(150.0f)											// コンボ数の座標
#define COMBO_NUMBER_POS	(D3DXVECTOR3(COMBO_NUMBER_POS_X, COMBO_NUMBER_POS_Y, 0.0f))

#define COMBO_NUMBER_SIZE_X (105.0f)															// コンボ数の座標
#define COMBO_NUMBER_SIZE_Y	(105.0f)															// コンボ数の座標
#define COMBO_NUMBER_SIZE	(D3DXVECTOR3(COMBO_NUMBER_SIZE_X, COMBO_NUMBER_SIZE_Y, 0.0f))

//=============================================================================
// コンストラクタ
// Author : Konishi Yuuto
//=============================================================================
CPlayer::CPlayer(PRIORITY Priority) : CJudge(Priority)
{
    m_Correct = HAND_TYPE_NONE;    // 勝ち
    m_nCombo = 0;
    m_apCombo.clear();
    m_bCombo = false;
}

//=============================================================================
// デストラクタ
// Author : Konishi Yuuto
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// 生成処理関数
// Author : Konishi Yuuto
//=============================================================================
CPlayer * CPlayer::Create()
{
    // メモリ確保
    CPlayer *pPlayer = new CPlayer;

    // nullcheck
    if (pPlayer)
    {
        // 初期化処理
        pPlayer->Init();
        return pPlayer;
    }

    // CPlayerを返す
    return nullptr;
}

//=============================================================================
// 初期化処理関数
// Author : Konishi Yuuto
//=============================================================================
HRESULT CPlayer::Init()
{
	// 初期化処理
	CJudge::Init();

	return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::Uninit()
{
    if (m_apCombo.size() != 0)
    {
        // ナンバーの終了処理
        for (auto& pCombo : m_apCombo)
        {
            pCombo->Uninit();
            pCombo = nullptr;
        }
        m_apCombo.clear();
    }

    // 自身の終了処理
    CJudge::Uninit();
}

//=============================================================================
// 更新関数処理関数
//=============================================================================
void CPlayer::Update()
{
    SetHand(HAND_TYPE_NONE);

    CCpu* pCpu = CManager::GetInstance()->GetGame()->GetCpu();
    if (pCpu)
    {
        // ジャッジフラグが無ければ
        if (!pCpu->GetJudge())
        {
            SelectHand();
            Judge();
        }
    }
}

//=============================================================================
// 手を選ぶ
//=============================================================================
void CPlayer::SelectHand()
{
    CCpu* pCpu = CManager::GetInstance()->GetGame()->GetCpu();
    if (!pCpu)
    {
        return;
    }
    
    CInputJoypad* pPad = CManager::GetInstance()->GetJoypad();
    // グー
    if (CLibrary::KeyboardTrigger(DIK_1) || pPad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_X, 0))
    {
        CScene2D* pScene2D = CScene2D::Create(TEX_POS, TEX_SIZE);
        CTexture* pTexture = GET_TEXTURE_PTR;
        pScene2D->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_GU));
        SetHand(HAND_TYPE_GU);
        BindScene2D(pScene2D);

        // 正解の手を決める
        switch (pCpu->GetCorrect())
        {
        case CORRECT_TYPE_WIN:
            m_Correct = HAND_TYPE_CHOKI;    // 勝てる
            break;
        case CORRECT_TYPE_DRAW:
            m_Correct = HAND_TYPE_GU;       // 引き分け
            break;
        case CORRECT_TYPE_LOSE:
            m_Correct = HAND_TYPE_PA;       // 負ける
            break;
        default:
            break;
        }
    }

    else if (CLibrary::KeyboardTrigger(DIK_2) || pPad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_Y, 0) )
    {
        CScene2D* pScene2D = CScene2D::Create(TEX_POS, TEX_SIZE);
        CTexture* pTexture = GET_TEXTURE_PTR;
        pScene2D->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_CHOKI));
        SetHand(HAND_TYPE_CHOKI);
        BindScene2D(pScene2D);

        // 正解の手を決める
        switch (pCpu->GetCorrect())
        {
        case CORRECT_TYPE_WIN:
            m_Correct = HAND_TYPE_PA;       // 勝てる
            break;
        case CORRECT_TYPE_DRAW:
            m_Correct = HAND_TYPE_CHOKI;    // 引き分け
            break;
        case CORRECT_TYPE_LOSE:
            m_Correct = HAND_TYPE_GU;       // 負ける
            break;
        default:
            break;
        }
    }
    else if (CLibrary::KeyboardTrigger(DIK_3) || pPad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_B, 0))
    {
        CScene2D* pScene2D = CScene2D::Create(TEX_POS, TEX_SIZE);
        CTexture* pTexture = GET_TEXTURE_PTR;
        pScene2D->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_PA));
        SetHand(HAND_TYPE_PA);
        BindScene2D(pScene2D);

        // 正解の手を決める
        switch (pCpu->GetCorrect())
        {
        case CORRECT_TYPE_WIN:
            m_Correct = HAND_TYPE_GU;       // 勝てる
            break;
        case CORRECT_TYPE_DRAW:
            m_Correct = HAND_TYPE_PA;       // 引き分け
            break;
        case CORRECT_TYPE_LOSE:
            m_Correct = HAND_TYPE_CHOKI;    // 負ける
            break;
        default:
            break;
        }
    }
}

//=============================================================================
// 勝ち負け判定
//=============================================================================
void CPlayer::Judge()
{
    if (GetHand() != HAND_TYPE_NONE)
    {
        CCpu* pCpu = CManager::GetInstance()->GetGame()->GetCpu();
        if (pCpu)
        {
            // 敵の手
            HAND_TYPE nCpuHand = pCpu->GetHand();   // 相手
            HAND_TYPE nHand = GetHand();            // 自分

            // グーの時
            if (nCpuHand == m_Correct)
            {
                // コンボの判定
                if (m_nCombo == 0)
                {
                    CreateCombo();
                }
                else
                {
                    AddCombo();

                }

                CreateEffect();


            }
            else
            {
                // 間違えコンボ終了
                EndCombo();
            }
        }

        // ジャッジ
        pCpu->SetJudge(true);
        m_Correct = HAND_TYPE_NONE;
    }
}

//=============================================================================
// コンボの加算
//=============================================================================
void CPlayer::AddCombo()
{
    m_nCombo++;

    int nDigit = 0;
    int nNumber = m_nCombo;

    // 桁数を求める
    while (nNumber != 0)
    {
        nNumber /= 10;
        nDigit++;
    }

    //　桁が増えたら
    if (m_nCombo == 10 || m_nCombo == 100 || m_nCombo == 1000)
    {
        // メモリの確保
        CNumber2d *pNumber2d = CNumber2d::Create(D3DXVECTOR3(
            COMBO_NUMBER_POS_X - (nDigit - 1) *COMBO_NUMBER_INTERVAL, COMBO_NUMBER_POS_Y, 0.0f), COMBO_NUMBER_SIZE);	// 座標、サイズ

        if (pNumber2d)
        {
            CTexture* pTexture = GET_TEXTURE_PTR;
            pNumber2d->BindTexture(
                pTexture->GetTexture(CTexture::TEXTURE_NUM_NUMBER));	// テクスチャの設定

            // 数字の設定
            pNumber2d->SetNumber(0);
        }

        // ポインタ取得
        m_apCombo.push_back(pNumber2d);
    }

    for (int nCount = 0; nCount < nDigit; nCount++)
    {
        // 桁の値を出す
        int nNum = (m_nCombo / (int)(pow(10, nCount))) % 10;

        // !nullcheck
        if (m_apCombo.at(nCount) != nullptr)
        {
            // 数字の設定
            m_apCombo.at(nCount)->SetNumber(nNum);
        }
    }

}

//=============================================================================
// コンボUi生成
//=============================================================================
void CPlayer::CreateCombo()
{	
    m_nCombo++;

    // コンボ数
    int nComboDigit = 0;
    int nConboNum = m_nCombo;

    // 桁数を求める
    while (nConboNum != 0)
    {
        nConboNum /= 10;
        nComboDigit++;
    }

    // コンボ数の処理
    for (int nCount = 0; nCount < nComboDigit; nCount++)
    {
        // メモリの確保
        CNumber2d *pNumber2d = CNumber2d::Create(D3DXVECTOR3(
            COMBO_NUMBER_POS_X - nCount*COMBO_NUMBER_INTERVAL, COMBO_NUMBER_POS_Y, 0.0f), COMBO_NUMBER_SIZE);

        // !nullcheck
        if (pNumber2d)
        {
            // テクスチャのポインタ
            CTexture *pTexture = GET_TEXTURE_PTR;
            // テクスチャの設定
            pNumber2d->BindTexture(
                pTexture->GetTexture(CTexture::TEXTURE_NUM_NUMBER));	// テクスチャの設定

            // 数字の設定
            pNumber2d->SetNumber(m_nCombo);

            // コンボ数
            m_apCombo.push_back(pNumber2d);
        }
    }

}

//=============================================================================
// コンボの終了
//=============================================================================
void CPlayer::EndCombo()
{	
    if (m_apCombo.size() != 0)
    {
        for (auto& pCombo : m_apCombo)
        {
            pCombo->Uninit();
            pCombo = nullptr;
        }
    }

    m_apCombo.clear();
    m_nCombo = 0;
}

//=============================================================================
// エフェクトの生成
//=============================================================================
void CPlayer::CreateEffect()
{
    if (m_nCombo == 10)
    {
        CAudience* pAudience = CManager::GetInstance()->GetGame()->GetAudience();
        pAudience->SetDrawFlag();
    }

    if (m_nCombo >= 20)
    {
        CRenderer* pRenderer = CManager::GetInstance()->GetRenderer();
        pRenderer->SetShockBlur(true, 20.0f);
    }
    if (m_nCombo >= 30)
    {
        CConfettiFactory::Create(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), 20);
        CConfettiFactory::Create(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 20);
    }
    if (m_nCombo >= 40)
    {
        CConfettiFactory::Create(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), 20);
        CConfettiFactory::Create(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 20);
    }
}
