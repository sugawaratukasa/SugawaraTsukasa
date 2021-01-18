//=============================================================================
//
// Manager 
// manager.cpp
// Author : 管原司
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "input.h"
#include "inputkeyboard.h"
#include "inputjoystick.h"
#include "player.h"
#include "bullet.h"
#include "bg.h"
#include "explosion.h"
#include "sound.h"
#include "enemy.h"
#include "number.h"
#include "score.h"
#include "life.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "item.h"
#include "bomui.h"
#include "polygon.h"
#include "ship.h"
#include "boss.h"
#include "warning.h"
#include "tutrial.h"
//*****************************************************************************
// グローバル変数:
//*****************************************************************************
CRenderer * CSceneManager::m_pRenderer = NULL;
CInputKeyboard * CSceneManager::m_pInputKeyboard = NULL;
CInputJoystick * CSceneManager::m_pInputJoystick = NULL;
CSound * CSceneManager::m_pSound = NULL;
CBullet * CSceneManager::m_pBullet = NULL;
CTitle * CSceneManager::m_pTitle = NULL;
CTutrial * CSceneManager::m_pTutrial = NULL;
CGame * CSceneManager::m_pGame = NULL;
CResult * CSceneManager::m_pResult = NULL;
CFade * CSceneManager::m_pFade = NULL;
CSceneManager::MODE CSceneManager::m_mode = MODE_NONE;
bool CSceneManager::m_bUseFade = false;
//=============================================================================
// コンストラクタ
//=============================================================================
CSceneManager::CSceneManager()
{
}
//=============================================================================
// デストラクタ
//=============================================================================
CSceneManager::~CSceneManager()
{
}
//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CSceneManager::Init(HINSTANCE hInsitance, HWND hWnd, bool bWindow)
{
	//レンダラーの生成
	if (m_pRenderer == NULL)
	{
		//メモリ確保
		m_pRenderer = new  CRenderer;
		//NULLでないとき
		if (m_pRenderer != NULL)
		{
			m_pRenderer->Init(hWnd, TRUE);
		}
		//NULLの場合
		else
		{
			return 0;
		}
	}
	//キーボード生成
	if (m_pInputKeyboard == NULL)
	{
		//メモリ確保
		m_pInputKeyboard = new CInputKeyboard;
		//NULLでないとき
		if (m_pInputKeyboard != NULL)
		{
			m_pInputKeyboard->Init(hInsitance, hWnd);
		}
		//NULLの場合
		else
		{
			return 0;
		}
	}
	//コントローラー生成
	if (m_pInputJoystick == NULL)
	{
		//メモリ確保
		m_pInputJoystick = new CInputJoystick;
		//NULLでないとき
		if (m_pInputJoystick != NULL)
		{
			m_pInputJoystick->Init(hInsitance, hWnd);
		}
		//NULLの場合
		else
		{
			return 0;
		}
	}
	//サウンド生成
	if (m_pSound == NULL)
	{
		//メモり確保
		m_pSound = new CSound;
		//NULLでないとき
		if (m_pSound != NULL)
		{
			m_pSound->Init(hWnd);
		}
		//NULLの場合
		else
		{
			return 0;
		}
	}
	//テクスチャロード
	CTitle::Load();
	//Result
	CResult::Load();
	//背景
	CBg::Load();
	//ライフ
	CLife::Load();
	//自機
	CPlayer::Load();
	//敵
	CEnemy::Load();
	//弾
	CBullet::Load();
	//爆発
	CExplosion::Load();
	//ナンバー
	CNumber::Load();
	//アイテム
	CItem::Load();
	//ボム
	CBom::Load();
	//Ship
	CShip::Load();
	//ボス
	CBoss::Load();
	//warning
	CWarning::Load();
	//チュートリアル
	CTutrial::Load();
	//セットタイトル
	SetMode(MODE_TITLE);
	if (m_pFade == NULL)
	{
		//フェード生成
		m_pFade = CFade::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, m_mode);
	}
	return S_OK;
}
//=============================================================================
// 終了関数
//=============================================================================
void CSceneManager::Uninit(void)
{
	//全てのオブジェクトのRelease
	//テクスチャ破棄
	//エフェクト
	CScene::ReleaseAll();
	//チュートリアル
	CTutrial::Unload();
	//warning
	CWarning::Unload();
	//ボス
	CBoss::Unload();
	//Ship
	CShip::Unload();
	//ボム
	CBom::Unload();
	//アイテム
	CItem::Unload();
	//ナンバー
	CNumber::Unload();
	//爆発
	CExplosion::Unload();
	//弾
	CBullet::Unload();
	//敵
	CEnemy::Unload();
	//自機
	CPlayer::Unload();
	//ライフ
	CLife::Unload();
	//背景
	CBg::Unload();
	//Result
	CResult::Unload();
	//タイトル
	CTitle::Unload();
	//サウンド破棄
	m_pSound->StopSound();
	//サウンドの終了処理
	if (m_pSound != NULL)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}
	//コントローラーの終了処理
	if (m_pInputJoystick != NULL)
	{
		m_pInputJoystick->Uninit();
		delete m_pInputJoystick;
		m_pInputJoystick = NULL;
	}
	//キーボードの終了処理
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}
	//レンダラーの終了処理
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
	//フェード終了
	if (m_pFade != NULL)
	{
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = NULL;
	}
}

//=============================================================================
// 更新関数
//=============================================================================
void CSceneManager::Update(void)
{
	//レンダラー更新
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();	// 更新処理
	}
	//キーボード更新
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}
	//キーボード更新
	if (m_pInputJoystick != NULL)
	{
		m_pInputJoystick->Update();
	}
	//フェード更新
	if (m_bUseFade == true)
	{
		if (m_pFade != NULL)
		{
			m_pFade->Update();
		}
	}
}

//=============================================================================
// 描画関数
//=============================================================================
void CSceneManager::Draw(void)
{
	//描画処理
	m_pRenderer->Draw(); 
}
//----------------------------------------------------------------------------
//モードのセット
//----------------------------------------------------------------------------
void CSceneManager::SetMode(MODE mode)
{
	m_mode = mode;
	CScene::ReleaseAll();
	switch (m_mode)
	{
		//Title
	case MODE_TITLE:
		m_pTitle = CTitle::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT);
		break;
	case MODE_TUTRIAL:
		m_pTutrial = CTutrial::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT);
		break;
		//Game
	case MODE_GAME:
		m_pGame = CGame::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH , SCREEN_HEIGHT);
		break;
		//Result
	case MODE_RESULT:
		m_pResult = CResult::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH / 2 , SCREEN_HEIGHT);
		break;
	default:
		break;
		return;
	}
	m_pInputJoystick->Update();
}
//----------------------------------------------------
//フェードの開始
//----------------------------------------------------
void CSceneManager::StartFade(MODE mode)
{
	m_mode = mode;
	m_bUseFade = true;
}
//----------------------------------------------------
//
//----------------------------------------------------
void CSceneManager::StopFade(void)
{
	m_bUseFade = false;
}
