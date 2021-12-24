//=============================================================================
//
// ���U���g�N���X [result.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "result.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "scene2d.h"
#include "fade.h"
#include "keyboard.h"
#include "texture.h"
#include "sound.h"
#include "joypad.h"
#include "resource_manager.h"
#include "player.h"
#include "number_2d.h"
#include "game.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CResult::CResult()
{
    m_pObject2D.clear();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CResult::~CResult()
{
    // �I������
    Uninit();
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CResult::Init()
{
    if (CManager::GetInstance()->CManager::GetResourceManager())
    {
        CSound* pSound = CManager::GetInstance()->CManager::GetResourceManager()->GetSoundClass();
        pSound->Stop(CSound::SOUND_SE_BYE);
    }

    // �^�C�g���e�N�X�`���̐���
    CScene2D* pScene2D = CScene2D::Create(HALF_SCREEN_POS, SCREEN_SIZE);
    pScene2D->BindTexture(GET_TEXTURE_PTR->GetTexture(CTexture::TEXTURE_NUM_RESULT));
    m_pObject2D.push_back(pScene2D);

    // �R���{��
    int nComboDigit = 0;
    int nConboNum = CManager::GetInstance()->GetResultScore();

    // ���������߂�
    while (nConboNum != 0)
    {
        nConboNum /= 10;
        nComboDigit++;
    }

    int nScore = CManager::GetInstance()->GetResultScore();

    // �X�R�A�̐���
    for (int nCount = 0; nCount < nComboDigit; nCount++)
    {
        // �X�R�A�̐���
        CNumber2d *pNumber2d = CNumber2d::Create(D3DXVECTOR3(400.0f - nCount * 80.0f, 360.0f, 0.0f), D3DXVECTOR3(105.0f, 105.0f, 0.0f));	// ���W�A�T�C�Y

        // !nullcheck
        if (pNumber2d)
        {
            // �e�N�X�`���̃|�C���^
            CTexture *pTexture = GET_TEXTURE_PTR;
            // �e�N�X�`���̐ݒ�
            pNumber2d->BindTexture(
                pTexture->GetTexture(CTexture::TEXTURE_NUM_NUMBER));	// �e�N�X�`���̐ݒ�

            if (nCount == 0)
            {
                // �����̐ݒ�
                pNumber2d->SetNumber(nScore);
            }
            else
            {
                // �����̐ݒ�
                pNumber2d->SetNumber(nScore / (nCount * 10));
            }
        }
    }

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CResult::Uninit()
{
    for (auto &object : m_pObject2D)
    {
        // �I������
        object->Uninit();
    }

    // �I�u�W�F�N�g�폜
    m_pObject2D.clear();
}

//=============================================================================
// �X�V����
//=============================================================================
void CResult::Update()
{

    CInputKeyboard* pKey = CManager::GetInstance()->GetKeyboard();
    CFade::FADE_MODE mode = CManager::GetInstance()->GetFade()->GetFade();

    // �R���g���[����start���������Ƃ����A�G���^�[�L�[���������Ƃ�
    if (CManager::GetInstance()->GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_START, 0) && mode == CFade::FADE_MODE_NONE
        || pKey->GetTrigger(DIK_RETURN) && mode == CFade::FADE_MODE_NONE)
    {
        CFade *pFade = CManager::GetInstance()->GetFade();
        pFade->SetFade(CManager::MODE_TYPE_TITLE);
    }
}

//=============================================================================
// �`�揈��
//=============================================================================
void CResult::Draw()
{

}