#ifndef _PLAYER_H_
#define _PLAYER_H_
//=============================================================================
//
// �v���C���[�N���X�w�b�_�[ [player.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "character.h"
#include "state_object.h"

//=========================================================================
// �O���錾
//=========================================================================
class CState;
class CDummyModel;

//=============================================================================
// �v���C���[�N���X
//=============================================================================
class CPlayer : public CCharacter, public CStateObject
{
public:
    enum ACTION_STATE
    {
        ACTION_NONE = -1,
        ACTION_IDOL,
        ACTION_MAX
    };//�s�����

    enum STATE_PLAYER
    {
        STATE_PLAYER_NONE = -1,     // �����l
        STATE_PLAYER_IDOL,          // �ʏ���
        STATE_PLAYER_MAX,           // �ő�l
    };

    CPlayer(PRIORITY Priority = PRIORITY_CHARACTER);    // �R���X�g���N�^
    ~CPlayer();                                         // �f�X�g���N�^

    static CPlayer*Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);    // �N���G�C�g

    HRESULT Init();                                 // ����������
    void Uninit();                                  // �I������
    void Update();                                  // �X�V����
    void Draw();                                    // �`�揈��
    void ChangeState(CState* pPlayerState);         // ��ԃ`�F���W

    // Set�֐�
    void SetMove(const D3DXVECTOR3 &move)       { CCharacter::SetMove(move); }  // �ړ��ʐݒ�
    void SetRotDest(const D3DXVECTOR3& rotDest) { m_rotDest = rotDest; }        // �ړI�̊p�x
    void SetAngle(const float& fAngle)          { m_fAngle = fAngle; }          // �A���O��

    // Get�֐�
    int GetLife()const              { return m_nHP; }           // HP�̏��
    float GetAngle()const           { return m_fAngle; }        // �A���O��
    D3DXVECTOR3 GetRotDest()const   { return m_rotDest; }       // �ړI
    D3DXVECTOR3 GetInertia()const   { return m_Inertia; }       // �����̏��
    float GetInertiaNum()const      { return m_fInertiaNum; }   // �����̒l

private:
    // private�֐�
    void UpdateState(); // �v���C���[�̏��
    void UpdateRot();   // �p�x�̍X�V����

    // �����o�ϐ�
    D3DXVECTOR3 m_rotDest;      // ��](�ڕW�l)
    D3DXVECTOR3 m_Inertia;      // ����
    float m_fInertiaNum;        // �����̒l
    float m_fRotationSpeed;     // ��]�̑��x
    bool m_bMove;               // �ړ��̃t���O
    int m_nHP;                  // �X���C��HP ~100�܂Łi�p�[�Z���g�j
    float m_fAngle;             // �J���������A���O��
    float m_fAngleSpeed;        // �ڕW�����܂Ō������X�s�[�h
    ACTION_STATE m_ActionState; // �s�����
    CState* m_pCurrentState;    // ���݂̏�ԃ|�C���^
    CState* m_pNextState;       // ���̏�ԃ|�C���^
    CDummyModel* m_pModel;
};
#endif