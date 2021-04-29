//******************************************************************************
// タイトル [title.cpp]
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
#include "../Polygon/title_polygon.h"
#include "../Polygon/press_enter_polygon.h"
#include "mode.h"
#include "title.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define TITLE_WAIT_COUNT	(10)													// ゲームへ遷移するカウント
#define TITLE_POS			(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,0.0f))	// タイトル位置座標
#define TITLE_SIZE			(D3DXVECTOR3(SCREEN_WIDTH /2, SCREEN_HEIGHT,0.0f))		// タイトルサイズ
#define TITLE_COLOR			(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))						// タイトルカラー
#define PRESS_ENTER_POS		(D3DXVECTOR3(SCREEN_WIDTH /2,600.0f,0.0f))				// PRESS_ENTER位置座標
#define PRESS_ENTER_SIZE	(D3DXVECTOR3(200.0f,200.0f,0.0f))						// PRESS_ENTERサイズ
#define PRESS_ENTER_COLOR	(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))						// タイトルカラー

//******************************************************************************
// コンストラクタ
//******************************************************************************
CTitle::CTitle()
{
	m_bfade = false;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CTitle::~CTitle()
{
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CTitle::Init()
{
	// タイトル画像生成
	CTitle_Polygon::Create(TITLE_POS, TITLE_SIZE, TITLE_COLOR, CPolygon::TEX_TYPE_TITLE);
	CPress_Enter_Polygon::Create(PRESS_ENTER_POS,PRESS_ENTER_SIZE,PRESS_ENTER_COLOR,CPolygon::TEX_TYPE_PRESS_ENTER);

	// 黒ポリゴン生成
	CBlack_Polygon::Create(POLYGON_RIGHT_POS, POLYGON_SIZE, BLACK_POLYGON_COLOR, CPolygon::TEX_TYPE_MAX);
	CBlack_Polygon::Create(POLYGON_LEFT_POS, POLYGON_SIZE, BLACK_POLYGON_COLOR, CPolygon::TEX_TYPE_MAX);
	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CTitle::Uninit(void)
{
	// フェード以外破棄
	CScene::DesignationReleaseAll(CScene::OBJTYPE_FADE);
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CTitle::Update(void)
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

	// AボタンまたはENTERを押したら
	if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_A) || pInputKeyboard->GetKeyboardTrigger(DIK_RETURN))
	{
		// サウンド再生
		//pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);

		// フェード生成
		CFade::Create(FADE_POS, FADE_SIZE,CSceneManager::MODE_TUTRIAL);
	}
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CTitle::Draw(void)
{
}