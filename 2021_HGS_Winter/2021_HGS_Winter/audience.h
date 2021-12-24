#ifndef _AUDIENCE_H_
#define _AUDIENCE_H_
//=============================================================================
//
// �ϋq�N���X [audience.h]
// Author : Masuzawa Mirai
//
//=============================================================================

//=========================================================================
// �C���N���[�h
//=========================================================================
#include "scene2d.h"

//=========================================================================
// �O���錾
//=========================================================================

//=========================================================================
// �N���X��`
//=========================================================================
class CAudience : public CScene2D
{
public:
    enum AUDIENCE_PARTS
    {
        PARTS_BACK = 0,
        PARTS_FRONT,
        PARTS_MAX
    };

    CAudience(PRIORITY = PRIORITY_UI); // �R���X�g���N�^
    ~CAudience();                     // �f�X�g���N�^

    static CAudience *Create();   // �C���X�^���X����
    HRESULT Init();            // ����������
    void Uninit();             // �I������
    void Update();             // �X�V����
    void Draw();               // �`��


    void SetUpFrag(bool bUp)    { m_bUp = bUp; }
    void SetDrawFlag()          { m_bDraw = true; }

    int GetStep(void) { return m_nStep; };
    void SetStep(int nStep) { m_nStep = nStep; };
private:

    const static D3DXVECTOR3 m_aUpPos[PARTS_MAX];
    CScene2D *m_apPolygon[PARTS_MAX];
    D3DXVECTOR3 m_basePos[PARTS_MAX];
    D3DXVECTOR3 m_aOffsetPos[PARTS_MAX];
    float       m_afMoveY[PARTS_MAX];
    bool m_bUp;
    bool m_bDraw;
    int m_nCntUp;
    int m_nStep;

};

#endif