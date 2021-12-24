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
}