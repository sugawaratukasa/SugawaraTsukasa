//******************************************************************************
// リザルト [result.cpp]
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
#include "mode.h"
#include "result.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define RANKING_POLYGON_POS		(D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f))	// ランキングポリゴン位置
#define RANKING_POLYGON_SIZE	(D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT,0.0f))		// ランキングポリゴンサイズ
#define RANKING_POLYGON_COLOR	(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))						// ランキングポリゴン色
#define RANKING_POS				(D3DXVECTOR3(700.0f, 300.0f, 0.0f))						// ランキング位置
#define RANKING_SIZE			(D3DXVECTOR3(30.0f,30.0f,0.0f))							// ランキングサイズ
//******************************************************************************
// 静的メンバ変数
//******************************************************************************
CPlayerdata *CResult::m_pPlayerData = NULL;

//******************************************************************************
// コンストラクタ
//******************************************************************************
CResult::CResult()
{
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CResult::~CResult()
{
	m_bfade = false;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CResult::Init()
{
	// ランキングポリゴン生成
	CRanking_Polygon::Create(RANKING_POLYGON_POS, RANKING_POLYGON_SIZE, RANKING_POLYGON_COLOR, CPolygon::TEX_TYPE_RANKING);
	//ランキング生成
	CRanking::Create(RANKING_POS, RANKING_SIZE);
	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CResult::Uninit(void)
{
	// フェード以外破棄
	CScene::DesignationReleaseAll(CScene::OBJTYPE_FADE);
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CResult::Update(void)
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

	// AボタンまたはENTERを押した場合
	if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_A) || pInputKeyboard->GetKeyboardTrigger(DIK_RETURN))
	{
		// サウンド再生
		pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);

		// フェード生成
		CFade::Create(FADE_POS, FADE_SIZE, CSceneManager::MODE_TITLE);
	}
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CResult::Draw(void)
{
}