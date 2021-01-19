//******************************************************************************
// リザルト [result.cpp]
// Author : 管原 司
//******************************************************************************
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "input.h"
#include "inputkeyboard.h"
#include "inputjoystick.h"
#include "result.h"
#include "fade.h"
#include "score.h"
#include "ranking.h"
//******************************************************************************
// 静的メンバ変数
//******************************************************************************
LPDIRECT3DTEXTURE9 CResult::m_pTexture = NULL;
CPlayerdata *CResult::m_pPlayerData = NULL;
//******************************************************************************
// テクスチャ読み込み
//******************************************************************************
HRESULT CResult::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data/Texture/Ranking.png", &m_pTexture);
	return S_OK;
}
//******************************************************************************
// テクスチャ破棄
//******************************************************************************
void CResult::Unload(void)
{
		// テクスチャの破棄
		if (m_pTexture != NULL)
		{
			m_pTexture->Release();
			m_pTexture = NULL;
		}
}
//******************************************************************************
// コンストラクタ
//******************************************************************************
CResult::CResult(int nPriority) : CScene(nPriority)
{
	m_pScene2D	= NULL;
	m_pos		= D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_size		= D3DXVECTOR3(0.0f,0.0f,0.0f);
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CResult::~CResult()
{
	m_bfade = false;
}
//******************************************************************************
// 生成関数
//******************************************************************************
CResult * CResult::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CResultクラスのポインタ
	CResult * pResult;

	// メモリ確保
	pResult = new CResult;

	// 位置座標代入
	pResult->m_pos = pos;

	// サイズ代入
	pResult->m_size = size;

	// 初期化
	pResult->Init();

	// ポインタを返す
	return pResult;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CResult::Init()
{
	//メモリ確保
	m_pScene2D = new CScene2d;

	// 位置座標設定
	m_pScene2D->SetPosition(m_pos);

	// サイズ設定
	m_pScene2D->SetSize(m_size);

	//RGBの設定
	m_pScene2D->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//テクスチャの受け渡し
	m_pScene2D->BindTexture(m_pTexture);

	// 初期化
	m_pScene2D->Init();

	//ランキング生成
	CRanking::Create(D3DXVECTOR3(700.0f, 300.0f, 0.0f), SCORE_SIZE);
	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CResult::Uninit(void)
{
	// 終了
	Release();
}
//******************************************************************************
// 更新関数
//******************************************************************************
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

	// AボタンまたはENTERを押した場合
	if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(JS_A) || pInputKeyboard->GetKeyboardTrigger(DIK_RETURN))
	{
		// trueにする
		m_bfade = true;
	}
	//trueの場合
	if (m_bfade == true)
	{
		// フェード開始
		CSceneManager::StartFade(CSceneManager::MODE_TITLE);
	}
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CResult::Draw(void)
{
}