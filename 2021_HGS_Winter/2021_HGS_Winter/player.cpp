//=============================================================================
// プレイヤークラス [player.cpp]
// Author : Konishi Yuuto
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "player.h"
#include "manager.h"
#include "keyboard.h"
#include "mouse.h"
#include "renderer.h"
#include "input.h"
#include "joypad.h"
#include "fade.h"
#include "resource_manager.h"
#include "motion.h"
#include "library.h"
#include "camera.h"
#include "game.h"
#include "test_model.h"
#include "model.h"
#include "state_player.h"
#include "state_player_normal.h"

//=============================================================================
// マクロ定義
// Author : Konishi Yuuto
//=============================================================================
#define PLAYER_SPEED			(10.0f)     // プレイヤーの移動量
#define PLAYER_ROT_SPEED		(0.1f)      // キャラクターの回転する速度

//=============================================================================
// 生成処理関数
// Author : Konishi Yuuto
//=============================================================================
CPlayer * CPlayer::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
	// メモリ確保
	CPlayer *pPlayer = new CPlayer;

	// nullcheck
	if (pPlayer)
	{
		// 初期化処理
		pPlayer->SetCharacterInfo(pos, rot);
		pPlayer->Init();
		return pPlayer;
	}

	// CPlayerを返す
	return nullptr;
}

//=============================================================================
// コンストラクタ
// Author : Konishi Yuuto
//=============================================================================
CPlayer::CPlayer(PRIORITY Priority) : CCharacter(Priority)
{
	m_rotDest = ZeroVector3;
	m_bMove = false;
	m_Inertia = ZeroVector3;
	m_fInertiaNum = 0.0f;
	m_fRotationSpeed = 0.1f;
	m_fAngleSpeed = 0.0f;
	m_nHP = 60;
	m_fAngle = 0.0f;
	m_ActionState = ACTION_NONE;
	m_pCurrentState = nullptr;
	m_pNextState = nullptr;
}

//=============================================================================
// デストラクタ
// Author : Konishi Yuuto
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// 初期化処理関数
// Author : Konishi Yuuto
//=============================================================================
HRESULT CPlayer::Init()
{
	// 初期化処理
	CCharacter::Init();

	// 初期化
	m_rotDest = GetRot();			// 向き

	SetType(CHARACTER_TYPE_PLAYER);	// プレイヤー

	if (!m_pCurrentState)
	{
		// インスタンス生成
		m_pCurrentState = CPlayerStateNormal::Create();
	}

	return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::Uninit()
{
#ifdef _DEBUG
	//情報保存

//	SaveInfo();
#endif // !_DEBUG
	CCharacter::Uninit();
}

//=============================================================================
// 更新関数処理関数
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::Update()
{
	{
		// 位置取得
		D3DXVECTOR3 pos = GetPos();

		// 古い位置設定
		SetPosOld(pos);
	}

	// 状態更新
	UpdateState();

	CCharacter::Update();

	// 更新処理
	UpdateRot();
}

//=============================================================================
// 描画処理関数
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::Draw()
{
	// 描画
	CCharacter::Draw();
}

//=============================================================================
// 状態の変更
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::ChangeState(CState *pPlayerState)
{
	m_pNextState = pPlayerState;
}

//=============================================================================
// 状態更新
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::UpdateState()
{
	if (m_pNextState)
	{
		delete m_pCurrentState;
		m_pCurrentState = nullptr;

		m_pCurrentState = m_pNextState;
		m_pNextState = nullptr;
	}

	if (m_pCurrentState)
	{
		// 更新処理
		m_pCurrentState->Update();
	}
}

//=============================================================================
// 更新処理
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::UpdateRot()
{
	// 角度の取得
	D3DXVECTOR3 rot = GetRot();

	while (m_rotDest.y - rot.y > D3DXToRadian(180))
	{
		m_rotDest.y -= D3DXToRadian(360);
	}

	while (m_rotDest.y - rot.y < D3DXToRadian(-180))
	{
		m_rotDest.y += D3DXToRadian(360);
	}

	// キャラクター回転の速度
	rot += (m_rotDest - rot) * m_fRotationSpeed;

	// 角度の更新処理
	CLibrary::RotFix(rot.y);

	// 角度の設定
	SetRot(rot);
}