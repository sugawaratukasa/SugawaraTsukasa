//******************************************************************************
// チュートリアルポーズ [tutorial_pause.cpp]
// Author : 管原司
//******************************************************************************
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "joystick.h"
#include "2d_polygon.h"
#include "fade.h"
#include "mode.h"
#include "sound.h"
#include "tutorial.h"
#include "tutorial_pause.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define BLACK_POLYGON_POS	(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f))								// 位置
#define BLACK_POLYGON_SIZE	(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f))										// サイズ
#define SIZE				(D3DXVECTOR3(750.0f, 500.0f, 0.0f))														// サイズ
#define GAME_SIZE			(D3DXVECTOR3(600.0f,500.0f, 0.0f))														// サイズ
#define RESUME_POS			(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - SIZE.y + 70.0f, 0.0f))				// 位置
#define CONTROLS_POS		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - SIZE.y / 2 + 70.0f, 0.0f))			// 位置
#define GAMESTART_POS		(D3DXVECTOR3(SCREEN_WIDTH / 2 + 15.0f, SCREEN_HEIGHT / 2 + SIZE.y / 2 -130.0f, 0.0f))	// 位置
#define EXIT_POS			(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + SIZE.y - 130.0f, 0.0f))				// 位置
#define DEAD_ZONE_MIN		(0)																						// スティックのデッドゾーン最小値
#define COL					(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))														// 色
#define BLACK_COL			(D3DXCOLOR(0.5f,0.5f,0.5f,1.0f))														// 色
//******************************************************************************
// コンストラクタ
//******************************************************************************
CTutorial_Pause::CTutorial_Pause(int nPriority) : CScene(nPriority)
{
	memset(m_apPolygon, NULL, sizeof(m_apPolygon));
	m_nCount	= INIT_INT;
	m_bStick	= false;
	m_bControls = false;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CTutorial_Pause::~CTutorial_Pause()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CTutorial_Pause * CTutorial_Pause::Create(void)
{
	// CPauseのポインタ
	CTutorial_Pause *pPause = NULL;

	// NULLの場合
	if (pPause == NULL)
	{
		// メモリ確保
		pPause = new CTutorial_Pause;

		// NULLでない場合
		if (pPause != NULL)
		{
			// オブジェクトタイプ設定
			pPause->SetObjType(OBJTYPE_NOSTOP_UI);

			// 初期化
			pPause->Init();
		}
	}
	// ポインタを返す
	return pPause;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CTutorial_Pause::Init(void)
{
	// RESUMEに
	m_nCount = TYPE_RESUME;

	// 黒ポリ生成
	m_apPolygon[TYPE_BLACK] = C2D_Polygon::Create(BLACK_POLYGON_POS, BLACK_POLYGON_SIZE, C2D_Polygon::TYPE_NONE);

	// RESUME生成
	m_apPolygon[TYPE_RESUME] = C2D_Polygon::Create(RESUME_POS, SIZE, C2D_Polygon::TYPE_RESUME);

	// TYPE_CONTROLS生成
	m_apPolygon[TYPE_CONTROLS] = C2D_Polygon::Create(CONTROLS_POS, SIZE, C2D_Polygon::TYPE_CONTROLS);

	// TYPE_CONTROLS生成
	m_apPolygon[TYPE_GAMESTART] = C2D_Polygon::Create(GAMESTART_POS, GAME_SIZE, C2D_Polygon::TYPE_GAMESTART);

	// TYPE_EXIT生成
	m_apPolygon[TYPE_EXIT] = C2D_Polygon::Create(EXIT_POS, SIZE, C2D_Polygon::TYPE_EXIT);

	// 更新停止
	SetUpdateStop(true);
	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CTutorial_Pause::Uninit(void)
{
	// 破棄
	CScene::Release();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CTutorial_Pause::Update(void)
{
	// 選択
	Select();
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CTutorial_Pause::Draw(void)
{
}
//******************************************************************************
// 選択関数
//******************************************************************************
void CTutorial_Pause::Select(void)
{
	//サウンド取得
	CSound * pSound = CManager::GetSound();

	// コントローラー取得
	DIJOYSTATE js;
	js.lY = INIT_INT;
	js.lX = INIT_INT;
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();


	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	if (g_lpDIDevice != NULL)
	{
		// falseでない場合
		if (m_bControls == false)
		{
			// falseの場合
			if (m_bStick == false)
			{
				// 左スティックを上に倒す場合
				if (js.lY >= STICK_REACTION)
				{
					// trueに
					m_bStick = true;

					// EXITの場合
					if (m_nCount == TYPE_EXIT)
					{
						// 更新
						pInputJoystick->Update();

						// EXITに
						m_nCount = TYPE_EXIT;
					}
					// EXITでない場合
					if (m_nCount != TYPE_EXIT)
					{
						// 選択音再生
						pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);

						// インクリメント
						m_nCount++;
					}
				}
				// 左スティックを下に倒す場合
				if (js.lY <= -STICK_REACTION)
				{
					// RESUMEの場合
					if (m_nCount == TYPE_RESUME)
					{
						// EXITに
						m_nCount = TYPE_RESUME;
					}
					// RESUMEでない場合
					if (m_nCount != TYPE_RESUME)
					{
						// 選択音再生
						pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);

						// デクリメント
						m_nCount--;
					}
					// trueに
					m_bStick = true;
				}
			}
			// trueの場合
			if (m_bStick == true)
			{
				// -500より大きく0より小さい場合
				if (js.lY > -STICK_REACTION && js.lY <= DEAD_ZONE_MIN)
				{
					m_bStick = false;
				}
				// 500より小さく0より大きい場合
				if (js.lY < STICK_REACTION && js.lY >= DEAD_ZONE_MIN)
				{
					m_bStick = false;
				}
			}
			// RESUMEの場合
			if (m_nCount == TYPE_RESUME)
			{
				// 色設定
				m_apPolygon[m_nCount]->SetColor(COL);
				m_apPolygon[TYPE_CONTROLS]->SetColor(BLACK_COL);
				m_apPolygon[TYPE_GAMESTART]->SetColor(BLACK_COL);
				m_apPolygon[TYPE_EXIT]->SetColor(BLACK_COL);

				// Aボタンを押した場合
				if (pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_A))
				{
					// 決定音再生
					pSound->PlaySound(CSound::SOUND_LABEL_SE_DETERMINATION);

					// 更新開始
					SetUpdateStop(false);

					// 破棄
					CTutorial_Pause::Release();
				}
			}
			// CONTROLSの場合
			if (m_nCount == TYPE_CONTROLS)
			{
				// 色設定
				m_apPolygon[m_nCount]->SetColor(COL);
				m_apPolygon[TYPE_RESUME]->SetColor(BLACK_COL);
				m_apPolygon[TYPE_GAMESTART]->SetColor(BLACK_COL);
				m_apPolygon[TYPE_EXIT]->SetColor(BLACK_COL);

				// Aボタンを押した場合
				if (pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_A))
				{
					// 決定音再生
					pSound->PlaySound(CSound::SOUND_LABEL_SE_DETERMINATION);

					// 生成
					C2D_Polygon::Create(BLACK_POLYGON_POS, BLACK_POLYGON_SIZE, C2D_Polygon::TYPE_CONTROLS_BG);

					// trueに
					m_bControls = true;
				}
			}
			// RESUMEの場合
			if (m_nCount == TYPE_GAMESTART)
			{
				// 色設定
				m_apPolygon[m_nCount]->SetColor(COL);
				m_apPolygon[TYPE_RESUME]->SetColor(BLACK_COL);
				m_apPolygon[TYPE_CONTROLS]->SetColor(BLACK_COL);
				m_apPolygon[TYPE_EXIT]->SetColor(BLACK_COL);

				// Aボタンを押した場合
				if (pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_A))
				{
					// 決定音再生
					pSound->PlaySound(CSound::SOUND_LABEL_SE_DETERMINATION);

					// 更新開始
					SetUpdateStop(false);

					// フェード生成
					CFade::Create(CManager::MODE_GAME);
				}
			}
			// RESUMEの場合
			if (m_nCount == TYPE_EXIT)
			{
				// 色設定
				m_apPolygon[m_nCount]->SetColor(COL);
				m_apPolygon[TYPE_RESUME]->SetColor(BLACK_COL);
				m_apPolygon[TYPE_CONTROLS]->SetColor(BLACK_COL);
				m_apPolygon[TYPE_GAMESTART]->SetColor(BLACK_COL);

				// Aボタンを押した場合
				if (pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_A))
				{
					// 決定音再生
					pSound->PlaySound(CSound::SOUND_LABEL_SE_DETERMINATION);

					// 更新開始
					SetUpdateStop(false);

					// フェード生成
					CFade::Create(CManager::MODE_TITLE);
				}
			}
			// Bが押された場合
			if (pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_B))
			{
				// 決定音再生
				pSound->PlaySound(CSound::SOUND_LABEL_SE_DETERMINATION);

				// 更新開始
				SetUpdateStop(false);

				// 更新
				pInputJoystick->Update();

				// 破棄
				CTutorial_Pause::Release();
			}
		}
		// trueの場合
		if (m_bControls == true)
		{
			// B,START,Aボタンを押した場合
			if (pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_B))
			{
				// 決定音再生
				pSound->PlaySound(CSound::SOUND_LABEL_SE_DETERMINATION);

				// falseに
				m_bControls = false;
			}
		}
		// STARTが押された場合
		if (pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_START))
		{
			// trueの場合
			if (m_bControls == true)
			{
				// falseに
				m_bControls = false;
			}
			// falseの場合
			if (m_bControls == false)
			{
				// 更新
				pInputJoystick->Update();
			}
			// 決定音再生
			pSound->PlaySound(CSound::SOUND_LABEL_SE_DETERMINATION);

			// 更新開始
			SetUpdateStop(false);

			// 破棄
			CTutorial_Pause::Release();
		}
	}
}
//******************************************************************************
// 破棄関数
//******************************************************************************
void CTutorial_Pause::Release(void)
{
	// チュートリアル取得
	CMode *pMode = CManager::GetMode();

	// ポーズの使用設定
	((CTutorial*)pMode)->SetPause(false);

	// 破棄
	m_apPolygon[TYPE_BLACK]->Uninit();
	m_apPolygon[TYPE_RESUME]->Uninit();
	m_apPolygon[TYPE_CONTROLS]->Uninit();
	m_apPolygon[TYPE_GAMESTART]->Uninit();
	m_apPolygon[TYPE_EXIT]->Uninit();

	// 終了
	Uninit();
	return;
}