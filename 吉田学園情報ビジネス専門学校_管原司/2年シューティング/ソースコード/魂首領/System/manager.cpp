//******************************************************************************
// manager [manager.cpp]
// Author : 管原　司
//******************************************************************************

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "../Input/input.h"
#include "../Input/inputkeyboard.h"
#include "../Input/inputjoystick.h"
#include "../Player/player.h"
#include "../Player/player_wepon.h"
#include "../Bullet/bullet.h"
#include "../Polygon/bg.h"
#include "sound.h"
#include "../Enemy/enemy.h"
#include "number.h"
#include "../UI/score.h"
#include "../UI/life.h"
#include "../Mode/mode.h"
#include "../Polygon/fade.h"
#include "../Polygon/item.h"
#include "../UI/bomui.h"
#include "../Polygon/polygon.h"
#include "../Boss/boss.h"
#include "../Boss/boss_left.h"
#include "../Boss/boss_right.h"
#include "../Mode/tutrial.h"
#include "../Enemy/ship.h"
#include "../Particle/particle.h"
#include "../Mode/title.h"
#include "../Mode/game.h"
#include "../Mode/result.h"
#include "../Beam/beam.h"
#include "../UI/warning.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODE_SIZE (D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT,0.0f))	// 
#define MAX_NUMBER (9)													// ナンバー最大数
//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
CRenderer * CSceneManager::m_pRenderer				= NULL;
CInputKeyboard * CSceneManager::m_pInputKeyboard	= NULL;
CInputJoystick * CSceneManager::m_pInputJoystick	= NULL;
CSound * CSceneManager::m_pSound					= NULL;
CMode *CSceneManager::m_pMode						= NULL;
CSceneManager::MODE CSceneManager::m_mode			= MODE_NONE;
//******************************************************************************
// コンストラクタ
//******************************************************************************
CSceneManager::CSceneManager()
{
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CSceneManager::~CSceneManager()
{
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CSceneManager::Init(HINSTANCE hInsitance, HWND hWnd, bool bWindow)
{
	// レンダラーの生成
	if (m_pRenderer == NULL)
	{
		// メモリ確保
		m_pRenderer = new CRenderer;

		// NULLでない場合
		if (m_pRenderer != NULL)
		{
			// レンダラー初期化処理
			m_pRenderer->Init(hWnd, TRUE);
		}
		// NULLの場合
		else
		{
			return 0;
		}
	}
	// キーボード生成
	if (m_pInputKeyboard == NULL)
	{
		// メモリ確保
		m_pInputKeyboard = new CInputKeyboard;
		// NULLでないとき
		if (m_pInputKeyboard != NULL)
		{
			// キーボード初期化処理
			m_pInputKeyboard->Init(hInsitance, hWnd);
		}
		// NULLの場合
		else
		{
			return 0;
		}
	}
	// コントローラー生成
	if (m_pInputJoystick == NULL)
	{
		// メモリ確保
		m_pInputJoystick = new CInputJoystick;
		// NULLでないとき
		if (m_pInputJoystick != NULL)
		{
			// コントローラー初期化処理
			m_pInputJoystick->Init(hInsitance, hWnd);
		}
		// NULLの場合
		else
		{
			return 0;
		}
	}
	//サウンド生成
	if (m_pSound == NULL)
	{
		// メモり確保
		m_pSound = new CSound;

		// NULLでないとき
		if (m_pSound != NULL)
		{
			// サウンド初期化処理
			m_pSound->Init(hWnd);
		}
		// NULLの場合
		else
		{
			return 0;
		}
	}

	// テクスチャ全読み込み
	LoadAll();

	// タイトルに設定
	SetMode(MODE_TITLE);

	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CSceneManager::Uninit(void)
{
	//全てのオブジェクトを破棄
	CScene::ReleaseAll();
	// テクスチャ全読み込み
	UnloadAll();
	//サウンド全停止
	m_pSound->StopSound();

	// NULLでない場合
	if (m_pInputJoystick != NULL)
	{
		// コントローラーの終了処理
		m_pInputJoystick->Uninit();
		delete m_pInputJoystick;
		m_pInputJoystick = NULL;
	}
	// NULLでない場合
	if (m_pInputKeyboard != NULL)
	{
		// キーボードの終了処理
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}
	// NULLでない場合
	if (m_pRenderer != NULL)
	{
		// レンダラーの終了処理
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
	// NULLでない場合
	if (m_pMode != NULL)
	{
		// モード終了
		m_pMode->Uninit();
	}

	// NULLでない場合
	if (m_pSound != NULL)
	{
		// サウンドの終了処理
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}
}

//******************************************************************************
// 更新関数
//******************************************************************************
void CSceneManager::Update(void)
{
	// NULLでない場合
	if (m_pRenderer != NULL)
	{
		// レンダラー更新
		m_pRenderer->Update();
	}
	// NULLでない場合
	if (m_pInputKeyboard != NULL)
	{
		// キーボード更新
		m_pInputKeyboard->Update();
	}
	// NULLでない場合
	if (m_pInputJoystick != NULL)
	{
		// コントローラー更新
		m_pInputJoystick->Update();
	}
	// NULLでない場合
	if (m_pMode != NULL)
	{
		// モード更新
		m_pMode->Update();
	}
}

//******************************************************************************
// 描画関数
//******************************************************************************
void CSceneManager::Draw(void)
{
	// NULLでない場合
	if (m_pRenderer != NULL)
	{
		//描画処理
		m_pRenderer->Draw();
	}
	if (m_pMode != NULL)
	{
		// モード描画処理
		m_pMode->Draw();
	}
}
//******************************************************************************
// モード設定
//******************************************************************************
void CSceneManager::SetMode(MODE mode)
{
	// NULLでない場合
	if (m_pMode != NULL)
	{
		// その時のモードの終了処理
		m_pMode->Uninit();
		// メモリ破棄
		delete m_pMode;
		// NULLに
		m_pMode = NULL;
	}
	// NULLの場合
	if (m_pMode == NULL)
	{
		m_mode = mode;

		switch (m_mode)
		{
		case MODE_TITLE:

			// タイトルの生成
			m_pMode = new CTitle;

			// タイトルの初期化処理
			m_pMode->Init();

			break;

		case MODE_GAME:
			// ゲームの生成
			m_pMode = new CGame;

			// ゲームの初期化処理
			m_pMode->Init();

			break;

		case MODE_TUTRIAL:

			// チュートリアルの生成
			m_pMode = new CTutrial;

			// チュートリアルの初期化処理
			m_pMode->Init();

			break;

		case MODE_RESULT:

			// クリア画面の生成
			m_pMode = new CResult;

			// クリア画面の初期化処理
			m_pMode->Init();

			break;
		}
	}
	// キーボード更新
	m_pInputJoystick->Update();
}
//******************************************************************************
// テクスチャ全読み込み関数
//******************************************************************************
void CSceneManager::LoadAll(void)
{
	// 背景
	CBg::Load();
	// ライフ
	CLife::Load();
	// 自機
	CPlayer::Load();
	// プレイヤーの武器
	CPlayer_Wepon::Load();
	// 敵
	CEnemy::Load();
	// 弾
	CBullet::Load();
	// ナンバー
	CNumber::Load();
	// アイテム
	CItem::Load();
	// ボム
	CBomUI::Load();
	// Ship
	CShip::Load();
	// ボス
	CBoss::Load();
	// ボスの左
	CBoss_Left::Load();
	// ボスの右
	CBoss_Right::Load();
	// warning
	CWarning::Load();
	// パーティクル
	CParticle::Load();
	// ポリゴン
	CPolygon::Load();
	// ビーム
	CBeam::Load();
}
//******************************************************************************
// テクスチャ全破棄関数
//******************************************************************************
void CSceneManager::UnloadAll(void)
{
	// テクスチャ破棄
	// ビーム
	CBeam::Unload();
	// ポリゴン
	CPolygon::Unload();
	// パーティクル
	CParticle::Unload();
	// warning
	CWarning::Unload();
	// ボス
	CBoss::Unload();
	// ボスの左
	CBoss_Left::Unload();
	// ボスの右
	CBoss_Right::Unload();
	// Ship
	CShip::Unload();
	// ボム
	CBomUI::Unload();
	// アイテム
	CItem::Unload();
	// ナンバー
	CNumber::Unload();
	// 弾
	CBullet::Unload();
	// 敵
	CEnemy::Unload();
	// 自機
	CPlayer::Unload();
	// プレイヤーの武器
	CPlayer_Wepon::Unload();
	// ライフ
	CLife::Unload();
	// 背景
	CBg::Unload();
}