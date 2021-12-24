#ifndef _CPU_H_
#define _CPU_H_
//=============================================================================
//
// CPU�N���X [cpu.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// �C���N���[�h
//=========================================================================
#include "judge.h"

//=========================================================================
// �O���錾
//=========================================================================
class CScene2D;
class CPlayer;

//=========================================================================
// �N���X��`
//=========================================================================
class CCpu : public CJudge
{
public:
    CCpu(PRIORITY = PRIORITY_MODEL);    // �R���X�g���N�^
    ~CCpu();                            // �f�X�g���N�^

    static CCpu *Create();  // �C���X�^���X����
    HRESULT Init();         // ����������
    void Uninit();          // �I������
    void Update();          // �X�V����
    void Draw();            // �`��

    void SetJudge(const bool& bFlag)    { m_bJudge = bFlag; }  // �W���b�W
    bool GetJudge()const                { return m_bJudge; }
    CORRECT_TYPE GetCorrect()const      { return m_Correct; }

private:
    void SelectJudge(); // ���I��
    void SubInter(CPlayer* &pPlayer);    // �Ԋu�̌��Z

    CORRECT_TYPE m_Correct; // �����̎�
    int m_nCounter;         // �����񂽁[
    int m_nInterval;        // �C���^�[�o��
    int m_nSubInter;        // �C���^�[�o���̌��Z�l
    bool m_bJudge;          // �W���b�W
};

#endif