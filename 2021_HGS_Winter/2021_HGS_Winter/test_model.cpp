//=============================================================================
//
// テストモデルクラス [test_model.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "test_model.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"
#include "library.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TEST_POS        (ZeroVector3)
#define TEST_ROT        (ZeroVector3)

//=============================================================================
// コンストラクタ
//=============================================================================
CTestModel::CTestModel(PRIORITY Priority) : CModel(Priority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CTestModel::~CTestModel()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CTestModel * CTestModel::Create()
{
    // メモリ確保
    CTestModel *pTestModel = new CTestModel(PRIORITY_MODEL);

    // !nullcheck
    if (pTestModel)
    {
        // 初期化処理
        pTestModel->Init();

        return pTestModel;
    }

    return nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTestModel::Init()
{
    // 初期化処理
    CModel::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_TEST_BLOCK);
    GetModelInfo()->SetModelStatus(TEST_POS, TEST_ROT, model);
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTestModel::Uninit()
{
    CModel::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CTestModel::Update()
{
    CModel::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CTestModel::Draw()
{
    CModel::Draw();
}