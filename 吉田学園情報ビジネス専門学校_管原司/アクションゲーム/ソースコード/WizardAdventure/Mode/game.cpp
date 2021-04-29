//******************************************************************************
// ツール [game.cpp]
// Author : 管原　
//******************************************************************************

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "manager.h"
#include "keyboard.h"
#include "joystick.h"
#include "renderer.h"
#include "time.h"
#include "mode.h"
#include "camera.h"
#include "light.h"
#include "scene.h"
#include "game.h"
#include "debug_proc.h"
#include "../3D/Model/player.h"
#include "map.h"
#include "../3D/3DPolygon/Particle/Particle_Emitter/particle_emitter.h"
#include "../3D/3DPolygon/BG/bg.h"
#include "sound.h"
#include "pause.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PLAYER_POS		(D3DXVECTOR3(100.0f, -50.0f, -200.0f))
#define PLAYER_ROT		(D3DXVECTOR3(0.0f,D3DXToRadian(90.0f),0.0f))
#define PLAYER_SIZE		(D3DXVECTOR3(30.0f,15.0f,30.0f))
#define ENEMY_POS		(D3DXVECTOR3(-100.0f,-45.0f,-200.0f))
#define ENEMY_POS2		(D3DXVECTOR3(0.0f,-45.0f,-200.0f))
#define TEST_POS		(D3DXVECTOR3(-150.0f, -70.0f, -200.0f))
#define TEST_ROT		(D3DXVECTOR3(0.0f,0.0,0.0))
#define TEST_SIZE		(D3DXVECTOR3(30.0f,30.0f, 30.0f))
#define TEST_COLOR		(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))
#define TEST_POS2		(D3DXVECTOR3(-50.0f, -50.0f, -200.0f))
#define TEST_ROT2		(D3DXVECTOR3(0.0f,0.0,0.0f))
#define TEST_SIZE2		(D3DXVECTOR3(30.0f, 30.0f, 30.0f))
#define TEST_POS3		(D3DXVECTOR3(-100.0f, -50.0f, -200.0f))
#define TEST_ROT3		(D3DXVECTOR3(0.0f,0.0,0.0f))
#define TEST_SIZE3		(D3DXVECTOR3(30.0f, 30.0f, 30.0f))
#define TEST_COLOR2		(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))
#define POS				(D3DXVECTOR3(-30.0f, 0.0f, -200.0f))
#define ROT				(D3DXVECTOR3(0.0f,90.0f,0.0f))
#define SIZE			(D3DXVECTOR3(30.0f, 30.0f, 30.0f))
#define COLOR			(D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))
#define CREATE_COUNT	(60)
//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CGame::CGame()
{
	m_nCount = INIT_INT;
	m_bPause = false;
}
//*****************************************************************************
//デストラクタ
//*****************************************************************************
CGame::~CGame()
{
}
//*****************************************************************************
//初期化処理
//*****************************************************************************
HRESULT CGame::Init(void)
{
	//サウンド取得
	CSound * pSound = CManager::GetSound();

	// ゲームBGM再生
	pSound->PlaySound(CSound::SOUND_LABEL_BGM_GAME);

	// カメラ
	CManager::CreateCamera();

	// ライト
	CManager::CreateLight();

	// マップ生成
	CMap::Create(CMap::TYPE_GAME);

	// プレイヤー生成
	CPlayer::Create(PLAYER_POS, PLAYER_ROT, PLAYER_SIZE);

	// エフェクト生成
	CParticle_Emitter::Create(PLAYER_POS, CParticle_Emitter::TYPE_MAP);

	// 背景生成
	CBg::Create();

	return S_OK;
}

//*****************************************************************************
//終了処理
//*****************************************************************************
void CGame::Uninit(void)
{
	//サウンドの停止
	CManager::GetSound()->StopSound();

	// フェード以外破棄
	CScene::DesignationReleaseAll(CScene::OBJTYPE_FADE);
}

//*****************************************************************************
//更新処理
//*****************************************************************************
void CGame::Update(void)
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
		// falseの場合
		if (m_bPause == false)
		{
			// STARTボタンを押した場合
			if (pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_START))
			{
				// タイトルBGM再生
				pSound->PlaySound(CSound::SOUND_LABEL_SE_DETERMINATION);

				// ポーズ生成
				CPause::Create();

				// trueに
				m_bPause = true;
			}
		}
	}
}

//*****************************************************************************
//描画処理
//*****************************************************************************
void CGame::Draw(void)
{

}
//*****************************************************************************
// ポーズ設定
//*****************************************************************************
void CGame::SetPause(bool bPause)
{
	m_bPause = bPause;
}
