//=============================================================================
//
// モデルクラス [model.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "model.h"
#include "manager.h"
#include "renderer.h"
#include "model_info.h"
#include "player.h"
#include "library.h"
#include "resource_manager.h"
#include "texture.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CModel::CModel(PRIORITY Priority) : CScene(Priority)
{
    m_move = ZeroVector3;
    m_size = ZeroVector3;
    m_scale = MODEL_DEFAULT_SIZE;
    m_nTexPattern = 0;
    m_nLife = 0;
    m_pModelInfo = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
CModel::~CModel()
{

}

//=============================================================================
// クリエイト処理
//=============================================================================
CModel * CModel::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
    //モデルクラスのポインタ変数
    CModel *pModel = new CModel(PRIORITY_MODEL);

    // nullcheck
    if (pModel)
    {
        //初期化処理呼び出し
        pModel->Init();
        return pModel;
    }

    return nullptr;
}

//=============================================================================
// プレイヤーとの距離の当たり判定
//=============================================================================
bool CModel::PlayerDisCollision(const float &fDistanse)
{
    // 座標の取得
    CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
    if (!pPlayer)
    {
        return false;
    }
    D3DXVECTOR3 PPos = pPlayer->GetPos();
    D3DXVECTOR3 ThisPos = GetModelInfo()->GetPos();

    // 距離の取得
    float fDistance = CLibrary::CalDistance(PPos, ThisPos);

    // 距離を測る
    if (fDistance <= fDistanse)
    {
        return true;
    }

    return false;
}

//=============================================================================
//モデルクラスの初期化処理
//=============================================================================
HRESULT CModel::Init()
{
    // 情報の生成
    CreateInfoPtr();

    return S_OK;
}

//=============================================================================
//モデルクラスの終了処理
//=============================================================================
void CModel::Uninit()
{
    // 影の終了処理
    HasPtrDelete();

    //オブジェクトの破棄
    Release();
}

//=============================================================================
// モデルクラスの更新処理
//=============================================================================
void CModel::Update()
{
    // 寿命を減らす
    m_nLife--;

    // 座標の更新
    m_pModelInfo->GetPos() += m_move;
}

//=============================================================================
// モデルクラスの描画処理
//=============================================================================
void CModel::Draw()
{
    //デバイス情報の取得
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
    D3DMATERIAL9 matDef;
    D3DXMATRIX mtxRot, mtxTrans, mtxScale, mtxWorld;
    D3DXVECTOR3 pos = m_pModelInfo->GetPos();
    D3DXVECTOR3 rot = m_pModelInfo->GetRot();

    //ワールドマトリックスの初期化
    D3DXMatrixIdentity(&mtxWorld);

    CLibrary::ConfigMatrix(&mtxWorld, pos, rot);
    m_pModelInfo->SetMtxWorld(mtxWorld);

    CModelInfo* pModelInfo = GetModelInfo();

    D3DXMATERIAL*pMat;		//マテリアルデータへのポインタ
    //マテリアルデータへのポインタを取得
    pMat = (D3DXMATERIAL*)pModelInfo->GetBuffMat()->GetBufferPointer();

    for (int nCntMat = 0; nCntMat < (int)pModelInfo->GetNumMat(); nCntMat++)
    {
        //マテリアルのアンビエントにディフューズカラーを設定
        pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

        //マテリアルの設定
        pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

        if (pModelInfo->GetModel().apTexture[nCntMat] != nullptr)
        {
            // テクスチャの設定
            pDevice->SetTexture(0, pModelInfo->GetModel().apTexture[nCntMat]);
        }
        else
        {
            pDevice->SetTexture(0, nullptr);
        }

        //モデルパーツの描画
        pModelInfo->GetMesh()->DrawSubset(nCntMat);

        pDevice->SetTexture(0, nullptr);
    }

    //現在のマテリアルを取得する
    pDevice->GetMaterial(&matDef);

    //保持していたマテリアルを戻す
    pDevice->SetMaterial(&matDef);
    pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
}

//=============================================================================
// モデル情報の設定
//=============================================================================
void CModel::HasPtrDelete()
{
    if (m_pModelInfo)
    {
        m_pModelInfo->Uninit();
        m_pModelInfo = nullptr;
    }
}

//=============================================================================
// 情報のポインタ生成
//=============================================================================
void CModel::CreateInfoPtr()
{
    if (!m_pModelInfo)
    {
        m_pModelInfo = CModelInfo::Create(CModelInfo::MODEL_TYPE_NONE);
    }
}

//=============================================================================
// 座標設定
//=============================================================================
void CModel::SetPos(const D3DXVECTOR3 & pos)
{
    GetModelInfo()->SetPos(pos);
}

//=============================================================================
// 角度設定
//=============================================================================
void CModel::SetRot(const D3DXVECTOR3& rot)
{
    GetModelInfo()->SetRot(rot);
}

//=============================================================================
// 座標の情報取得
//=============================================================================
D3DXVECTOR3 CModel::GetPos()const
{
    return GetModelInfo()->GetPos();
}

//=============================================================================
// 角度の情報取得
//=============================================================================
D3DXVECTOR3 CModel::GetRot()const
{
    return GetModelInfo()->GetRot();
}
