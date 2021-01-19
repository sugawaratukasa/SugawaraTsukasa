//******************************************************************************
// コンティニュー [continue.cpp]
// Author : 管原　司
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "input.h"
#include "inputkeyboard.h"
#include "inputjoystick.h"
#include "player.h"
#include "sound.h"
#include "number.h"
#include "game.h"
#include "continue.h"
//******************************************************************************
// コンストラクタ
//******************************************************************************
CContinue::CContinue(int nPriority)
{
	m_pNumber = NULL;
	m_pos  = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_size = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_nContinueCount = 0;
	m_nContinueNum = 0;
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
	//初期化
	m_pNumber = CNumber::Create(m_pos, m_size);
	m_nContinueNum = 9;
	m_pNumber->SetNumber(m_nContinueNum);
	
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
	//キーボード取得
	CInputKeyboard * pInputKeyboard = CSceneManager::GetInputKeyboard();
	//コントローラー取得
	DIJOYSTATE js;
	//インプットジョイスティック
	CInputJoystick * pInputJoystick = CSceneManager::GetInputJoystick();
	//デバイス取得
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();
	//プレイヤーの取得
	CPlayer * pPlayer = CGame::GetPlayer();
	//サウンド取得
	CSound * pSound = CSceneManager::GetSound();
	CSound::SOUND_LABEL type;
	type = CSound::SOUND_LABEL_SE_SHOT;
	//コンティニュータイムのインクリメント
	m_nContinueCount++;
	//1秒たったら
	if (m_nContinueCount % 60 == 0)
	{
		//ナンバーのデクリメント
		m_nContinueNum--;
		//ナンバーの設定
		m_pNumber->SetNumber(m_nContinueNum);
	}
	//ナンバーが0の場合
	if (m_nContinueNum <= 0)
	{
		//リザルトに遷移
		CSceneManager::StartFade(CSceneManager::MODE_RESULT);
	}
	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(11) || pInputKeyboard->GetKeyboardTrigger(DIK_RETURN))
	{
		pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);
		//コンティニューの判定
		pPlayer->SetContinue(PLAYER_CONTINUE);
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
