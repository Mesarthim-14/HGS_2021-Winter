//=============================================================================
//
// タイトルクラス [title.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "title.h"
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
CTitle::CTitle()
{
    m_pObject2D.clear();
}

//=============================================================================
// デストラクタ
//=============================================================================
CTitle::~CTitle()
{
    // 終了処理
    Uninit();
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTitle::Init()
{
    if (CManager::GetInstance()->CManager::GetResourceManager())
    {
        // サウンドの生成
        CManager::GetInstance()->CManager::GetResourceManager()->GetSoundClass()->Play(CSound::SOUND_BGM_TITLE);
    }

    // タイトルテクスチャの生成
    CScene2D* pScene2D = CScene2D::Create(HALF_SCREEN_POS, SCREEN_SIZE);
    pScene2D->BindTexture(GET_TEXTURE_PTR->GetTexture(CTexture::TEXTURE_NUM_TITLE));
    m_pObject2D.push_back(pScene2D);

    return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTitle::Uninit()
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
void CTitle::Update()
{

    CInputKeyboard* pKey = CManager::GetInstance()->GetKeyboard();
    CFade::FADE_MODE mode = CManager::GetInstance()->GetFade()->GetFade();

    // コントローラのstartを押したときか、エンターキーを押したとき
    if (CManager::GetInstance()->GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_START, 0) && mode == CFade::FADE_MODE_NONE
        || pKey->GetTrigger(DIK_RETURN) && mode == CFade::FADE_MODE_NONE)
    {
        // サウンドの再生
        CManager::GetInstance()->CManager::GetResourceManager()->GetSoundClass()->Play(CSound::SOUND_SE_DON);

        CFade *pFade = CManager::GetInstance()->GetFade();
        pFade->SetFade(CManager::MODE_TYPE_TUTORIAL);
    }
}

//=============================================================================
// 描画処理
//=============================================================================
void CTitle::Draw()
{

}