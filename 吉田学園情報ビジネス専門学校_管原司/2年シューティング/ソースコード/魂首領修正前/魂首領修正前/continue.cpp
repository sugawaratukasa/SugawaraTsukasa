//-----------------------------------------------------------------
// Continue
// continue.cpp
// Author 管原 司
//-----------------------------------------------------------------
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
#include "game.h"
#include "fade.h"
#include "item.h"
#include "bomui.h"
#include "polygon.h"
#include "ship.h"
#include "continue.h"
//-----------------------------------------------------------------
//コントラクタ
//-----------------------------------------------------------------
CContinue::CContinue(int nPriority)
{
	m_pNumber = NULL;
	m_nContinueCount = 0;
	m_nContinueNum = 0;
}
//-----------------------------------------------------------------
//デストラクタ
//-----------------------------------------------------------------
CContinue::~CContinue()
{
}
//-----------------------------------------------------------------
//生成関数
//-----------------------------------------------------------------
CContinue * CContinue::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//CPlayerクラスのポインタ
	CContinue * pContinue;
	//メモリ確保
	pContinue = new CContinue;
	//初期化
	pContinue->Init(pos, rot, sizeX, sizeY);
	return pContinue;
}
//-----------------------------------------------------------------
//初期化処理
//-----------------------------------------------------------------
HRESULT CContinue::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//初期化
	m_pNumber = CNumber::Create(pos, sizeX, sizeY);
	m_nContinueNum = 9;
	m_pNumber->SetNumber(m_nContinueNum);
	
	return S_OK;
}
//-----------------------------------------------------------------
//終了処理
//-----------------------------------------------------------------
void CContinue::Uninit(void)
{
	if (m_pNumber != NULL)
	{
		m_pNumber->Uninit();
		delete m_pNumber;
		m_pNumber = NULL;
	}
	//リリース
	Release();
}
//-----------------------------------------------------------------
//更新処理
//-----------------------------------------------------------------
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
//-----------------------------------------------------------------
//描画処理
//-----------------------------------------------------------------
void CContinue::Draw(void)
{
	m_pNumber->Draw();
}
