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
#include "result.h"
#include "fade.h"
#include "ranking.h"
LPDIRECT3DTEXTURE9 CResult::m_pTexture = NULL;
CPlayerdata *CResult::m_pPlayerData = NULL;
//--------------------------------------------------
//テクスチャのロード
//--------------------------------------------------
HRESULT CResult::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data/Texture/Ranking.png", &m_pTexture);
	return S_OK;
}
//-------------------------------------------------
//テクスチャの破棄
//-------------------------------------------------
void CResult::Unload(void)
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
CResult * CResult::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//CPlayerクラスのポインタ
	CResult * pResult;
	//メモリ確保
	pResult = new CResult;
	//初期化
	pResult->Init(pos, rot, sizeX, sizeY);
	return pResult;
}
//---------------------------------------------------
//コンストラクタ
//---------------------------------------------------
CResult::CResult(int nPriority) : CScene(nPriority)
{
	m_pScene2D = NULL;
}
//---------------------------------------------------
//デストラクタ
//---------------------------------------------------
CResult::~CResult()
{
	m_bfade = false;
}
//---------------------------------------------------
//初期化
//---------------------------------------------------
HRESULT CResult::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//メモリ確保
	m_pScene2D = new CScene2d;
	m_pScene2D->Init(pos, rot, sizeX, sizeY);
	//RGBの設定
	m_pScene2D->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//テクスチャの受け渡し
	m_pScene2D->BindTexture(m_pTexture);
	//テクスチャセット
	m_pScene2D->SetTexture(0.0f, 0.0f, 1.0f, 1.0f);
	//ランキング生成
	CRanking::Create(D3DXVECTOR3(700.0f, 300.0f, 0.0f), rot, 30, 30);
	return S_OK;
}
//---------------------------------------------------
//終了
//---------------------------------------------------
void CResult::Uninit(void)
{
	//破棄
	Release();
}
//---------------------------------------------------
//更新
//---------------------------------------------------
void CResult::Update(void)
{
	//更新
	m_pScene2D->Update();
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
	if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(JS_A) || pInputKeyboard->GetKeyboardTrigger(DIK_RETURN))
	{
		m_bfade = true;
	}
	//trueの場合
	if (m_bfade == true)
	{
		CSceneManager::StartFade(CSceneManager::MODE_TITLE);
	}
}
//---------------------------------------------------
//描画
//---------------------------------------------------
void CResult::Draw(void)
{
}