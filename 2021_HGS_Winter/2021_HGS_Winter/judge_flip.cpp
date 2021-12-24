//=============================================================================CJudgeFlip
//
// �W���b�W�t���b�v�N���X [judge_flip.cpp]
// Author : Masuzawa Mirai
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "judge_flip.h"
#include "texture.h"
#include "resource_manager.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define POS D3DXVECTOR3(SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f - 200.0f, 0.0f)
#define SIZE D3DXVECTOR3(200.0f, 200.0f, 0.0f)
#define WIN_TEX_NUM CTexture::TEXTURE_NUM_AUDIENCE1
#define LOSE_TEX_NUM CTexture::TEXTURE_NUM_AUDIENCE2

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CJudgeFlip::CJudgeFlip(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CJudgeFlip::~CJudgeFlip()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CJudgeFlip * CJudgeFlip::Create()
{
    // �������m��
    CJudgeFlip *pPolygon = new CJudgeFlip(PRIORITY_UI);

    // !nullcheck
    if (pPolygon)
    {
        // ����������
        pPolygon->Init();

        return pPolygon;
    }

    return nullptr;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CJudgeFlip::Init()
{
    // ����������
    SetSceneInfo(POS, SIZE);
    CScene2D::Init();

    BindTexture(GET_TEXTURE_PTR->GetTexture(WIN_TEX_NUM));

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CJudgeFlip::Uninit()
{
    CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CJudgeFlip::Update()
{
    CScene2D::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CJudgeFlip::Draw()
{
    CScene2D::Draw();
}

void CJudgeFlip::SetFlip(JUDGE_FLIP_STATE state)
{
    switch (state)
    {
    case CJudgeFlip::STATE_WIN:
        BindTexture(GET_TEXTURE_PTR->GetTexture(WIN_TEX_NUM));
        break;
    case CJudgeFlip::STATE_LOSE:
        BindTexture(GET_TEXTURE_PTR->GetTexture(LOSE_TEX_NUM));
        break;

    default:
        break;
    }
}
