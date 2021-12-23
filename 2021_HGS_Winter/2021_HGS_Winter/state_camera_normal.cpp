//=====================================================================
//
// �J�����ʏ��ԊǗ��N���X [state_camera_normal.h]
// Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "state_camera_normal.h"
#include "library.h"
#include "manager.h"
#include "game.h"
#include "player.h"
#include "camera.h"
#include "keyboard.h"
#include "renderer.h"

//=====================================================================
// �}�N����`
//=====================================================================
#define INPUT_CONVERSION        (D3DXToRadian(1.0f))    // �X�e�B�b�N���͕ω���
#define PLAYER_HEIGHT           (0.0f)                  // �����_�̍���
#define CAMERA_MIN_HIGHT        (2.0f)                  // �J�����̍Œፂ�x
#define PLAYER_CAMERA_HEIGHT    (300.0f)                // �v���C���[�̍���
#define CAMERA_DISTANCE         (2000.0f)               // �v���C���[�ƃJ�����̋���

//=====================================================================
// �R���X�g���N�^
//=====================================================================
CCameraStateNormal::CCameraStateNormal()
{
}

//=====================================================================
// �f�X�g���N�^
//=====================================================================
CCameraStateNormal::~CCameraStateNormal()
{

}

//=====================================================================
// �C���X�^���X����
//=====================================================================
CCameraStateNormal * CCameraStateNormal::Create()
{
    // �������m��
    CCameraStateNormal *pStateNormal = new CCameraStateNormal;
    if (pStateNormal)
    {
        // ����������
        pStateNormal->Init();
        return pStateNormal;
    }

    return nullptr;
}

//=====================================================================
// ����������
//=====================================================================
void CCameraStateNormal::Init()
{

}

//=====================================================================
// �X�V����
//=====================================================================
void CCameraStateNormal::Update()
{
    CCamera *pCamera = CManager::GetInstance()->GetCamera();
    if (!pCamera)
    {
        return;
    }

    // �L�[�{�[�h�X�V
    KeyBoardMove(pCamera);
}

//=====================================================================
// �L�[�{�[�h����
//=====================================================================
void CCameraStateNormal::KeyBoardMove(CCamera* &pCamera)
{
    // �v���C���[
    CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();
    if (!pPlayer)
    {
        return;
    }

    D3DXVECTOR3 PlayerPos = pPlayer->GetPos();    //�v���C���[�ʒu
    D3DXVECTOR3 PlayerRot = pPlayer->GetRot();    //�v���C���[�ʒu

    // �J�������W
    float fDistance = pCamera->GetDistance();
    float fVartical = pCamera->GetVartical();
    float fHorizontal = pCamera->GetHorizontal();   // �J�����̊p�x

    //�L�[�{�[�h�N���X���̎擾
    CInputKeyboard *pKeyInput = CManager::GetInstance()->GetKeyboard();
    D3DXVECTOR3 VDest = ZeroVector3;

    //���_�i�J�������W�j�̍�����
    if (pKeyInput->GetPress(DIK_LEFT))
    {
        fHorizontal += INPUT_CONVERSION;
    }
    //���_�i�J�������W�j�̉E����
    if (pKeyInput->GetPress(DIK_RIGHT))
    {
        fHorizontal -= INPUT_CONVERSION;
    }
    //���_�i�J�������W�j�̏����
    if (pKeyInput->GetPress(DIK_UP))
    {
        fVartical -= INPUT_CONVERSION;
    }
    //���_�i�J�������W�j�̉�����
    if (pKeyInput->GetPress(DIK_DOWN))
    {
        fVartical += INPUT_CONVERSION;
    }

    // �p�x�̏C��
    CLibrary::RotFix(fHorizontal);

    // �p�x�̐ݒ�
    pCamera->SetVartical(fVartical);
    pCamera->SetHorizontal(fHorizontal);

    // �J�����̈ʒu�ݒ�
    VDest.x = PlayerPos.x + fDistance * sinf(fVartical) * sinf(fHorizontal);    // �J�����ʒuX�ݒ�
    VDest.y = PlayerPos.y + fDistance * cosf(fVartical);                        // �J�����ʒuY�ݒ�
    VDest.z = PlayerPos.z + fDistance * sinf(fVartical) * cosf(fHorizontal);    // �J�����ʒuZ�ݒ�

    D3DXVECTOR3 posRDest = D3DXVECTOR3(PlayerPos.x, PlayerPos.y + PLAYER_HEIGHT, PlayerPos.z);    //�����_�ݒ�

    //�J����POSY�̉���
    if (VDest.y <= CAMERA_MIN_HIGHT)
    {
        VDest.y = CAMERA_MIN_HIGHT;    //���E�l�ɖ߂�
    }

    //�ݒ�l�̔��f
    pCamera->GetposV() += (VDest - pCamera->GetposV())*0.1f;
    pCamera->GetposR() += (posRDest - pCamera->GetposR())*0.9f;
}