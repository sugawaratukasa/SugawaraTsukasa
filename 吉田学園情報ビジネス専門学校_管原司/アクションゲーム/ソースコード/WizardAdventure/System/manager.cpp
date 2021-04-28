//******************************************************************************
// マネージャー処理 [manager.cpp]
// Author : 管原　司
//******************************************************************************

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "camera.h"
#include "light.h"
#include "input.h"
#include "keyboard.h"
#include "joystick.h"
#include "debug_proc.h"
#include "mode.h"
#include "title.h"
#include "game.h"
#include "../3D/Model/player.h"
#include "../3D/3DPolygon/frame.h"
#include "../3D/3DPolygon/floor.h"
#include "../3D/Model/Object/3d_obj.h"
#include "particle_texture.h"
#include "../3D/3DPolygon/3d_polygon.h"
#include "../3D/3DPolygon/Billboard/billboard_ui.h"
#include "../3D/Model/Enemy/enemy.h"
#include "ui_texture.h"
#include "result.h"
#include "tutorial.h"
#include "sound.h"
//******************************************************************************
// 静的メンバ変数
//******************************************************************************
CRenderer *CManager::m_pRenderer = NULL;
CCamera *CManager::m_pCamera = NULL;
CLight *CManager::m_pLight = NULL;
CInputKeyboard *CManager::m_pKeyboard = NULL;
CInputJoystick *CManager::m_pJoystick = NULL;
CDebugProc *CManager::m_pDebugProc = NULL;
CMode *CManager::m_pMode = NULL;
CParticle_Texture *CManager::m_pParticle_Texture = NULL;
CUI_Texture *CManager::m_pUI_Texture = NULL;
CManager::MODE CManager::m_Mode = MODE_NONE;
CSound *CManager::m_pSound = NULL;
//******************************************************************************
//コンストラクタ
//******************************************************************************
CManager::CManager()
{

}

//******************************************************************************
//デストラクタ
//******************************************************************************
CManager::~CManager()
{

}

//******************************************************************************
//初期化処理
//******************************************************************************
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindouw)
{

	//クラス生成と初期化	
	//レンダラー
	if (m_pRenderer == NULL)
	{
		// メモリ確保
		m_pRenderer = new CRenderer;
		if (m_pRenderer != NULL)
		{
			// 初期化
			m_pRenderer->Init(hWnd, TRUE);
		}
	}
	// キーボード
	if (m_pKeyboard == NULL)
	{
		// メモリ確保
		m_pKeyboard = new CInputKeyboard;
		if (m_pKeyboard != NULL)
		{
			// 初期化
			m_pKeyboard->Init(hInstance, hWnd);
		}
	}
	// コントローラー
	if (m_pJoystick == NULL)
	{
		// メモリ確保
		m_pJoystick = new CInputJoystick;
		if (m_pJoystick != NULL)
		{
			// 初期化
			m_pJoystick->Init(hInstance, hWnd);
		}
	}
	// デバッグ
	if (m_pDebugProc == NULL)
	{
		m_pDebugProc = new CDebugProc;
		if (m_pDebugProc != NULL)
		{
			m_pDebugProc->Init();
		}
	}
	// テクスチャ
	if (m_pParticle_Texture == NULL)
	{
		// メモリ確保
		m_pParticle_Texture = new CParticle_Texture;

		// NULLでない場合
		if (m_pParticle_Texture != NULL)
		{
			// 初期化
			m_pParticle_Texture->Init();
		}
	}
	// テクスチャ
	if (m_pUI_Texture == NULL)
	{
		// メモリ確保
		m_pUI_Texture = new CUI_Texture;

		// NULLでない場合
		if (m_pUI_Texture != NULL)
		{
			// 初期化
			m_pUI_Texture->Init();
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
	}
	
	//テクスチャの読み込み
	LoadAll();

	// モード設定
	SetMode(MODE_TITLE);
	return S_OK;
}

//******************************************************************************
//終了処理
//******************************************************************************
void CManager::Uninit(void)
{
	// 全破棄
	CScene::ReleaseAll();

	//テクスチャの破棄
	UnloadAll();

	//サウンド全停止
	m_pSound->StopSound();

	// テクスチャの終了
	if (m_pUI_Texture != NULL)
	{
		// 終了
		m_pUI_Texture->Uninit();

		// メモリ開放
		delete m_pUI_Texture;

		// NULLに
		m_pUI_Texture = NULL;
	}
	// テクスチャの終了
	if (m_pParticle_Texture != NULL)
	{
		// 終了
		m_pParticle_Texture->Uninit();

		// メモリ開放
		delete m_pParticle_Texture;

		// NULLに
		m_pParticle_Texture = NULL;
	}
	// モードの終了
	if (m_pMode != NULL)
	{
		//その時のモード終了
		m_pMode->Uninit();
	}
	// デバッグ
	if (m_pDebugProc != NULL)
	{
		m_pDebugProc->Uninit();
		delete m_pDebugProc;
		m_pDebugProc = NULL;
	}
	//キーボードの破棄
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard->Uninit();
		delete m_pKeyboard;
		m_pKeyboard = NULL;
	}
	//コントローラーの破棄
	if (m_pJoystick != NULL)
	{
		m_pJoystick->Uninit();
		delete m_pJoystick;
		m_pJoystick = NULL;
	}
	//ライトの終了
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}
	//カメラの終了
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}
	//レンダラーの終了
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
	// NULLでない場合
	if (m_pSound != NULL)
	{
		// サウンドの終了処理
		m_pSound->Uninit();

		// メモリ開放
		delete m_pSound;

		// NULLに
		m_pSound = NULL;
	}
}

