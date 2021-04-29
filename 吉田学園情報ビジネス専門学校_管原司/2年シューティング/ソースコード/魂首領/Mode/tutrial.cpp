//******************************************************************************
// チュートリアル [tutrial.cpp]
// Author : 管原 司
//******************************************************************************

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "../System/main.h"
#include "../System/manager.h"
#include "../System/renderer.h"
#include "../System/scene.h"
#include "../System/scene2d.h"
#include "../Input/input.h"
#include "../Input/inputkeyboard.h"
#include "../Input/inputjoystick.h"
#include "../Polygon/fade.h"
#include "../UI/score.h"
#include "../Polygon/polygon.h"
#include "../System/ranking.h"
#include "../Polygon/ranking_polygon.h"
#include "../System/sound.h"
#include "../Polygon/black_polygon.h"
#include "../Polygon/tutrial_polygon.h"
#include "mode.h"
#include "tutrial.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define TUTRIAL_POS		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f))// 位置
#define MODE_SIZE		(D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT,0.0f))		// サイズ
#define TUTRIAL_COLOR	(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))						// カラー
//******************************************************************************
// コンストラクタ
//******************************************************************************-
CTutrial::CTutrial()
{
	m_bfade = false;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CTutrial::~CTutrial()
{
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CTutrial::Init()
{
	// チュートリアル画像生成
	CTutrial_Polygon::Create(TUTRIAL_POS, MODE_SIZE, TUTRIAL_COLOR,CPolygon::TEX_TYPE_TUTRIAL);
	// 黒ポリゴン生成
	CBlack_Polygon::Create(POLYGON_RIGHT_POS, POLYGON_SIZE, BLACK_POLYGON_COLOR, CPolygon::TEX_TYPE_MAX);
	CBlack_Polygon::Create(POLYGON_LEFT_POS, POLYGON_SIZE, BLACK_POLYGON_COLOR, CPolygon::TEX_TYPE_MAX);
	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CTutrial::Uninit(void)
{
	// フェード以外破棄
	CScene::DesignationReleaseAll(CScene::OBJTYPE_FADE);
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CTutrial::Update(void)
{
	//サウンド取得
	CSound * pSound = CSceneManager::GetSound();
	CSound::SOUND_LABEL type;
	type = CSound::SOUND_LABEL_SE_SHOT;

	//キーボード取得
	CInputKeyboard * pInputKeyboard = CSceneManager::GetInputKeyboard();

	//コントローラー取得
	DIJOYSTATE js;
	CInputJoystick * pInputJoystick = CSceneManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	// コントローラーAボタンまたはENTER
	if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_A) || pInputKeyboard->GetKeyboardTrigger(DIK_RETURN))
	{
		// サウンド再生
		//pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);

		// フェード生成
		CFade::Create(FADE_POS, FADE_SIZE, CSceneManager::MODE_GAME);
	}
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CTutrial::Draw(void)
{
}