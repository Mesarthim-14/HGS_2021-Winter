////////////////////////////////////////////////////
//
//    �ϋq�N���X�̏���[audience.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//=============================
// �C���N���[�h
//=============================
#include "audience.h"
#include "scene2d.h"
#include "manager.h"
#include "texture.h"
#include "resource_manager.h"

//**********************************
// �}�N����`
//**********************************
#define SIZE D3DXVECTOR3(612.0f, 344.0f, 0.0f)*2.2f
#define MOVE_SPEED_Y    1.0f
#define MOVE_SPEED_RATE 1.3f
#define OFFSET_POS_Y_MAX 10.0f
#define BASE_POS D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - 120.0f, 0.0f)
#define UP_FRAME 100
#define UP_RATE  0.05f

//**********************************
// �ÓI�����o�ϐ���`
//**********************************
const D3DXVECTOR3 CAudience::m_aUpPos[PARTS_MAX] = 
{
    D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - 300.0f, 0.0f),
    D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - 200.0f, 0.0f)
};

//=============================
// �R���X�g���N�^
//=============================
CAudience::CAudience(PRIORITY pri) : CScene2D(pri)
{
    ZeroMemory(&m_aOffsetPos, sizeof(m_aOffsetPos));
    ZeroMemory(&m_afMoveY, sizeof(m_afMoveY));
    ZeroMemory(&m_basePos, sizeof(m_basePos));
    m_bUp = false;
    m_nCntUp = 0;
}

//=============================
// �f�X�g���N�^
//=============================
CAudience::~CAudience()
{
}

//=============================
// �N���G�C�g
//=============================
CAudience * CAudience::Create(void)
{
    // �������̊m��
    CAudience *pConfettiFactory = new CAudience;
    // ������
    pConfettiFactory->Init();

    return pConfettiFactory;
}

//=============================
// ����������
//=============================
HRESULT CAudience::Init(void)
{
    
    for (int nCntPats = 0; nCntPats < PARTS_MAX; nCntPats++)
    {
        m_basePos[nCntPats] = BASE_POS;
        m_aOffsetPos[nCntPats] = ZeroVector3;
        m_apPolygon[nCntPats] = new CScene2D(PRIORITY_UI);
        m_apPolygon[nCntPats]->SetSceneInfo(m_basePos[nCntPats], SIZE);
        m_apPolygon[nCntPats]->Init();
    }

    m_afMoveY[PARTS_FRONT] = MOVE_SPEED_Y;
    m_afMoveY[PARTS_BACK] = MOVE_SPEED_Y * MOVE_SPEED_RATE;

    m_apPolygon[PARTS_FRONT]->BindTexture(GET_TEXTURE_PTR->GetTexture(CTexture::TEXTURE_NUM_AUDIENCE2));
    m_apPolygon[PARTS_BACK]->BindTexture(GET_TEXTURE_PTR->GetTexture(CTexture::TEXTURE_NUM_AUDIENCE1));
    
    m_bUp = false;
    m_nCntUp = 0;

    return S_OK;
}

//=============================
// �I������
//=============================
void CAudience::Uninit(void)
{
    // �J������
    Release();
}


//=============================
// �X�V����
//=============================
void CAudience::Update(void)
{
    for (int nCntPats = 0; nCntPats < PARTS_MAX; nCntPats++)
    {
        if (m_bUp)
        {
            m_basePos[nCntPats] += (m_aUpPos[nCntPats] - m_basePos[nCntPats]) * UP_RATE;
            m_nCntUp++;
            if (m_nCntUp >= UP_FRAME) m_bUp = false;
        }
        else
        {
            m_nCntUp = 0;
            m_basePos[nCntPats] += (BASE_POS - m_basePos[nCntPats]) * UP_RATE;
        }

        m_aOffsetPos[nCntPats].y += m_afMoveY[nCntPats];

        if (m_aOffsetPos[nCntPats].y >= OFFSET_POS_Y_MAX || m_aOffsetPos[nCntPats].y <= -OFFSET_POS_Y_MAX)
        {
            m_afMoveY[nCntPats] *= -1;
        }

        m_apPolygon[nCntPats]->SetSceneInfo(m_basePos[nCntPats] + m_aOffsetPos[nCntPats], SIZE);

        m_apPolygon[nCntPats]->SetVertexPos();
    }
 
   // m_apPolygon[PARTS_FRONT]->SetSceneInfo()
}

//=============================
// �`�揈��
//=============================
void CAudience::Draw(void)
{
}