//******************************************************************************
// 更新処理
//******************************************************************************
void CManager::Update(void)
{
	// NULLでない場合
	if (m_pRenderer != NULL)
	{
		//レンダラーの更新処理
		m_pRenderer->Update();
	}
	// NULLでない場合
	if (m_pCamera != NULL)
	{
		//カメラのの更新処理
		m_pCamera->Update();
	}
	// NULLでない場合
	if (m_pMode != NULL)
	{
		// その時のモードの描画処理
		m_pMode->Update();
	}
	// NULLでない場合
	if (m_pKeyboard != NULL)
	{
		//キーボードの更新
		m_pKeyboard->Update();
	}
	// NULLでない場合
	if (m_pJoystick != NULL)
	{
		// コントローラーの更新
		m_pJoystick->Update();
	}
}

//******************************************************************************
// 描画処理
//******************************************************************************
void CManager::Draw(void)
{
	// NULLでない場合
	if (m_pRenderer != NULL)
	{
		//描画処理
		m_pRenderer->Draw();
	}
	// NULLでない場合
	if (m_pMode != NULL)
	{
		// その時のモードの描画処理
		m_pMode->Draw();
	}
}

//******************************************************************************
// テクスチャの読み込みまとめ
//******************************************************************************
void CManager::LoadAll(void)
{
	// プレイヤーモデル読み込み
	CPlayer::Load();

	// フレーム
	CFrame::Load();

	// 床
	CFloor::Load();

	// 3Dオブジェクト
	C3D_Obj::Load();

	// 3dポリゴン
	C3D_Polygon::Load();

	// ビルボードUI
	CBillboard_UI::Load();

	// 敵
	CEnemy::Load();
}

//******************************************************************************
// テクスチャの破棄まとめ
//******************************************************************************
void CManager::UnloadAll(void)
{
	// 敵
	CEnemy::Unload();

	// ビルボードUI
	CBillboard_UI::Unload();

	// 3dポリゴン
	C3D_Polygon::Unload();

	// 3Dオブジェクト
	C3D_Obj::Unload();

	// 床
	CFloor::Unload();

	// フレーム
	CFrame::Unload();

	// プレイヤーモデル破棄
	CPlayer::Unload();
}

//******************************************************************************
// カメラの生成
//******************************************************************************
void CManager::CreateCamera(void)
{
	// NULLの場合
	if (m_pCamera == NULL)
	{
		// ポインタの動的確保
		m_pCamera = new CCamera;

		if (m_pCamera != NULL)
		{
			// 初期化
			m_pCamera->Init();
		}
	}
}

//******************************************************************************
// ライトの生成
//******************************************************************************
void CManager::CreateLight(void)
{
	if (m_pLight == NULL)
	{
		// ポインタの動的確保
		m_pLight = new CLight;
		if (m_pLight != NULL)
		{
			// 初期化
			m_pLight->Init();
		}
	}
}
//******************************************************************************
// モードの設定
//******************************************************************************
void CManager::SetMode(MODE mode)
{
	if (m_pMode != NULL)
	{
		// その時のモードの終了処理
		m_pMode->Uninit();
		delete m_pMode;
		m_pMode = NULL;
	}

	if (m_pMode == NULL)
	{
		// 代入
		m_Mode = mode;

		switch (m_Mode)
		{
			// タイトル
		case MODE_TITLE:

			// ツールの生成
			m_pMode = new CTitle;

			// ツールの初期化処理
			m_pMode->Init();
			break;
		case MODE_TUTORIAL:
			// NULLでない場合
			if (m_pCamera != NULL)
			{
				// 終了
				m_pCamera->Uninit();

				// 破棄
				delete m_pCamera;

				// NULLに
				m_pCamera = NULL;
			}
			// ツールの生成
			m_pMode = new CTutorial;

			// ツールの初期化処理
			m_pMode->Init();
			break;
			// ゲーム
		case MODE_GAME:

			// NULLでない場合
			if (m_pCamera != NULL)
			{
				// 終了
				m_pCamera->Uninit();

				// 破棄
				delete m_pCamera;

				// NULLに
				m_pCamera = NULL;
			}
			// ツールの生成
			m_pMode = new CGame;

			// ツールの初期化処理
			m_pMode->Init();
			break;
			// タイトル
		case MODE_RESULT:

			// ツールの生成
			m_pMode = new CResult;

			// ツールの初期化処理
			m_pMode->Init();
			break;
		default:
			return;
			break;
		}
	}
}