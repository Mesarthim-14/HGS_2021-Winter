//=============================================================================
//
// CPU�N���X [cpu.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
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
// �}�N����`
//=============================================================================
#define POS         (D3DXVECTOR3(SCREEN_WIDTH/2 + 200.0f, SCREEN_HEIGHT/2, 0.0f))   // ���W
#define SIZE        (D3DXVECTOR3(450.0f, 450.0f, 0.0f))                             // �T�C�Y
#define INTERVAL    (200)                                                           // �Ԋu

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCpu::CCpu(PRIORITY Priority) : CJudge(Priority)
{
    m_nCounter = 0;
    m_bJudge = false;
    m_Correct = CORRECT_TYPE_NONE;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCpu::~CCpu()
{

}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CCpu * CCpu::Create()
{
    // �������m��
    CCpu *pTestModel = new CCpu(PRIORITY_1);

    // !nullcheck
    if (pTestModel)
    {
        // ����������
        pTestModel->Init();

        return pTestModel;
    }

    return nullptr;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCpu::Init()
{

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CCpu::Uninit()
{
    Release();
}

//=============================================================================
// �X�V����
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
// �`�揈��
//=============================================================================
void CCpu::Draw()
{

}

//=============================================================================
// ���I��
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

    HAND_TYPE nHand = (HAND_TYPE)CLibrary::Random(0, 2);    // �o����
    m_Correct = (CORRECT_TYPE)CLibrary::Random(0, 0);       // �����̎�
    CScene2D* pScene2D = CScene2D::Create(POS, SIZE);
    CTexture* pTexture = GET_TEXTURE_PTR;
    switch (nHand)
    {
        // �O�[
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
