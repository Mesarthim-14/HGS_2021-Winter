////////////////////////////////////////////////////
//
//    女の子クラスの処理[girle.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//=============================
// インクルード
//=============================
#include "end.h"
#include "texture.h"
#include "manager.h"
#include "resource_manager.h"

//**********************************
// マクロ定義
//**********************************
#define POS D3DXVECTOR3(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f,0.0f)
#define DOWN_POS D3DXVECTOR3(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f+100.0f,0.0f)
#define SIZE D3DXVECTOR3(7559.0f/16.0f,4252.0f/8.0f,0.0f)
#define DOWN_SIZE (SIZE*0.85f)
#define ANIM_X_MAX 2
#define RHYTHM_INTERVAL 30

//=============================
// コンストラクタ
//=============================
CEnd::CEnd(PRIORITY pri) : CScene2D(pri)
{
    m_nTexNum = 0;
    m_nCntRhythm = 0;
}

//=============================
// デストラクタ
//=============================
CEnd::~CEnd()
{
}

//=============================
// クリエイト
//=============================
CEnd * CEnd::Create(void)
{
    // メモリの確保
    CEnd *pGirle = new CEnd(PRIORITY_UI);
    // 初期化
    pGirle->Init();

    return pGirle;
}

//=============================
// 初期化処理
//=============================
HRESULT CEnd::Init(void)
{
    // 初期化処理
    SetSceneInfo(HALF_SCREEN_POS, D3DXVECTOR3(700.0f, 400.0f, 0.0f));

    CScene2D::Init();

    BindTexture(GET_TEXTURE_PTR->GetTexture(CTexture::TEXTURE_NUM_END));
    m_nCntRhythm = 0;
    return S_OK;
}

//=============================
// 終了処理
//=============================
void CEnd::Uninit(void)
{
    CScene2D::Uninit();
}

//=============================
// 更新処理
//=============================
void CEnd::Update(void)
{
}

//=============================
// 更新処理
//=============================
void CEnd::Draw()
{
    CScene2D::Draw();
}
