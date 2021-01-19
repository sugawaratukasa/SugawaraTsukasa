//******************************************************************************
// manager [manager.cpp]
// Author : 管原　司
//******************************************************************************

//*****************************************************************************
// ファイルのインクルード
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
#include "boss.h"
#include "warning.h"
#include "tutrial.h"
#include "ship.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODE_SIZE (D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT,0.0f))
//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
CRenderer * CSceneManager::m_pRenderer = NULL;
CInputKeyboard * CSceneManager::m_pInputKeyboard = NULL;
CInputJoystick * CSceneManager::m_pInputJoystick = NULL;
CSound * CSceneManager::m_pSound = NULL;
CTitle * CSceneManager::m_pTitle = NULL;
CTutrial * CSceneManager::m_pTutrial = NULL;
CGame * CSceneManager::m_pGame = NULL;
CResult * CSceneManager::m_pResult = NULL;
CFade * CSceneManager::m_pFade = NULL;
CSceneManager::MODE CSceneManager::m_mode = MODE_NONE;
bool CSceneManager::m_bUseFade = false;
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
		m_pRenderer = new  CRenderer;
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

	// NULLでない場合
	if (m_pFade == NULL)
	{
		// フェード生成
		m_pFade = CFade::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), FADE_SIZE, m_mode);
	}
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
	if (m_pSound != NULL)
	{
		// サウンドの終了処理
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}
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
	if (m_pFade != NULL)
	{
		// フェード終了
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = NULL;
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
	// m_bUseFadeがtrueの場合
	if (m_bUseFade == true)
	{
		// NULLでない場合
		if (m_pFade != NULL)
		{
			// フェード更新
			m_pFade->Update();
		}
	}
}

//******************************************************************************
// 描画関数
//******************************************************************************
void CSceneManager::Draw(void)
{
	//描画処理
	m_pRenderer->Draw(); 
}
//******************************************************************************
// モード設定
//******************************************************************************
void CSceneManager::SetMode(MODE mode)
{
	// mode代入
	m_mode = mode;

	// 全終了
	CScene::ReleaseAll();

	switch (m_mode)
	{
		// タイトル
	case MODE_TITLE:
		m_pTitle = CTitle::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), MODE_SIZE);
		break;
		// チュートリアル
	case MODE_TUTRIAL:
		m_pTutrial = CTutrial::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), MODE_SIZE);
		break;
		// ゲーム
	case MODE_GAME:
		m_pGame = CGame::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), MODE_SIZE);
		break;
		// リザルト
	case MODE_RESULT:
		m_pResult = CResult::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), MODE_SIZE);
		break;
		// その他の場合
	default:
		break;
		return;
	}
	// キーボード更新
	m_pInputJoystick->Update();
}
//******************************************************************************
// フェード開始
//******************************************************************************
void CSceneManager::StartFade(MODE mode)
{
	// modeを代入
	m_mode = mode;
	// trueに
	m_bUseFade = true;
}
//******************************************************************************
// フェード停止
//******************************************************************************
void CSceneManager::StopFade(void)
{
	// falseに
	m_bUseFade = false;
}
//******************************************************************************
// テクスチャ全読み込み関数
//******************************************************************************
void CSceneManager::LoadAll(void)
{
	// タイトル
	CTitle::Load();
	// リザルト
	CResult::Load();
	// 背景
	CBg::Load();
	// ライフ
	CLife::Load();
	// 自機
	CPlayer::Load();
	// 敵
	CEnemy::Load();
	// 弾
	CBullet::Load();
	// 爆発
	CExplosion::Load();
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
	// warning
	CWarning::Load();
	// チュートリアル
	CTutrial::Load();
}
//******************************************************************************
// テクスチャ全破棄関数
//******************************************************************************
void CSceneManager::UnloadAll(void)
{
	// テクスチャ破棄
	// チュートリアル
	CTutrial::Unload();
	// warning
	CWarning::Unload();
	// ボス
	CBoss::Unload();
	// Ship
	CShip::Unload();
	// ボム
	CBomUI::Unload();
	// アイテム
	CItem::Unload();
	// ナンバー
	CNumber::Unload();
	// 爆発
	CExplosion::Unload();
	// 弾
	CBullet::Unload();
	// 敵
	CEnemy::Unload();
	// 自機
	CPlayer::Unload();
	// ライフ
	CLife::Unload();
	// 背景
	CBg::Unload();
	// Result
	CResult::Unload();
	// タイトル
	CTitle::Unload();
}