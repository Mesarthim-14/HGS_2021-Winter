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
#define DOWN_POS D3DXVECTOR3(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f+100.0f,0.0f)
#define SIZE D3DXVECTOR3(7559.0f/16.0f,4252.0f/8.0f,0.0f)
#define DOWN_SIZE (SIZE*0.85f)
#define ANIM_X_MAX 2
#define RHYTHM_INTERVAL 30

//=============================
// �R���X�g���N�^
//=============================
CGirle::CGirle(PRIORITY pri) : CScene2D(pri)
{
    m_nTexNum = 0;
    m_nCntRhythm = 0;
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
    CGirle *pGirle = new CGirle(PRIORITY_CHARACTER);
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
    SetSceneInfo(DOWN_POS, DOWN_SIZE);

    CScene2D::Init();

    BindTexture(GET_TEXTURE_PTR->GetTexture(CTexture::TEXTURE_NUM_GIRLE));
    m_nCntRhythm = 0;
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

    // ���񂿂Ꮘ��
    m_nCntRhythm++;
    m_nCntRhythm %= RHYTHM_INTERVAL;
    D3DXVECTOR3 pos = GetPos();
    D3DXVECTOR3 size = GetSize();
    if (m_nCntRhythm <= RHYTHM_INTERVAL / 3 == 0)
    {
        pos += (DOWN_POS - pos)*0.05f;
        size += (DOWN_SIZE - size)*0.05f;
    }
    else
    {
        pos += (POS - pos)*0.01f;
        size += (SIZE - size)*0.01f;
    }
    SetPos(pos);
    SetSize(size);

    SetVertexPos();

    // �e�N�X�`���A�j���[�V�����̊Ǘ�
    VERTEX_2D *pVtx;
    // ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
    GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

    // �e�N�X�`�����W�̐ݒ�
    pVtx[0].tex = D3DXVECTOR2((1.0f / ANIM_X_MAX) * (float)m_nTexNum                      , 0.0f);
    pVtx[1].tex = D3DXVECTOR2((1.0f / ANIM_X_MAX) * (float)m_nTexNum + (1.0f / ANIM_X_MAX), 0.0f);
    pVtx[2].tex = D3DXVECTOR2((1.0f / ANIM_X_MAX) * (float)m_nTexNum                      , 1.0f);
    pVtx[3].tex = D3DXVECTOR2((1.0f / ANIM_X_MAX) * (float)m_nTexNum + (1.0f / ANIM_X_MAX), 1.0f);

    // ���_�o�b�t�@���A�����b�N����
    GetVtxBuff()->Unlock();
}

//=============================
// �X�V����
//=============================
void CGirle::Draw()
{
    CScene2D::Draw();
}
