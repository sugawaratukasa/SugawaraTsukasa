//******************************************************************************
// タイトル [title.cpp]
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
#include "sound.h"
#include "title.h"
#include "fade.h"
#include "polygon.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define TITLE_WAIT_COUNT (10)								// ゲームへ遷移するカウント
#define PRESS_ENTER_SIZE (D3DXVECTOR3(200.0f,200.0f,0.0f))	// プレスエンターサイズ
//******************************************************************************
// 静的メンバ変数
//******************************************************************************
LPDIRECT3DTEXTURE9 CTitle::m_apTexture[MAX_TITLE_TEX] = {};

//******************************************************************************
// テクスチャ読み込み
//******************************************************************************
HRESULT CTitle::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data/Texture/Title.png", &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/PressEnter.png", &m_apTexture[1]);
	return S_OK;
}
//******************************************************************************
// テクスチャ破棄
//******************************************************************************
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
//******************************************************************************
// コンストラクタ
//******************************************************************************
CTitle::CTitle(int nPriority) : CScene(nPriority)
{
	memset(m_apScene2D, 0, sizeof(m_apScene2D));
	m_pos		= D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_size		= D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_color		= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_bColor	= false;
	m_bfade		= false;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CTitle::~CTitle()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CTitle * CTitle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//　CTitleクラスのポインタ
	CTitle * pTitle;

	//　メモリ確保
	pTitle = new CTitle;

	// 位置座標代入
	pTitle->m_pos = pos;

	// サイズ代入
	pTitle->m_size = size;

	// 初期化
	pTitle->Init();

	// ポインタを返す
	return pTitle;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CTitle::Init()
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
	}
	// 位置座標設定
	m_apScene2D[0]->SetPosition(m_pos);
	m_apScene2D[1]->SetPosition(D3DXVECTOR3(m_pos.x, 600.0f, 0.0f));

	// サイズ設定
	m_apScene2D[0]->SetSize(m_size);
	m_apScene2D[1]->SetSize(PRESS_ENTER_SIZE);

	// 初期化
	m_apScene2D[0]->Init();
	m_apScene2D[1]->Init();

	// 黒ポリゴン生成
	CPolygon::Create(POLYGON_RIGHT_POS, POLYGON_SIZE);
	CPolygon::Create(POLYGON_LEFT_POS, POLYGON_SIZE);
	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CTitle::Uninit(void)
{
	//終了
	Release();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CTitle::Update(void)
{
	// 最大数分繰り返す
	for (int nCnt = 0; nCnt < MAX_TITLE; nCnt++)
	{
		// 更新
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

	// falseの場合
	if (m_bColor == false)
	{
		// α値減算
		m_color.a -= 0.05f;
		// 0.1以下の場合
		if (m_color.a <= 0.1f)
		{
			// trueにする
			m_bColor = true;
		}
	}
	else
	{
		// α値加算
		m_color.a += 0.05f;
		// 1.0f以上の場合
		if (m_color.a >= 1.0f)
		{
			// falseにする
			m_bColor = false;
		}
	}
	// カラー設定
	m_apScene2D[1]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_color.a));

	// AボタンまたはENTERを押したら
	if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(JS_A) || pInputKeyboard->GetKeyboardTrigger(DIK_RETURN))
	{
		// サウンド再生
		pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);

		// trueに
		m_bfade = true;
	}
	//trueの場合
	if (m_bfade == true)
	{
		// フェード開始
		CSceneManager::StartFade(CSceneManager::MODE_TUTRIAL);
	}
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CTitle::Draw(void)
{
}