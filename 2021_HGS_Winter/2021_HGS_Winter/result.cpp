//=============================================================================
//
// リザルトクラス [result.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "result.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "scene2d.h"
#include "fade.h"
#include "keyboard.h"
#include "texture.h"
#include "sound.h"
#include "joypad.h"
#include "resource_manager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CResult::CResult()
{
    m_pObject2D.clear();
}

//=============================================================================
// デストラクタ
//=============================================================================
CResult::~CResult()
{
    // 終了処理
    Uninit();
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CResult::Init()
{
    // タイトルテクスチャの生成
    CScene2D* pScene2D = CScene2D::Create(HALF_SCREEN_POS, SCREEN_SIZE);
    pScene2D->BindTexture(GET_TEXTURE_PTR->GetTexture(CTexture::TEXTURE_NUM_RESULT));
    m_pObject2D.push_back(pScene2D);

    return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CResult::Uninit()
{
    for (auto &object : m_pObject2D)
    {
        // 終了処理
        object->Uninit();
    }

    // オブジェクト削除
    m_pObject2D.clear();
}

//=============================================================================
// 更新処理
//=============================================================================
void CResult::Update()
{

    CInputKeyboard* pKey = CManager::GetInstance()->GetKeyboard();
    CFade::FADE_MODE mode = CManager::GetInstance()->GetFade()->GetFade();

    // コントローラのstartを押したときか、エンターキーを押したとき
    if (CManager::GetInstance()->GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_START, 0) && mode == CFade::FADE_MODE_NONE
        || pKey->GetTrigger(DIK_RETURN) && mode == CFade::FADE_MODE_NONE)
    {
        CFade *pFade = CManager::GetInstance()->GetFade();
        pFade->SetFade(CManager::MODE_TYPE_TITLE);
    }
}

//=============================================================================
// 描画処理
//=============================================================================
void CResult::Draw()
{

}