//=============================================================================
//
// 画面遷移
// title.cpp
// Author : 管原司
//
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "input.h"
#include "inputkeyboard.h"
#include "inputjoystick.h"
#include "player.h"
#include "bullet.h"
#include "bg.h"
#include "explosion.h"
#include "sound.h"
#include "enemy.h"
#include "number.h"
#include "score.h"
#include "life.h"
#include "title.h"
#include "fade.h"
#include "polygon.h"
#include "tutrial.h"
LPDIRECT3DTEXTURE9 CTutrial::m_pTexture = NULL;
//--------------------------------------------------
//テクスチャのロード
//--------------------------------------------------
HRESULT CTutrial::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data/Texture/Tutrial.png", &m_pTexture);
	return S_OK;
}
//-------------------------------------------------
//テクスチャの破棄
//-------------------------------------------------
void CTutrial::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
//---------------------------------------------------
//生成関数
//---------------------------------------------------
CTutrial * CTutrial::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//CPlayerクラスのポインタ
	CTutrial * pTitle;
	//メモリ確保
	pTitle = new CTutrial;
	//初期化
	pTitle->Init(pos, rot, sizeX, sizeY);
	return pTitle;
}
//---------------------------------------------------
//コンストラクタ
//---------------------------------------------------
CTutrial::CTutrial(int nPriority) : CScene2d(nPriority)
{
	m_fade = false;
}
//---------------------------------------------------
//デストラクタ
//---------------------------------------------------
CTutrial::~CTutrial()
{
}
//---------------------------------------------------
//初期化
//---------------------------------------------------
HRESULT CTutrial::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//初期化
	CScene2d::Init(pos, rot, sizeX, sizeY);
	//RGBの設定
	SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//テクスチャの受け渡し
	BindTexture(m_pTexture);
	//テクスチャセット
	SetTexture(0.0f, 0.0f, 1.0f, 1.0f);
	CPolygon::Create(D3DXVECTOR3(RIGHT_POS_X, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), POLYGON_SIZE_X, SCREEN_HEIGHT);
	CPolygon::Create(D3DXVECTOR3(LEFT_POS_X, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), POLYGON_SIZE_X, SCREEN_HEIGHT);
	return S_OK;
}
//---------------------------------------------------
//終了
//---------------------------------------------------
void CTutrial::Uninit(void)
{
	//終了
	CScene2d::Uninit();
}
//---------------------------------------------------
//更新
//---------------------------------------------------
void CTutrial::Update(void)
{
	int nWaitnCnt = 0;
	//更新
	CScene2d::Update();
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

	if (m_fade == false)
	{
		if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(JS_A) || pInputKeyboard->GetKeyboardTrigger(DIK_RETURN))
		{
			pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);
			m_fade = true;
		}
	}
	if (m_fade == true)
	{
		CSceneManager::StartFade(CSceneManager::MODE_GAME);
	}
}
//---------------------------------------------------
//描画
//---------------------------------------------------
void CTutrial::Draw(void)
{
	//描画
	CScene2d::Draw();
}