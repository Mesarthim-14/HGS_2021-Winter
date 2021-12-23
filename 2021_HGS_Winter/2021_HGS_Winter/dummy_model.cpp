//=============================================================================
//
// テストモデルクラス [test_model.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "dummy_model.h"
#include "manager.h"
#include "renderer.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TEST_POS        (ZeroVector3)
#define TEST_ROT        (ZeroVector3)

//=============================================================================
// コンストラクタ
//=============================================================================
CDummyModel::CDummyModel(PRIORITY Priority) : CModel(Priority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CDummyModel::~CDummyModel()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CDummyModel * CDummyModel::Create()
{
    // メモリ確保
    CDummyModel *pTestModel = new CDummyModel(PRIORITY_MODEL);

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
HRESULT CDummyModel::Init()
{
    // 初期化処理
    CModel::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_TEST_DUMMY);
    GetModelInfo()->SetModelStatus(TEST_POS, TEST_ROT, model);

    return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CDummyModel::Uninit()
{
    CModel::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CDummyModel::Update()
{
    CModel::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CDummyModel::Draw()
{
    CModel::Draw();
}