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
    // �^�C�g���e�N�X�`���̐���
    CScene2D* pScene2D = CScene2D::Create(HALF_SCREEN_POS, SCREEN_SIZE);
    pScene2D->BindTexture(GET_TEXTURE_PTR->GetTexture(CTexture::TEXTURE_NUM_RESULT));
    m_pObject2D.push_back(pScene2D);

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