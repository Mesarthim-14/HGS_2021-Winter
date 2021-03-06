#ifndef _SOUND_H_
#define _SOUND_H_

//================================================
//
// サウンド処理 [sound.h]
// Author : Konishi Yuuto
//
//================================================

//================================================
// インクルード
//================================================
#include "main.h"
#include "xaudio2.h"

//================================================
//クラス宣言
//================================================
class CSound
{
public:
    enum SOUND_LABEL
    {
        SOUND_BGM_TITLE = 0,        // タイトル
        SOUND_BGM_GAME,
        SOUND_SE_BYE,
        SOUND_SE_CLAP,
        SOUND_SE_DON,
        SOUND_SE_DONDON,
        SOUND_SE_DRAW,
        SOUND_SE_FINISH,
        SOUND_SE_HAPPY,
        SOUND_SE_OUT,
        SOUND_SE_SAFE,
        SOUND_SE_MOUHITOIKI,
        SOUND_SE_GOOD,
        SOUND_SE_EXCELLENT,
        SOUND_SE_MARVELOUS,
        SOUND_SE_START,
        SOUND_SE_GAYA,
        SOUND_SE_HANAFUBUKI,
        SOUND_SE_PON,
        SOUND_LABEL_MAX,
    };

    enum SOUND_LOOP
    {
        SOUND_LOOP_ON = -1,             //ループする
        SOUND_LOOP_OFF,                 //ループしない
    };

    CSound();                           // コンストラクタ
    ~CSound();                          // デストラクタ

    static CSound *Create(void);        // インスタンス生成
    HRESULT Init(void);                 // 初期化処理
    void Uninit(void);                  // 終了処理
    HRESULT Play(SOUND_LABEL label);    // サウンド再生
    void Stop(SOUND_LABEL label);       // サウンドストップ
    void StopAll(void);                 // 全てのサウンドを停止

private:
    struct PARAM
    {
        char *m_pFilename;  // ファイル名
        SOUND_LOOP isLoop;  // ループするかどうか
    };

    HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
    HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
    IXAudio2 *m_pXAudio2 = NULL;                                                                    // XAudio2オブジェクトへのインターフェイス
    IXAudio2MasteringVoice *m_pMasteringVoice = NULL;                                               // マスターボイス
    IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};                                     // ソースボイス
    BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};                                                      // オーディオデータ
    DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};                                                       // オーディオデータサイズ

    // 各音素材のパラメータ
    static PARAM m_aParam[SOUND_LABEL_MAX];
};
#endif