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
LPDIRECT3DTEXTURE9 CTitle::m_apTexture[MAX_TITLE_TEX] = {};
//--------------------------------------------------
//テクスチャのロード
//--------------------------------------------------
HRESULT CTitle::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data/Texture/Title.png", &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/PressEnter.png", &m_apTexture[1]);
	return S_OK;
}
//-------------------------------------------------
//テクスチャの破棄
//-------------------------------------------------
void CTitle::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_TITLE_TEX; nCnt++)
	{
		// テクスチャの破棄
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}
//---------------------------------------------------
//生成関数
//---------------------------------------------------
CTitle * CTitle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//CPlayerクラスのポインタ
	CTitle * pTitle;
	//メモリ確保
	pTitle = new CTitle;
	//初期化
	pTitle->Init(pos, rot, sizeX, sizeY);
	return pTitle;
}
//---------------------------------------------------
//コンストラクタ
//---------------------------------------------------
CTitle::CTitle(int nPriority) : CScene(nPriority)
{
	memset(m_apScene2D, 0, sizeof(m_apScene2D));
	m_bfade = false;
	m_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_bColor = false;
}
//---------------------------------------------------
//デストラクタ
//---------------------------------------------------
CTitle::~CTitle()
{
}
//---------------------------------------------------
//初期化
//---------------------------------------------------
HRESULT CTitle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//初期化
	for (int nCnt = 0; nCnt < MAX_TITLE; nCnt++)
	{
		//メモリ確保
		m_apScene2D[nCnt] = new CScene2d;
		//RGBの設定
		m_apScene2D[nCnt]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		//テクスチャの受け渡し
		m_apScene2D[nCnt]->BindTexture(m_apTexture[nCnt]);
		//テクスチャセット
		m_apScene2D[nCnt]->SetTexture(0.0f, 0.0f, 1.0f, 1.0f);
	}
	m_apScene2D[0]->Init(pos, rot, sizeX, sizeY);
	m_apScene2D[1]->Init(D3DXVECTOR3(pos.x, 600, 0.0f), rot, 200, 200);
	CPolygon::Create(D3DXVECTOR3(RIGHT_POS_X, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), POLYGON_SIZE_X, SCREEN_HEIGHT);
	CPolygon::Create(D3DXVECTOR3(LEFT_POS_X, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), POLYGON_SIZE_X, SCREEN_HEIGHT);
	return S_OK;
}
//---------------------------------------------------
//終了
//---------------------------------------------------
void CTitle::Uninit(void)
{
	//破棄
	Release();
}
//---------------------------------------------------
//更新
//---------------------------------------------------
void CTitle::Update(void)
{
	for (int nCnt = 0; nCnt < MAX_TITLE; nCnt++)
	{
		m_apScene2D[nCnt]->Update();
	}
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
	if (m_bColor == false)
	{
		m_color.a -= 0.05f;
		if (m_color.a <= 0.1f)
		{
			m_bColor = true;
		}
	}
	else
	{
		m_color.a += 0.05f;
		if (m_color.a >= 1.0f)
		{
			m_bColor = false;
		}
	}
	m_apScene2D[1]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_color.a));
	if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(JS_A) || pInputKeyboard->GetKeyboardTrigger(DIK_RETURN))
	{
		pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);
		m_bfade = true;
	}
	//trueの場合
	if (m_bfade == true)
	{
		CSceneManager::StartFade(CSceneManager::MODE_TUTRIAL);
	}
}
//---------------------------------------------------
//描画
//---------------------------------------------------
void CTitle::Draw(void)
{
}