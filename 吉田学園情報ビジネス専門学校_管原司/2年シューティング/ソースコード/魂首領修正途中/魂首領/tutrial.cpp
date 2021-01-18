//******************************************************************************
// チュートリアル [tutrial.cpp]
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
#include "fade.h"
#include "polygon.h"
#include "sound.h"
#include "tutrial.h"
//******************************************************************************
// 静的メンバ変数
//******************************************************************************
LPDIRECT3DTEXTURE9 CTutrial::m_pTexture = NULL;
//******************************************************************************
// テクスチャ読み込み
//******************************************************************************
HRESULT CTutrial::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data/Texture/Tutrial.png", &m_pTexture);
	return S_OK;
}
//******************************************************************************
// テクスチャ破棄
//******************************************************************************
void CTutrial::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
//******************************************************************************
// 生成関数
//******************************************************************************
CTutrial * CTutrial::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CTutrialクラスのポインタ
	CTutrial * pTitle;

	// メモリ確保
	pTitle = new CTutrial;

	// 位置座標設定
	pTitle->SetPosition(pos);

	// サイズ設定
	pTitle->SetSize(size);

	// 初期化
	pTitle->Init();

	// ポインタを返す
	return pTitle;
}
//******************************************************************************
// コンストラクタ
//******************************************************************************-
CTutrial::CTutrial(int nPriority) : CScene2d(nPriority)
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
	//初期化
	CScene2d::Init();

	//RGBの設定
	SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//テクスチャの受け渡し
	BindTexture(m_pTexture);

	// 黒ポリゴン生成
	CPolygon::Create(POLYGON_RIGHT_POS, POLYGON_SIZE);
	CPolygon::Create(POLYGON_LEFT_POS, POLYGON_SIZE);
	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CTutrial::Uninit(void)
{
	//終了
	CScene2d::Uninit();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CTutrial::Update(void)
{
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

	// falseの場合
	if (m_bfade == false)
	{
		// コントローラーAボタンまたはENTER
		if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(JS_A) || pInputKeyboard->GetKeyboardTrigger(DIK_RETURN))
		{
			// サウンド再生
			//pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);
			// trueに
			m_bfade = true;
		}
	}
	// trueの場合
	if (m_bfade == true)
	{
		// フェード開始
		CSceneManager::StartFade(CSceneManager::MODE_GAME);
	}
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CTutrial::Draw(void)
{
	//描画
	CScene2d::Draw();
}