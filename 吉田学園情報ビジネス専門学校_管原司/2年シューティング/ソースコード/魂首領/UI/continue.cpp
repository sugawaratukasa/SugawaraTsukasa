//******************************************************************************
// コンティニュー [continue.cpp]
// Author : 管原　司
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
#include "../Player/player.h"
#include "../System/sound.h"
#include "../System/number.h"
#include "../Mode/game.h"
#include "continue.h"
#include "../Polygon/fade.h"
#include "../Polygon/polygon.h"
#include "../Polygon/continue_polygon.h"
#include "../Polygon/press_enter_polygon.h"
//******************************************************************************
// マクロ定義
//******************************************************************************		
#define PRESS_ENTER_POS			(D3DXVECTOR3(SCREEN_WIDTH / 2,600,0.0f))						// プレスエンター位置
#define PRESS_ENTER_SIZE		(D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 4,0.0f))			// プレスエンターサイズ
#define CONTINUE_POLYGON_POS	(D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2 - 200,0.0f))	// コンティニューポリゴンの位置
#define CONTINUE_POLYGON_SIZE	(D3DXVECTOR3(SCREEN_WIDTH / 2,300.0f,0.0f))						// コンティニューポリゴンのサイズ
#define CONTINUE_POLYGON_COLOR	(D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))								// コンティニューポリゴンのサイズ
#define PRESS_ENTER_COLOR		(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))								// プレスエンター色
#define COLOR_VALUE				(D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))								// 色の値
#define TIME_COUNT				(60)															// 時間
#define CONTINUE_TIMW_MIN		(0)																// コンティニュー時間の最小
#define REMAINDER_VALUE			(0)																// 余り0の値
#define CONTINUE_TIME_MAX		(9)																// コンティニュー時間の最大
#define PLAYER_CONTINUE			(1)																// プレイヤーのコンティニュー
//******************************************************************************
// コンストラクタ
//******************************************************************************
CContinue::CContinue(int nPriority) : CScene(nPriority)
{
	m_pNumber			= NULL;
	m_pContinue_Polygon = NULL;
	m_pPress_Enter		= NULL;
	m_pos				= INIT_D3DXVECTOR3;
	m_size				= INIT_D3DXVECTOR3;
	m_nContinueCount	= INIT_INT;
	m_nContinueNum		= INIT_INT;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CContinue::~CContinue()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CContinue * CContinue::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CContinueクラスのポインタ
	CContinue * pContinue;

	// メモリ確保
	pContinue = new CContinue;

	// 位置座標代入
	pContinue->m_pos = pos;

	// サイズ代入
	pContinue->m_size = size;

	// 初期化
	pContinue->Init();

	// ポインタを返す
	return pContinue;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CContinue::Init(void)
{
	// 数字生成
	m_pNumber = CNumber::Create(m_pos, m_size, COLOR_VALUE);

	// コンティニュー時間
	m_nContinueNum = CONTINUE_TIME_MAX;

	// 数字設定
	m_pNumber->SetNumber(m_nContinueNum);

	// UI生成

	// コンティニューポリゴン生成
	m_pContinue_Polygon = CContinue_Polygon::Create(CONTINUE_POLYGON_POS, CONTINUE_POLYGON_SIZE, CONTINUE_POLYGON_COLOR, CPolygon::TEX_TYPE_CONTINUE);

	// プレスエンター生成
	m_pPress_Enter = CPress_Enter_Polygon::Create(PRESS_ENTER_POS, PRESS_ENTER_SIZE, PRESS_ENTER_COLOR,CPolygon::TEX_TYPE_PRESS_ENTER);

	return S_OK;								  
}												 
//******************************************************************************
// 終了関数
//******************************************************************************
void CContinue::Uninit(void)
{
	// 終了
	if (m_pNumber != NULL)
	{
		m_pNumber->Uninit();
		delete m_pNumber;
		m_pNumber = NULL;
	}
	//リリース
	Release();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CContinue::Update(void)
{
	// キーボード取得
	CInputKeyboard * pInputKeyboard = CSceneManager::GetInputKeyboard();

	// ジョイスティック
	DIJOYSTATE js;

	// インプットジョイスティック
	CInputJoystick * pInputJoystick = CSceneManager::GetInputJoystick();

	// デバイス取得
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	// プレイヤーの取得
	CPlayer * pPlayer = CGame::GetPlayer();

	// サウンド取得
	CSound * pSound = CSceneManager::GetSound();
	CSound::SOUND_LABEL type;
	type = CSound::SOUND_LABEL_SE_SHOT;

	// コンティニュータイムのインクリメント
	m_nContinueCount++;
	// 1秒たったら
	if (m_nContinueCount % TIME_COUNT == REMAINDER_VALUE)
	{
		// ナンバーのデクリメント
		m_nContinueNum--;
		// ナンバーの設定
		m_pNumber->SetNumber(m_nContinueNum);
	}
	// ナンバーが0の場合
	if (m_nContinueNum <= CONTINUE_TIMW_MIN)
	{
		// リザルトに遷移
		CFade::Create(FADE_POS, FADE_SIZE, CSceneManager::MODE_RESULT);
	}
	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	// STARTボタンまたはENTERが押された場合
	if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(11) || pInputKeyboard->GetKeyboardTrigger(DIK_RETURN))
	{
		// 音生成
		pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);

		// コンティニューの判定
		pPlayer->SetContinue(PLAYER_CONTINUE);

		// コンティニューポリゴン破棄
		m_pContinue_Polygon->Uninit();

		// プレスエンター破棄
		m_pPress_Enter->Uninit();

		// 終了
		Uninit();
		return;
	}
	
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CContinue::Draw(void)
{
	// 描画
	m_pNumber->Draw();
}
