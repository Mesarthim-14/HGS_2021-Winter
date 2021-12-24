#ifndef _JUDGE_H_
#define _JUDGE_H_
//=============================================================================
//
// CPU�N���X [cpu.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// �C���N���[�h
//=========================================================================
#include "model.h"

//=========================================================================
// �O���錾
//=========================================================================
class CScene2D;

//=========================================================================
// �N���X��`
//=========================================================================
class CJudge : public CScene
{
public:
    enum HAND_TYPE
    {
        HAND_TYPE_NONE = -1,  // �����l
        HAND_TYPE_GU,         // �O�[
        HAND_TYPE_CHOKI,      // �`���L
        HAND_TYPE_PA,         // �p�[
        HAND_TYPE_MAX         // �ő�l
    };
    enum CORRECT_TYPE
    {
        CORRECT_TYPE_NONE = -1,  // �����l
        CORRECT_TYPE_WIN,        // ����
        CORRECT_TYPE_DRAW,       // ��������
        CORRECT_TYPE_LOSE,       // ����
        CORRECT_TYPE_MAX         // �ő�l
    };

    CJudge(PRIORITY = PRIORITY_MODEL);    // �R���X�g���N�^
    ~CJudge();                              // �f�X�g���N�^

    static CJudge *Create();    // �C���X�^���X����
    virtual HRESULT Init();     // ����������
    virtual void Uninit();      // �I������
    virtual void Update();      // �X�V����
    void Draw() {}

    // Set�֐�
    void SetHand(HAND_TYPE Num) { m_Hand = Num; }
    void BindScene2D(CScene2D* pScene);

    // Get�֐�
    HAND_TYPE GetHand()const    { return m_Hand; }
    CScene2D* GetScene()const   { return m_pScene2D; }

private:
    HAND_TYPE m_Hand;       // �o����
    CScene2D* m_pScene2D;   // �摜
};

#endif