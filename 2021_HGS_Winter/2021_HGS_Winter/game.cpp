//=======================================================================================
//
// ゲーム処理 [game.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// インクルード
//=======================================================================================
#include "game.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "joypad.h"
#include "sound.h"
#include "keyboard.h"
#include "resource_manager.h"
#include "fade.h"
#include "test_2d.h"
#include "test_model.h"
#include "test_character.h"
#include "library.h"
#include "camera_game.h"
#include "state_player_normal.h"
#include "meshfield.h"
#include "ground.h"
#include "cpu.h"
#include "confetti_factory.h"
#include "audience.h"
#include "girle.h"
#include "judge_flip.h"
#include "gauge.h"
#include "present_box.h"
#include "texture.h"
#include "scene2d.h"

//=======================================================================================
// コンストラクタ
//=======================================================================================
CGame::CGame()
{
    m_pPlayer = nullptr;
    m_pCpu = nullptr;

    m_pGirle = nullptr;
}

//=======================================================================================
// デストラクタ
//=======================================================================================
CGame::~CGame()
{
    // 終了処理
    Uninit();
}

//=======================================================================================
// 初期化処理
//=======================================================================================
HRESULT CGame::Init()
{
    // タイトルテクスチャの生成
    CScene2D* pScene2D = CScene2D::Create(HALF_SCREEN_POS, SCREEN_SIZE);
    pScene2D->BindTexture(GET_TEXTURE_PTR->GetTexture(CTexture::TEXTURE_NUM_GAME));
    m_pObject2D.push_back(pScene2D);

    if (!m_pCpu)
    {
        m_pCpu = CCpu::Create();
    }

    CreatePlayer();

    // 観客の生成
    m_pAudience = CAudience::Create();

    m_pFlip = CJudgeFlip::Create();

    m_pGirle = CGirle::Create();

    CPresentBox::Create();
    return S_OK;
}

//=======================================================================================
// 終了処理
//=======================================================================================
void CGame::Uninit()
{
    if (m_pCpu)
    {
        m_pCpu->Uninit();
        m_pCpu = nullptr;
    }
    
    // プレイヤーの終了処理
    if (m_pPlayer)
    {
        m_pPlayer->Uninit();
        m_pPlayer = nullptr;
    }

    // プレイヤーの終了処理
    if (m_pGirle)
    {
        m_pGirle->Uninit();
        m_pGirle = nullptr;
    }
}

//=======================================================================================
// 更新処理
//=======================================================================================
void CGame::Update()
{
    m_pAudience->SetStep(m_pPlayer->GetCombo());
#ifdef _DEBUG
    CInputKeyboard* pKey = CManager::GetInstance()->GetKeyboard();
    CFade::FADE_MODE mode = CManager::GetInstance()->GetFade()->GetFade();

    // タイトルに戻る
    if (pKey->GetTrigger(DIK_TAB) && mode == CFade::FADE_MODE_NONE)
    {
        CFade *pFade = CManager::GetInstance()->GetFade();
        pFade->SetFade(CManager::MODE_TYPE_TITLE);
    }

    if (pKey->GetTrigger(DIK_RETURN) && mode == CFade::FADE_MODE_NONE)
    {
        CFade *pFade = CManager::GetInstance()->GetFade();
        pFade->SetFade(CManager::MODE_TYPE_RESULT);
    }

    //  紙吹雪出す
    if (pKey->GetTrigger(DIK_Z))
    {
        m_pAudience->SetUpFrag(true);
        CConfettiFactory::Create(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f),20);
        CConfettiFactory::Create(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f),20);
    }
    if (pKey->GetTrigger(DIK_B))
    {
        CRenderer* pRenderer = CManager::GetInstance()->GetRenderer();
        if (pRenderer->GetShockBlur())
        {
            pRenderer->SetShockBlur(false, 0.0f);
        }
        else
        {
            pRenderer->SetShockBlur(true, 10.0f);
        }
    }

    if (pKey->GetTrigger(DIK_LEFT))
    {
        m_pFlip->SetFlip(CJudgeFlip::STATE_WIN);
    }
    if (pKey->GetTrigger(DIK_RIGHT))
    {
        m_pFlip->SetFlip(CJudgeFlip::STATE_LOSE);
    }
    

#endif // !_DEBUG
}

//=======================================================================================
// 描画処理
//=======================================================================================
void CGame::Draw()
{
}

//=======================================================================================
// プレイヤーの生成
//=======================================================================================
void CGame::CreatePlayer()
{
    // プレイヤーの生成
    if (!m_pPlayer)
    {
        m_pPlayer = CPlayer::Create();
    }
}