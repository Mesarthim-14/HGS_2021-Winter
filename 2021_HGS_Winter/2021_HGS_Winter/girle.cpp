////////////////////////////////////////////////////
//
//    女の子クラスの処理[girle.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//=============================
// インクルード
//=============================
#include "girle.h"
#include "texture.h"
#include "manager.h"
#include "resource_manager.h"

//**********************************
// マクロ定義
//**********************************
#define POS D3DXVECTOR3(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f,0.0f)
#define SIZE D3DXVECTOR3(200.0f,250.0f,0.0f)

//=============================
// コンストラクタ
//=============================
CGirle::CGirle(PRIORITY pri) : CScene2D(pri)
{
}

//=============================
// デストラクタ
//=============================
CGirle::~CGirle()
{
}

//=============================
// クリエイト
//=============================
CGirle * CGirle::Create(void)
{
    // メモリの確保
    CGirle *pGirle = new CGirle;
    // 初期化
    pGirle->Init();

    return pGirle;
}

//=============================
// 初期化処理
//=============================
HRESULT CGirle::Init(void)
{
    // 初期化処理
    SetSceneInfo(POS, SIZE);

    CScene2D::Init();

    return S_OK;
}

//=============================
// 終了処理
//=============================
void CGirle::Uninit(void)
{
    // 開放処理
    Release();
}

//=============================
// 更新処理
//=============================
void CGirle::Update(void)
{
    CScene2D::Update();
}

//=============================
// 更新処理
//=============================
void CGirle::Draw()
{
    CScene2D::Draw();
}
