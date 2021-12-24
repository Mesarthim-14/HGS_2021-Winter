//=============================================================================CGauge
//
// �Q�[�W�N���X [gauge.cpp]
// Author : Masuzawa Mirai
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "gauge.h"
#include "texture.h"
#include "resource_manager.h"
#include "judge_flip.h"
#include "player.h"
#include "scene2d.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define POS D3DXVECTOR3(SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f - 200.0f, 0.0f)
#define SIZE D3DXVECTOR3(200.0f, 200.0f, 0.0f)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGauge::CGauge(PRIORITY Priority) : CScene2D(Priority)
{
    m_nMaxFrame = 0;
    m_nCntFrame = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGauge::~CGauge()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CGauge * CGauge::Create(int nMaxFrame)
{
    // �������m��
    CGauge *pPolygon = new CGauge(PRIORITY_UI);

    // !nullcheck
    if (pPolygon)
    {
        // ����������
        pPolygon->Init();
        pPolygon->m_nMaxFrame = nMaxFrame;
        return pPolygon;
    }

    return nullptr;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CGauge::Init()
{
    // ����������
    SetSceneInfo(POS, SIZE);
    CScene2D::Init();

    SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.3f));
    
    m_nCntFrame = 0;
    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CGauge::Uninit()
{
    CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CGauge::Update()
{
    if (!CManager::GetInstance()->GetGame()->GetPlayer()->GetEnd())
    {
        CScene2D::Update();

        m_nCntFrame++;

        if (m_nCntFrame >= m_nMaxFrame)
        {
            Uninit();
            return;
        }
        // �e�N�X�`���A�j���[�V�����̊Ǘ�
        VERTEX_2D *pVtx;
        // ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
        GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

        // �e�N�X�`�����W�̐ݒ�
        pVtx[0].pos.y = pVtx[2].pos.y - 200.0f * ((float)m_nCntFrame / (float)m_nMaxFrame);
        pVtx[1].pos.y = pVtx[3].pos.y - 200.0f * ((float)m_nCntFrame / (float)m_nMaxFrame);


        // ���_�o�b�t�@���A�����b�N����
        GetVtxBuff()->Unlock();

    }
}

//=============================================================================
// �`�揈��
//=============================================================================
void CGauge::Draw()
{
    // �X�e���V���o�b�t�@���g��
    LPDIRECT3DDEVICE9 pDevice = GET_RENDERER_DEVICE;

    // �X�e���V���e�X�g��L����
    pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

    // �X�e���V���e�X�g�Ɣ�r����Q�ƒl�ݒ�
    pDevice->SetRenderState(D3DRS_STENCILREF, JUDGE_FLIP_STENCIL);

    // �X�e���V���e�X�g�̒l�ɑ΂��Ẵ}�X�N�ݒ� 0xff(�S�Đ^)
    pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);

    // ���̕`��ł̎Q�ƒl == �X�e���V���o�b�t�@�̎Q�ƒl�Ȃ獇�i
    pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);

    // �X�e���V���e�X�g�̌��ʂɑ΂��Ă̔��f�ݒ�
    pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
    pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
    pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);

    // �`�揈��
    CScene2D::Draw();

    // �X�e���V���e�X�g�𖳌���
    pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
}
