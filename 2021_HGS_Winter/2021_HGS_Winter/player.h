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
#include "judge.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CNumber2d;

//=============================================================================
// �v���C���[�N���X
//=============================================================================
class CPlayer : public CJudge
{
public:
    CPlayer(PRIORITY Priority = PRIORITY_CHARACTER);    // �R���X�g���N�^
    ~CPlayer();                                         // �f�X�g���N�^

    static CPlayer*Create();    // �N���G�C�g

    HRESULT Init();         // ����������
    void Uninit();          // �I������
    void Update();          // �X�V����
    void EndCombo();        // �R���{�I��
    void CreateEffect();    // ���o�̐���

    // Get�֐�
    int GetCombo()const { return m_nCombo; }

private:
    void SelectHand();  // ���I��
    void Judge();       // ����
    void AddCombo();    // �R���{�̉��Z
    void CreateCombo(); // �R���{UI����

    HAND_TYPE m_Correct;            // ����
    vector<CNumber2d*> m_apCombo;   // �R���{�p�|�C���^
    int m_nCombo;                   // �R���{
    bool m_bCombo;                  // �R���{���g�p���Ă��邩
};
#endif