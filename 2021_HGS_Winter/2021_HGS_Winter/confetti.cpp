//===================================================
//
// 紙吹雪処理 [confetti.cpp]
//    Author : 増澤 未来
//
//====================================================

//**********************************
//インクルード
//**********************************
#include "confetti.h"
#include "renderer.h"
#include "manager.h"

//**********************************
//マクロ定義
//**********************************
#define MIN_SIZE (10.0f)                // 最小サイズ
#define RAND_SIZE_AMPLITUDE (20)       // 乱数のふり幅*サイズ
#define ADJUST_RAND (100.0f)           // 乱数生成時調整値*小数点を出すため
#define MIN_LIFE (30.0f)               // 最小ライフ
#define RAND_LIFE_AMPLITUDE (20)       // 乱数のふり幅*寿命
#define RAND_MOVE_ANGLE_AMPLITUDE (45) // 乱数のふり幅*紙吹雪を飛ばす角度
#define MIN_SPEED (12.0f)               // 最小スピード
#define RAND_SPEED_AMPLITUDE (10)      // 乱数のふり幅*スピード
#define ADD_ANGLE (D3DXToRadian(1.0f))                 // 角度加算値
#define MOVE_Y_DIST (5.0f)                      // 移動量Yの目標値
#define MOVE_RATE (0.035f)                       // 移動量の係数
#define SIZE_DIST D3DXVECTOR3(-2.0f,-2.0f,0.0f) // サイズの目標値
#define SIZE_RATE (0.2f)                        // サイズの係数
#define RAND_COLOR_AMPLITUDE (5)                // 乱数のふり幅*色

//==================================
// コンストラクタ
//==================================
CConfetti::CConfetti(PRIORITY pri) :CScene2D(pri)
{
    m_nLife = 0;
    m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_fMoveAngle = 0.0f;
    m_fMoveRate = MOVE_RATE;
    m_fAngle = 0.0f;
}

//==================================
// デストラクタ
//==================================
CConfetti::~CConfetti()
{
}

//==================================
// クリエイト
//==================================
CConfetti * CConfetti::Create(D3DXVECTOR3 pos, D3DXCOLOR col, float fMoveAngle)
{
    // メモリの確保
    CConfetti *pConfetti = NULL;
    pConfetti = new CConfetti;

    //NULLチェック
    if (pConfetti != NULL)
    {
        pConfetti->m_fMoveAngle = fMoveAngle;
        // 初期化処理
        pConfetti->Init();
        pConfetti->SetPos(pos);

        float fRate = (float)(rand() % RAND_COLOR_AMPLITUDE) / 10.0f;
        D3DXCOLOR polygonColor;
        D3DXColorLerp(&polygonColor, &col, &D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), fRate);
        pConfetti->SetColor(polygonColor);

    }
    return pConfetti;
}

//==================================
// 初期化処理
//==================================
HRESULT CConfetti::Init(void)
{
    CScene2D::Init();

    // サイズの設定
    float fRandSize = (float)(rand() % (RAND_SIZE_AMPLITUDE*(int)ADJUST_RAND));
    fRandSize = MIN_SIZE + (fRandSize / ADJUST_RAND);
    SetSize(D3DXVECTOR3(fRandSize, fRandSize, 0.0f));

    // 寿命の設定
    m_nLife = MIN_LIFE + rand() % RAND_LIFE_AMPLITUDE;

    // 初期角度の設定
    m_fAngle = D3DXToRadian(rand() % 360);
    SetRotation(m_fAngle);
    
    // 移動角度の設定
    m_fMoveAngle += D3DXToRadian((rand() % RAND_MOVE_ANGLE_AMPLITUDE) - (RAND_MOVE_ANGLE_AMPLITUDE / 2));

    // スピード
    float fRandSpeed = (float)(rand() % (RAND_SPEED_AMPLITUDE*(int)ADJUST_RAND));
    fRandSpeed = MIN_SPEED + (fRandSpeed / ADJUST_RAND);

    // 移動量の設定
    m_move = D3DXVECTOR3(cosf(m_fMoveAngle)*fRandSpeed, sinf(m_fMoveAngle)*fRandSpeed*2.0f, 0.0f);

    m_fMoveRate = (float)(rand() % (3 + 1));

    m_fMoveRate = m_fMoveRate / ADJUST_RAND + MOVE_RATE;

    return S_OK;
}

//==================================
// 更新処理
//==================================
void CConfetti::Update(void)
{
    // 座標に移動量を足す
    SetPos(GetPos() + m_move);
    // 移動量の変異;
    m_move.y += (MOVE_Y_DIST - m_move.y)*m_fMoveRate;
    
    // 角度
    if (m_move.x >= 0) m_fAngle += ADD_ANGLE;
    else               m_fAngle -= ADD_ANGLE;

    SetRotation(m_fAngle);
    // 寿命処理
    m_nLife--;
    if (m_nLife < 0)
    {
        // サイズを小さくする
        D3DXVECTOR3 size = GetSize();
        size += (SIZE_DIST - size)*SIZE_RATE;
        SetSize(size);
        // 消す
        if (size.x <= 0)
        {
            Uninit();
        }
    }
}

//==================================
// 描画処理
//==================================
void CConfetti::Draw()
{
    // デバイスの取得
    LPDIRECT3DDEVICE9 pDevice = GET_RENDERER_DEVICE;

    // 加算合成
    pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
    pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

    CScene2D::Draw();

    // 通常合成に戻す
    pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
    pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
