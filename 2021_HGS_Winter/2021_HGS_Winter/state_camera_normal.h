#ifndef _STATE_CAMERA_NORMAL_H_
#define _STATE_CAMERA_NORMAL_H_
//=====================================================================
//
//    �ʏ�J������ԊǗ��N���X [state_camera_normal.h]
//    Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "state_camera.h"

//=====================================================================
// �O���錾
//=====================================================================
class CCamera;

//=====================================================================
// �N���X��`
//=====================================================================
class CCameraStateNormal : public CCameraState
{
public:
    CCameraStateNormal();                   // �R���X�g���N�^
    ~CCameraStateNormal();                  // �f�X�g���N�^
    static CCameraStateNormal* Create();    // �C���X�^���X����

    void Init();            // ����������
    void Update()override;  // �X�V����

private:
    // private�֐�
    void KeyBoardMove(CCamera* &pCamera);   // �L�[�{�[�h�̍X�V����

};
#endif