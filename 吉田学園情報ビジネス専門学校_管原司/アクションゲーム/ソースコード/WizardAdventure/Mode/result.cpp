//******************************************************************************
// リザルト [result.cpp]
// Author : 管原　
//******************************************************************************

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "manager.h"
#include "keyboard.h"
#include "renderer.h"
#include "joystick.h"
#include "2d_polygon.h"
#include "fade.h"
#include "../2D/2D_Particle/2d_particle_effect.h"
#include "sound.h"
#include "result.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BG_POS				(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f))	// 位置
#define BG_SIZE				(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f))			// サイズ
#define TITLE_POS			(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3, 0.0f))	// 位置
#define TITLE_SIZE			(D3DXVECTOR3(1500.0f, 750.0f, 0.0f))						// サイズ
#define PRESS_START_POS		(D3DXVECTOR3(SCREEN_WIDTH / 2, 700.0f, 0.0f))				// 位置
#define PRESS_START_SIZE	(D3DXVECTOR3(750.0f, 300.0f, 0.0f))							// サイズ
#define COUNT				(3)															// カウント
#define REMAINDER			(0)															// 余り
#define RANDOM_POS_MUT		(10)														// 10倍
#define MUT					(2)															// ２倍
#define SCREEN_X			(SCREEN_WIDTH - 800)										// Xの位置
#define SCREEN_Y			(SCREEN_HEIGHT - 500)										// Xの位置
//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CResult::CResult()
{
	m_nCount = INIT_INT;
}
//*****************************************************************************
//デストラクタ
//*****************************************************************************
CResult::~CResult()
{
}
//*****************************************************************************
//初期化処理
//*****************************************************************************
HRESULT CResult::Init(void)
{
	// サウンド取得
	CSound *pSound = CManager::GetSound();

	// BGM再生
	pSound->PlaySoundA(CSound::SOUND_LABEL_BGM_RESULT);

	// タイトル生成
	C2D_Polygon::Create(TITLE_POS, TITLE_SIZE, C2D_Polygon::TYPE_RESULT);
	return S_OK;
}

//*****************************************************************************
//終了処理
//*****************************************************************************
void CResult::Uninit(void)
{
	// サウンドの停止
	CManager::GetSound()->StopSound();

	// フェード以外破棄
	CScene::DesignationReleaseAll(CScene::OBJTYPE_FADE);
}

//*****************************************************************************
//更新処理
//*****************************************************************************
void CResult::Update(void)
{
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
			// ゲームに遷移
			CFade::Create(CManager::MODE_TITLE);
		}
	}
	// インクリメント
	m_nCount++;
	// 5あまり0
	if (m_nCount % COUNT == REMAINDER)
	{
		// 位置
		D3DXVECTOR3 Random_pos = INIT_D3DXVECTOR3;

		// 位置ランダム
		Random_pos.x = float(rand() % (int)SCREEN_X *RANDOM_POS_MUT * MUT - (int)SCREEN_X *RANDOM_POS_MUT / MUT);

		// 除算
		Random_pos.x = Random_pos.x / RANDOM_POS_MUT;

		// 位置ランダム
		Random_pos.y = float(rand() % (int)SCREEN_Y *RANDOM_POS_MUT * MUT - (int)SCREEN_Y *RANDOM_POS_MUT / MUT);

		// 除算
		Random_pos.y = Random_pos.y / RANDOM_POS_MUT;

		// 生成
		C2D_Particle_Effect::Create(Random_pos, C2D_Particle_Effect::TYPE_COLOR_BOM);
	}
}

//*****************************************************************************
//描画処理
//*****************************************************************************
void CResult::Draw(void)
{

}