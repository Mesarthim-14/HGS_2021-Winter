//=============================================================================
//
// �`���[�g���A���N���X [tutorial.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "tutorial.h"
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
CTutorial::CTutorial()
{
    m_pObject2D.clear();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTutorial::~CTutorial()
{
    // �I������
    Uninit();
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTutorial::Init()
{
    // �^�C�g���e�N�X�`���̐���
    CScene2D* pScene2D = CScene2D::Create(HALF_SCREEN_POS, SCREEN_SIZE);
    pScene2D->BindTexture(GET_TEXTURE_PTR->GetTexture(CTexture::TEXTURE_NUM_TUTORIAL));
    m_pObject2D.push_back(pScene2D);

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTutorial::Uninit()
{
    if (CManager::GetInstance()->CManager::GetResourceManager())
    {
        CSound* pSound = CManager::GetInstance()->CManager::GetResourceManager()->GetSoundClass();
        pSound->Stop(CSound::SOUND_BGM_TITLE);
    }

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
void CTutorial::Update()
{

    CInputKeyboard* pKey = CManager::GetInstance()->GetKeyboard();
    CFade::FADE_MODE mode = CManager::GetInstance()->GetFade()->GetFade();

    // �R���g���[����start���������Ƃ����A�G���^�[�L�[���������Ƃ�
    if (CManager::GetInstance()->GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_START, 0) && mode == CFade::FADE_MODE_NONE
        || pKey->GetTrigger(DIK_RETURN) && mode == CFade::FADE_MODE_NONE)
    {
        CFade *pFade = CManager::GetInstance()->GetFade();
        pFade->SetFade(CManager::MODE_TYPE_GAME);
    }
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTutorial::Draw()
{

}