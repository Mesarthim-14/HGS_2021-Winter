////////////////////////////////////////////////////
//
//    ���̎q�N���X�̏���[girle.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//=============================
// �C���N���[�h
//=============================
#include "girle.h"
#include "texture.h"
#include "manager.h"
#include "resource_manager.h"

//**********************************
// �}�N����`
//**********************************
#define POS D3DXVECTOR3(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f,0.0f)
#define SIZE D3DXVECTOR3(200.0f,250.0f,0.0f)

//=============================
// �R���X�g���N�^
//=============================
CGirle::CGirle(PRIORITY pri) : CScene2D(pri)
{
}

//=============================
// �f�X�g���N�^
//=============================
CGirle::~CGirle()
{
}

//=============================
// �N���G�C�g
//=============================
CGirle * CGirle::Create(void)
{
    // �������̊m��
    CGirle *pGirle = new CGirle;
    // ������
    pGirle->Init();

    return pGirle;
}

//=============================
// ����������
//=============================
HRESULT CGirle::Init(void)
{
    // ����������
    SetSceneInfo(POS, SIZE);

    CScene2D::Init();

    return S_OK;
}

//=============================
// �I������
//=============================
void CGirle::Uninit(void)
{
    // �J������
    Release();
}

//=============================
// �X�V����
//=============================
void CGirle::Update(void)
{
    CScene2D::Update();
}

//=============================
// �X�V����
//=============================
void CGirle::Draw()
{
    CScene2D::Draw();
}
