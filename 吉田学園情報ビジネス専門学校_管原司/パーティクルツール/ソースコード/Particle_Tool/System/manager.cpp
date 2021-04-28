//***********************************************************************************
// マネージャー処理 [manager.cpp]
// Author : 管原　司
//***********************************************************************************

//***********************************************************************************
//インクルードファイル
//***********************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "camera.h"
#include "mode.h"
#include "tool.h"
#include "texture.h"
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include <d3d9.h>
#include <dinput.h>
#include <tchar.h>

//***********************************************************************************
//スタティック変数初期化
//***********************************************************************************
CRenderer *CManager::m_pRenderer = NULL;
CCamera *CManager::m_pCamera	 = NULL;
CMode *CManager::m_pMode		 = NULL;
CTexture *CManager::m_pTexture	 = NULL;
//***********************************************************************************
//コンストラクタ
//***********************************************************************************
CManager::CManager()
{

}

//***********************************************************************************
//デストラクタ
//***********************************************************************************
CManager::~CManager()
{

}

//***********************************************************************************
//初期化処理
//***********************************************************************************
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindouw)
{
	// NULLの場合
	if (m_pRenderer == NULL)
	{
		// メモリ確保
		m_pRenderer = new CRenderer;

		// NULLでない場合
		if (m_pRenderer != NULL)
		{
			// 初期化
			m_pRenderer->Init(hWnd, TRUE);
		}
	}
	// NULLの場合
	if (m_pTexture == NULL)
	{
		// メモリ確保
		m_pTexture = new CTexture;

		// NULLでない場合
		if (m_pTexture != NULL)
		{
			// 初期化
			m_pTexture->Init();
		}
	}

	// バージョンチェック
	IMGUI_CHECKVERSION();

	// コンテキスト生成
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// 色設定
	ImGui::StyleColorsDark();

	// 初期化
	ImGui_ImplWin32_Init(hWnd);

	// 初期化
	ImGui_ImplDX9_Init(GetRenderer()->GetDevice());

	// フォント設定
	ImFont* font = io.Fonts->AddFontFromFileTTF("C://Windows//Fonts//MEIRYO.TTC", 20.0f, NULL, io.Fonts->GetGlyphRangesJapanese());

	IM_ASSERT(font != NULL);

	// モード設定
	SetMode(MODE_TOOL);
	return S_OK;
}

//***********************************************************************************
//終了処理
//***********************************************************************************
void CManager::Uninit(void)
{
	CScene::ReleaseAll();

	// テクスチャの終了
	if (m_pTexture != NULL)
	{
		// 終了
		m_pTexture->Uninit();

		// メモリ開放
		delete m_pTexture;

		// NULLに
		m_pTexture = NULL;
	}
	// モードの終了
	if (m_pMode != NULL)
	{
		//その時のモード終了
		m_pMode->Uninit();

		// メモリ開放
		delete m_pMode;

		// NULLに
		m_pMode = NULL;
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
	// 終了
	ImGui_ImplDX9_Shutdown();

	// 終了
	ImGui_ImplWin32_Shutdown();

	// コンテキスト破棄
	ImGui::DestroyContext();
}

//***********************************************************************************
// 更新処理
//***********************************************************************************
void CManager::Update(void)
{
	// NULLでない場合
	if (m_pRenderer != NULL)
	{
#ifdef _DEBUG
		// FPSのセット
		m_pRenderer->SetNumFPS(m_nCountFPS);
#endif
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
}

//***********************************************************************************
// 描画処理
//***********************************************************************************
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

//***********************************************************************************
//テクスチャの読み込みまとめ
//***********************************************************************************
void CManager::LoadAll(void)
{

}

//***********************************************************************************
//テクスチャの破棄まとめ
//***********************************************************************************
void CManager::UnloadAll(void)
{

}

//***********************************************************************************
//カメラの生成
//***********************************************************************************
void CManager::CreateCamera(void)
{
	// NULLの場合
	if (m_pCamera == NULL)
	{
		// メモリ確保
		m_pCamera = new CCamera;

		// NULLでない場合
		if (m_pCamera != NULL)
		{
			// 初期化
			m_pCamera->Init();
		}
	}
}
//***********************************************************************************
// モードの設定
//***********************************************************************************
void CManager::SetMode(MODE mode)
{
	// NULLでない場合
	if (m_pMode != NULL)
	{
		// その時のモードの終了処理
		m_pMode->Uninit();

		// 破棄
		delete m_pMode;

		// NULLに
		m_pMode = NULL;
	}
	// NULLの場合
	if (m_pMode == NULL)
	{
		// 代入
		m_Mode = mode;

		switch (m_Mode)
		{
		case MODE_TOOL:
			// ツールの生成
			m_pMode = new CTool;

			// ツールの初期化処理
			m_pMode->Init();

			break;

		default:
			return;
			break;
		}
	}
}