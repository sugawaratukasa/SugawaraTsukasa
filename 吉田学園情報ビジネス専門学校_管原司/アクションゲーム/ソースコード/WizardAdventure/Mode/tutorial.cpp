//******************************************************************************
// チュートリアル [tutorial.cpp]
// Author : 管原司
//******************************************************************************

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "manager.h"
#include "keyboard.h"
#include "joystick.h"
#include "scene.h"
#include "renderer.h"
#include "joystick.h"
#include "2d_polygon.h"
#include "fade.h"
#include "map.h"
#include "../3D/3DPolygon/Particle/Particle_Emitter/particle_emitter.h"
#include "../3D/3DPolygon/BG/bg.h"
#include "../3D/Model/player.h"
#include "sound.h"
#include "tutorial_pause.h"
#include "tutorial.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PLAYER_POS			(D3DXVECTOR3(100.0f, -50.0f, -200.0f))						// 位置
#define PLAYER_ROT			(D3DXVECTOR3(0.0f,D3DXToRadian(90.0f),0.0f))				// 向き
#define PLAYER_SIZE			(D3DXVECTOR3(30.0f,15.0f,30.0f))							// サイズ
#define PRESS_START_POS		(D3DXVECTOR3(SCREEN_WIDTH / 2, 900.0f, 0.0f))				// 位置
#define PRESS_START_SIZE	(D3DXVECTOR3(750.0f, 300.0f, 0.0f))							// サイズ
//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CTutorial::CTutorial()
{
	m_bPause = false;
}
//*****************************************************************************
//デストラクタ
//*****************************************************************************
CTutorial::~CTutorial()
{
}
//*****************************************************************************
//初期化処理
//*****************************************************************************
HRESULT CTutorial::Init(void)
{
	//サウンド取得
	CSound * pSound = CManager::GetSound();

	// タイトルBGM再生
	pSound->PlaySound(CSound::SOUND_LABEL_BGM_TITLE);

	// カメラ
	CManager::CreateCamera();

	// ライト
	CManager::CreateLight();

	// マップ生成
	CMap::Create(CMap::TYPE_TUTORIAL);

	// プレイヤー生成
	CPlayer::Create(PLAYER_POS, PLAYER_ROT, PLAYER_SIZE);

	// 背景生成
	CBg::Create();
	
	// PRESS_START
	C2D_Polygon::Create(PRESS_START_POS, PRESS_START_SIZE, C2D_Polygon::TYPE_PRESS_START);
	return S_OK;
}

//*****************************************************************************
//終了処理
//*****************************************************************************
void CTutorial::Uninit(void)
{
	//サウンドの停止
	CManager::GetSound()->StopSound();

	// フェード以外破棄
	CScene::DesignationReleaseAll(CScene::OBJTYPE_FADE);
}

//*****************************************************************************
//更新処理
//*****************************************************************************
void CTutorial::Update(void)
{
	//サウンド取得
	CSound * pSound = CManager::GetSound();

	// コントローラー取得
	DIJOYSTATE js;
	js.lY = INIT_INT;
	js.lX = INIT_INT;
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();
	// NULLでない場合
	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	// NULLでない場合
	if (g_lpDIDevice != NULL)
	{
		// STARTボタンを押した場合
		if (pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_START) || pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_A))
		{
			// falseの場合
			if (m_bPause == false)
			{
				// STARTボタンを押した場合
				if (pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_START))
				{
					// 決定音再生
					pSound->PlaySound(CSound::SOUND_LABEL_SE_DETERMINATION);

					// ポーズ生成
					CTutorial_Pause::Create();

					// trueに
					m_bPause = true;
				}
			}
		}
	}
}

//*****************************************************************************
//描画処理
//*****************************************************************************
void CTutorial::Draw(void)
{

}
//*****************************************************************************
// ポーズの使用設定
//*****************************************************************************
void CTutorial::SetPause(bool bPause)
{
	m_bPause = bPause;
}