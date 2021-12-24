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
#define DOWN_POS D3DXVECTOR3(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f+100.0f,0.0f)
#define SIZE D3DXVECTOR3(7559.0f/16.0f,4252.0f/8.0f,0.0f)
#define DOWN_SIZE (SIZE*0.85f)
#define ANIM_X_MAX 2
#define RHYTHM_INTERVAL 30

//=============================
// コンストラクタ
//=============================
CGirle::CGirle(PRIORITY pri) : CScene2D(pri)
{
    m_nTexNum = 0;
    m_nCntRhythm = 0;
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
    CGirle *pGirle = new CGirle(PRIORITY_CHARACTER);
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
    SetSceneInfo(DOWN_POS, DOWN_SIZE);

    CScene2D::Init();

    BindTexture(GET_TEXTURE_PTR->GetTexture(CTexture::TEXTURE_NUM_GIRLE));
    m_nCntRhythm = 0;
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

    // ずんちゃ処理
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

    // テクスチャアニメーションの管理
    VERTEX_2D *pVtx;
    // 頂点バッファをロックし、頂点情報へのポインタを取得
    GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

    // テクスチャ座標の設定
    pVtx[0].tex = D3DXVECTOR2((1.0f / ANIM_X_MAX) * (float)m_nTexNum                      , 0.0f);
    pVtx[1].tex = D3DXVECTOR2((1.0f / ANIM_X_MAX) * (float)m_nTexNum + (1.0f / ANIM_X_MAX), 0.0f);
    pVtx[2].tex = D3DXVECTOR2((1.0f / ANIM_X_MAX) * (float)m_nTexNum                      , 1.0f);
    pVtx[3].tex = D3DXVECTOR2((1.0f / ANIM_X_MAX) * (float)m_nTexNum + (1.0f / ANIM_X_MAX), 1.0f);

    // 頂点バッファをアンロックする
    GetVtxBuff()->Unlock();
}

//=============================
// 更新処理
//=============================
void CGirle::Draw()
{
    CScene2D::Draw();
}
