//=============================================================================CGauge
//
// ゲージクラス [gauge.cpp]
// Author : Masuzawa Mirai
//
//=============================================================================

//=============================================================================
// インクルード
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
// マクロ定義
//=============================================================================
#define POS D3DXVECTOR3(SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f - 200.0f, 0.0f)
#define SIZE D3DXVECTOR3(200.0f, 200.0f, 0.0f)

//=============================================================================
// コンストラクタ
//=============================================================================
CGauge::CGauge(PRIORITY Priority) : CScene2D(Priority)
{
    m_nMaxFrame = 0;
    m_nCntFrame = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CGauge::~CGauge()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CGauge * CGauge::Create(int nMaxFrame)
{
    // メモリ確保
    CGauge *pPolygon = new CGauge(PRIORITY_UI);

    // !nullcheck
    if (pPolygon)
    {
        // 初期化処理
        pPolygon->Init();
        pPolygon->m_nMaxFrame = nMaxFrame;
        return pPolygon;
    }

    return nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGauge::Init()
{
    // 初期化処理
    SetSceneInfo(POS, SIZE);
    CScene2D::Init();

    SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.3f));
    
    m_nCntFrame = 0;
    return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CGauge::Uninit()
{
    CScene2D::Uninit();
}

//=============================================================================
// 更新処理
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
        // テクスチャアニメーションの管理
        VERTEX_2D *pVtx;
        // 頂点バッファをロックし、頂点情報へのポインタを取得
        GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

        // テクスチャ座標の設定
        pVtx[0].pos.y = pVtx[2].pos.y - 200.0f * ((float)m_nCntFrame / (float)m_nMaxFrame);
        pVtx[1].pos.y = pVtx[3].pos.y - 200.0f * ((float)m_nCntFrame / (float)m_nMaxFrame);


        // 頂点バッファをアンロックする
        GetVtxBuff()->Unlock();

    }
}

//=============================================================================
// 描画処理
//=============================================================================
void CGauge::Draw()
{
    // ステンシルバッファを使う
    LPDIRECT3DDEVICE9 pDevice = GET_RENDERER_DEVICE;

    // ステンシルテストを有効に
    pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

    // ステンシルテストと比較する参照値設定
    pDevice->SetRenderState(D3DRS_STENCILREF, JUDGE_FLIP_STENCIL);

    // ステンシルテストの値に対してのマスク設定 0xff(全て真)
    pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);

    // この描画での参照値 == ステンシルバッファの参照値なら合格
    pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);

    // ステンシルテストの結果に対しての反映設定
    pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
    pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
    pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);

    // 描画処理
    CScene2D::Draw();

    // ステンシルテストを無効に
    pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
}
