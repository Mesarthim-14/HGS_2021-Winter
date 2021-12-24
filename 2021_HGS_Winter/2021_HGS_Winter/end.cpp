////////////////////////////////////////////////////
//
//    ���̎q�N���X�̏���[girle.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//=============================
// �C���N���[�h
//=============================
#include "end.h"
#include "texture.h"
#include "manager.h"
#include "resource_manager.h"

//**********************************
// �}�N����`
//**********************************
#define POS D3DXVECTOR3(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f,0.0f)
#define DOWN_POS D3DXVECTOR3(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f+100.0f,0.0f)
#define SIZE D3DXVECTOR3(7559.0f/16.0f,4252.0f/8.0f,0.0f)
#define DOWN_SIZE (SIZE*0.85f)
#define ANIM_X_MAX 2
#define RHYTHM_INTERVAL 30

//=============================
// �R���X�g���N�^
//=============================
CEnd::CEnd(PRIORITY pri) : CScene2D(pri)
{
    m_nTexNum = 0;
    m_nCntRhythm = 0;
}

//=============================
// �f�X�g���N�^
//=============================
CEnd::~CEnd()
{
}

//=============================
// �N���G�C�g
//=============================
CEnd * CEnd::Create(void)
{
    // �������̊m��
    CEnd *pGirle = new CEnd(PRIORITY_UI);
    // ������
    pGirle->Init();

    return pGirle;
}

//=============================
// ����������
//=============================
HRESULT CEnd::Init(void)
{
    // ����������
    SetSceneInfo(HALF_SCREEN_POS, D3DXVECTOR3(700.0f, 400.0f, 0.0f));

    CScene2D::Init();

    BindTexture(GET_TEXTURE_PTR->GetTexture(CTexture::TEXTURE_NUM_END));
    m_nCntRhythm = 0;
    return S_OK;
}

//=============================
// �I������
//=============================
void CEnd::Uninit(void)
{
    CScene2D::Uninit();
}

//=============================
// �X�V����
//=============================
void CEnd::Update(void)
{
}

//=============================
// �X�V����
//=============================
void CEnd::Draw()
{
    CScene2D::Draw();
}
