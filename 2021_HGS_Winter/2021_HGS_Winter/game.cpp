//=======================================================================================
//
// �Q�[������ [game.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// �C���N���[�h
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
// �R���X�g���N�^
//=======================================================================================
CGame::CGame()
{
    m_pPlayer = nullptr;
    m_pCpu = nullptr;

    m_pGirle = nullptr;
}

//=======================================================================================
// �f�X�g���N�^
//=======================================================================================
CGame::~CGame()
{
    // �I������
    Uninit();
}

//=======================================================================================
// ����������
//=======================================================================================
HRESULT CGame::Init()
{
    // �^�C�g���e�N�X�`���̐���
    CScene2D* pScene2D = CScene2D::Create(HALF_SCREEN_POS, SCREEN_SIZE);
    pScene2D->BindTexture(GET_TEXTURE_PTR->GetTexture(CTexture::TEXTURE_NUM_GAME));
    m_pObject2D.push_back(pScene2D);

    if (!m_pCpu)
    {
        m_pCpu = CCpu::Create();
    }

    CreatePlayer();

    // �ϋq�̐���
    m_pAudience = CAudience::Create();

    m_pFlip = CJudgeFlip::Create();

    m_pGirle = CGirle::Create();

    CPresentBox::Create();
    return S_OK;
}

//=======================================================================================
// �I������
//=======================================================================================
void CGame::Uninit()
{
    if (m_pCpu)
    {
        m_pCpu->Uninit();
        m_pCpu = nullptr;
    }
    
    // �v���C���[�̏I������
    if (m_pPlayer)
    {
        m_pPlayer->Uninit();
        m_pPlayer = nullptr;
    }

    // �v���C���[�̏I������
    if (m_pGirle)
    {
        m_pGirle->Uninit();
        m_pGirle = nullptr;
    }
}

//=======================================================================================
// �X�V����
//=======================================================================================
void CGame::Update()
{
    m_pAudience->SetStep(m_pPlayer->GetCombo());
#ifdef _DEBUG
    CInputKeyboard* pKey = CManager::GetInstance()->GetKeyboard();
    CFade::FADE_MODE mode = CManager::GetInstance()->GetFade()->GetFade();

    // �^�C�g���ɖ߂�
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

    //  ������o��
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
// �`�揈��
//=======================================================================================
void CGame::Draw()
{
}

//=======================================================================================
// �v���C���[�̐���
//=======================================================================================
void CGame::CreatePlayer()
{
    // �v���C���[�̐���
    if (!m_pPlayer)
    {
        m_pPlayer = CPlayer::Create();
    }
}