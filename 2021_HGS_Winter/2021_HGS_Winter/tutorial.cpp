//=============================================================================
//
// チュートリアルクラス [tutorial.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "tutorial.h"
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
CTutorial::CTutorial()
{
    m_pObject2D.clear();
}

//=============================================================================
// デストラクタ
//=============================================================================
CTutorial::~CTutorial()
{
    // 終了処理
    Uninit();
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTutorial::Init()
{
    // タイトルテクスチャの生成
    CScene2D* pScene2D = CScene2D::Create(HALF_SCREEN_POS, SCREEN_SIZE);
    pScene2D->BindTexture(GET_TEXTURE_PTR->GetTexture(CTexture::TEXTURE_NUM_TUTORIAL));
    m_pObject2D.push_back(pScene2D);

    return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTutorial::Uninit()
{
    if (CManager::GetInstance()->CManager::GetResourceManager())
    {
        CSound* pSound = CManager::GetInstance()->CManager::GetResourceManager()->GetSoundClass();
        pSound->Stop(CSound::SOUND_BGM_TITLE);
    }

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
void CTutorial::Update()
{

    CInputKeyboard* pKey = CManager::GetInstance()->GetKeyboard();
    CFade::FADE_MODE mode = CManager::GetInstance()->GetFade()->GetFade();

    // コントローラのstartを押したときか、エンターキーを押したとき
    if (CManager::GetInstance()->GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_START, 0) && mode == CFade::FADE_MODE_NONE
        || pKey->GetTrigger(DIK_RETURN) && mode == CFade::FADE_MODE_NONE)
    {
        CFade *pFade = CManager::GetInstance()->GetFade();
        pFade->SetFade(CManager::MODE_TYPE_GAME);
    }
}

//=============================================================================
// 描画処理
//=============================================================================
void CTutorial::Draw()
{

}