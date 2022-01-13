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
#include "player.h"
#include "number_2d.h"
#include "game.h"

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
    // リザルトテクスチャの生成
    CScene2D* pScene2D = CScene2D::Create(HALF_SCREEN_POS, SCREEN_SIZE);
    pScene2D->BindTexture(GET_TEXTURE_PTR->GetTexture(CTexture::TEXTURE_NUM_RESULT));
    m_pObject2D.push_back(pScene2D);

    // コンボ数
    int nComboDigit = 0;
    int nConboNum = CManager::GetInstance()->GetResultScore();

    // 桁数を求める
    do
    {
        nConboNum /= 10;
        nComboDigit++;
    } while (nConboNum != 0);

    int nScore = CManager::GetInstance()->GetResultScore();

    // スコアの生成
    for (int nCount = 0; nCount < nComboDigit; nCount++)
    {
        // スコアの生成
        CNumber2d *pNumber2d = CNumber2d::Create(D3DXVECTOR3(740.0f - nCount * 200.0f, 380.0f, 0.0f), D3DXVECTOR3(255.0f, 255.0f, 0.0f));	// 座標、サイズ

        // !nullcheck
        if (pNumber2d)
        {
            // テクスチャのポインタ
            CTexture *pTexture = GET_TEXTURE_PTR;
            // テクスチャの設定
            pNumber2d->BindTexture(
                pTexture->GetTexture(CTexture::TEXTURE_NUM_NUMBER));	// テクスチャの設定

            if (nCount == 0)
            {
                // 数字の設定
                pNumber2d->SetNumber(nScore);
            }
            else
            {
                // 数字の設定
                pNumber2d->SetNumber(nScore / (nCount * 10));
            }
        }
    }

    if (nScore < 10)
    {
        CManager::GetInstance()->CManager::GetResourceManager()->GetSoundClass()->Play(CSound::SOUND_SE_MOUHITOIKI);
    }
    else if (nScore >= 10 && nScore < 20)
    {
        CManager::GetInstance()->CManager::GetResourceManager()->GetSoundClass()->Play(CSound::SOUND_SE_GOOD);
    }
    else if (nScore >= 20 && nScore < 30)
    {
        CManager::GetInstance()->CManager::GetResourceManager()->GetSoundClass()->Play(CSound::SOUND_SE_EXCELLENT);
    }
    else if (nScore >= 30)
    {
        CManager::GetInstance()->CManager::GetResourceManager()->GetSoundClass()->Play(CSound::SOUND_SE_MARVELOUS);
    }

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
        CManager::GetInstance()->CManager::GetResourceManager()->GetSoundClass()->Play(CSound::SOUND_SE_BYE);

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