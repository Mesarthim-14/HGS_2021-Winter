//=============================================================================CJudgeFlip
//
// ジャッジフリップクラス [judge_flip.cpp]
// Author : Masuzawa Mirai
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "judge_flip.h"
#include "texture.h"
#include "resource_manager.h"
#include "manager.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define POS D3DXVECTOR3(SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f - 200.0f, 0.0f)
#define SIZE D3DXVECTOR3(200.0f, 200.0f, 0.0f)
#define DOWN_SIZE D3DXVECTOR3(180.0f, 180.0f, 0.0f)
#define WIN_TEX_NUM CTexture::TEXTURE_NUM_AUDIENCE1
#define LOSE_TEX_NUM CTexture::TEXTURE_NUM_AUDIENCE2

//=============================================================================
// コンストラクタ
//=============================================================================
CJudgeFlip::CJudgeFlip(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CJudgeFlip::~CJudgeFlip()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CJudgeFlip * CJudgeFlip::Create()
{
    // メモリ確保
    CJudgeFlip *pPolygon = new CJudgeFlip(PRIORITY_UI);

    // !nullcheck
    if (pPolygon)
    {
        // 初期化処理
        pPolygon->Init();

        return pPolygon;
    }

    return nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CJudgeFlip::Init()
{
    // 初期化処理
    SetSceneInfo(POS, SIZE);
    CScene2D::Init();

    return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CJudgeFlip::Uninit()
{
    CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CJudgeFlip::Update()
{
    CScene2D::Update();

    D3DXVECTOR3 size = GetSize();

    size += (SIZE - size)*0.1f;

    SetSize(size);

    SetVertexPos();
}

//=============================================================================
// 描画処理
//=============================================================================
void CJudgeFlip::Draw()
{
    if (GetTexture())
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
        pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_GREATEREQUAL);

        // ステンシルテストの結果に対しての反映設定
        pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
        pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
        pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);

        CScene2D::Draw();

        // ステンシルテストを無効に
        pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
    }
}

void CJudgeFlip::SetFlip(JUDGE_FLIP_STATE state)
{
    switch (state)
    {
    case CJudgeFlip::STATE_WIN:
        BindTexture(GET_TEXTURE_PTR->GetTexture(CTexture::TEXTURE_NUM_WIN));
        break;
    case CJudgeFlip::STATE_DRAW:
        BindTexture(GET_TEXTURE_PTR->GetTexture(CTexture::TEXTURE_NUM_DRAW));
        break;

    case CJudgeFlip::STATE_LOSE:
        BindTexture(GET_TEXTURE_PTR->GetTexture(CTexture::TEXTURE_NUM_LOSE));
        break;

    default:
        break;
    }

    SetSize(DOWN_SIZE);
    SetVertexPos();
}
