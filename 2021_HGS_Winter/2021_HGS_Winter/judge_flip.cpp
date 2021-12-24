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

//=============================================================================
// マクロ定義
//=============================================================================
#define POS D3DXVECTOR3(SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f - 200.0f, 0.0f)
#define SIZE D3DXVECTOR3(200.0f, 200.0f, 0.0f)
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

    BindTexture(GET_TEXTURE_PTR->GetTexture(WIN_TEX_NUM));

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
}

//=============================================================================
// 描画処理
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
