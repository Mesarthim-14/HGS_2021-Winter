#ifndef _MANAGER_H_
#define _MANAGER_H_
//=============================================================================
//
// マネージャー処理 [manager.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define GET_TEXTURE_PTR     (CManager::GetInstance()->GetResourceManager()->GetTextureClass())    // テクスチャのポインタ
#define GET_SOUND_PTR       (CManager::GetInstance()->GetResourceManager()->GetSoundClass())    // サウンドのポインタ
#define GET_XFILE_PTR       (CManager::GetInstance()->GetResourceManager()->GetXfileClass())    // Xファイルのポインタ
#define GET_RENDERER_DEVICE (CManager::GetInstance()->GetRenderer()->GetDevice())                // デバイス取得

//=============================================================================
//前方宣言
//=============================================================================
class CRenderer;
class CInputKeyboard;
class CMouse;
class CFade;
class CInputJoypad;
class CScene;
class CResourceManager;
class CGame;
class CModeBase;
class CLight;
class CCamera;
class CPlayer;


//=============================================================================
//マネージャークラス
//=============================================================================
class CManager
{
public:
    //=========================================================================
    //列挙型定義
    //=========================================================================
    enum MODE_TYPE
    {
        MODE_TYPE_NONE = 0,
        MODE_TYPE_TITLE,            // タイトルモード
        MODE_TYPE_TUTORIAL,         // チュートリアルモード
        MODE_TYPE_GAME,             // ゲームモード
        MODE_TYPE_RESULT,           // リザルトモード
        MODE_TYPE_MAX,
    };

    ~CManager();    // デストラクタ

    HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow); // 初期化処理
    void Uninit();                                              // 終了処理
    void Update();                                              // 更新処理
    void Draw();                                                // 描画処理

    // Set関数
    void SetMode(const MODE_TYPE &mode);    // モードの設定
    void SetResultScore(const int &nScore) { m_nResultScore = nScore; } // リザルト用スコアの設定

    // Get関数
    static CManager* GetInstance();                                                                 // インスタンス情報
    CModeBase *GetModePtr();                                                                        // ゲームの情報
    CGame* GetGame()const;                                                                          // ゲーム情報
    MODE_TYPE GetMode()const                         { return m_mode; }                      // モードの情報
    CRenderer *GetRenderer()const                    { return m_pRenderer.get(); }           // レンダラー情報
    CInputKeyboard *GetKeyboard()const               { return m_pInput.get(); }              // キーボード情報
    CMouse *GetMouse()const                          { return m_pInputMouse.get(); }         // マウス情報
    CFade *GetFade()const                            { return m_pFade.get(); }               // フェード情報
    CInputJoypad *GetJoypad()const                   { return m_pJoypad.get(); }             // ジョイパッドコントローラの情報
    CScene *GetScene()const                          { return m_pScene.get(); }              // シーン情報
    CResourceManager *GetResourceManager()const      { return m_pResourceManager.get(); }    // リソースマネージャのポインタ
    CCamera *GetCamera()const                        { return m_pCamera.get(); }             // カメラのポインタ
    CLight *GetLight()const                          { return m_pLight.get(); }              // ライトのポインタ
    static void SetActivePause(const bool &bPause)   { m_bPause = bPause; }                  // ポーズのセット
    static bool GetActivePause()                     { return m_bPause; }                    // フェードの取得処理
    int GetResultScore()const                       { return m_nResultScore; }               // リザルト用スコアの取得

private:
    // private関数
    void LoadAll();                                        // 全てのロード処理
    void UnLoadAll();                                    // 全てのアンロード処理

    // メンバ変数
    unique_ptr<CRenderer> m_pRenderer;                  // レンダラークラスのポインタ
    unique_ptr<CInputKeyboard> m_pInput;                // インプットクラスのポインタ
    unique_ptr<CMouse> m_pInputMouse;                   // マウスインプットクラスのポインタ
    unique_ptr<CFade> m_pFade;                          // フェードクラスのポインタ
    unique_ptr<CInputJoypad> m_pJoypad;                 // ジョイパッドコントローラのポインタ
    unique_ptr<CScene> m_pScene;                        // シーンのポインタ
    unique_ptr<CResourceManager> m_pResourceManager;    // リソースマネージャのポインタ
    unique_ptr<CModeBase> m_pModeBase;                  // モードのポインタ
    unique_ptr<CCamera> m_pCamera;                      // カメラのポインタ
    unique_ptr<CLight> m_pLight;                        // ライトのポインタ
    MODE_TYPE m_mode;                                   // モード

    // シングルトン
    CManager();                     // コンストラクタ
    static CManager* m_pManager;    // 自身のポインタ

    static bool m_bPause;           // ポーズフラグ

    static int m_nResultScore;      // リザルト用スコア
};

#endif