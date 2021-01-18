//---------------------------------------------------
// BG
// bg.cpp
// Author:	管原司
//---------------------------------------------------
//---------------------------------------------------
//インクルードファイル
//---------------------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "input.h"
#include "inputkeyboard.h"
#include "inputjoystick.h"
#include "bg.h"
#include "player.h"
#include "game.h"
LPDIRECT3DTEXTURE9 CBg::m_apTexture[MAX_BG] = {};
//--------------------------------------------------
//テクスチャ読み込み
//--------------------------------------------------
HRESULT CBg::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data/Texture/bg2.png", &m_apTexture[TYPE_FARST_BG]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/bg101.png", &m_apTexture[TYPE_SECOUND_BG]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/bg102.png", &m_apTexture[TYPE_THIRD_BG]);
	return S_OK;
}
//--------------------------------------------------
//テクスチャの破棄
//--------------------------------------------------
void CBg::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
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
CBg * CBg::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//ポインタ
	CBg * pBg;
	//メモリ確保
	pBg = new CBg;
	//初期化
	pBg->Init(pos, rot, sizeX, sizeY);
	return pBg;
}
//---------------------------------------------------
//コンストラクタ
//---------------------------------------------------
CBg::CBg(int nPriority) : CScene(nPriority)
{
	memset(m_apScene2D, 0, sizeof(m_apScene2D));
	m_type = TYPE_NONE;
	m_Farstpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Secoundpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Thirdpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_texsizeX = 0.0f;
	m_texsizeY = 0.0f;
	m_fFastMove = 0.0f;
	m_fSlowMove = 0.0f;
	m_fmove = 0.0f;
}
//---------------------------------------------------
//デストラクタ
//---------------------------------------------------
CBg::~CBg()
{
}
//---------------------------------------------------
//初期化
//---------------------------------------------------
HRESULT CBg::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//メモリ確保
	m_apScene2D[TYPE_FARST_BG] = new CScene2d;
	m_apScene2D[TYPE_SECOUND_BG] = new CScene2d;
	m_apScene2D[TYPE_THIRD_BG] = new CScene2d;
	//初期化
	m_apScene2D[TYPE_FARST_BG]->Init(pos, rot, sizeX, sizeY);
	m_apScene2D[TYPE_SECOUND_BG]->Init(pos, rot, sizeX, sizeY);
	m_apScene2D[TYPE_THIRD_BG]->Init(pos, rot, sizeX, sizeY);
	//カラー設定
	m_apScene2D[TYPE_FARST_BG]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apScene2D[TYPE_SECOUND_BG]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apScene2D[TYPE_THIRD_BG]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//テクスチャの受け渡し
	m_apScene2D[TYPE_FARST_BG]->BindTexture(m_apTexture[TYPE_FARST_BG]);
	m_apScene2D[TYPE_SECOUND_BG]->BindTexture(m_apTexture[TYPE_SECOUND_BG]);
	m_apScene2D[TYPE_THIRD_BG]->BindTexture(m_apTexture[TYPE_THIRD_BG]);
	//オブジェクトタイプの設定
	m_apScene2D[TYPE_FARST_BG]->SetObjType(CScene::OBJTYPE_BG);
	m_apScene2D[TYPE_SECOUND_BG]->SetObjType(CScene::OBJTYPE_BG);
	m_apScene2D[TYPE_THIRD_BG]->SetObjType(CScene::OBJTYPE_BG);

	return S_OK;
}
//---------------------------------------------------
//終了
//---------------------------------------------------
void CBg::Uninit(void)
{
	//終了
	Release();
}
//---------------------------------------------------
//更新
//---------------------------------------------------
void CBg::Update(void)
{
	//更新
	m_apScene2D[TYPE_FARST_BG]->Update();
	m_apScene2D[TYPE_SECOUND_BG]->Update();
	m_apScene2D[TYPE_THIRD_BG]->Update();
	//
	//キーボード取得
	CInputKeyboard * pInputKeyboard = CSceneManager::GetInputKeyboard();
	//コントローラー取得
	DIJOYSTATE js;
	CInputJoystick * pInputJoystick = CSceneManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();
	//プレイヤーの取得
	CPlayer * pPlayer = CGame::GetPlayer();
	//プレイヤーの座標取得
	D3DXVECTOR3 PlayerPos;
	PlayerPos = pPlayer->GetPosition();
	int nPlayerState = 0;
	nPlayerState = pPlayer->GetPlayerState();
	//座標の取得
	m_Farstpos = m_apScene2D[TYPE_FARST_BG]->GetPosition();
	m_Secoundpos = m_apScene2D[TYPE_SECOUND_BG]->GetPosition();
	m_Thirdpos = m_apScene2D[TYPE_THIRD_BG]->GetPosition();
	//普通
	m_fmove += 0.005f;
	//遅い
	m_fSlowMove += 0.0005f;
	if (m_fFastMove >= 1.0f)
	{
		m_fFastMove = 0.0f;
	}
	if (m_fmove >= 1.0f)
	{
		m_fmove = 0.0f;
	}
	if (m_fSlowMove >= 1.0f)
	{
		m_fSlowMove = 0.0f;
	}
	m_apScene2D[TYPE_FARST_BG]->SetTexture(m_texsizeX, m_texsizeY + +m_fFastMove, 1.0f , 1.0f);
	m_apScene2D[TYPE_SECOUND_BG]->SetTexture(m_texsizeX, m_texsizeY + +m_fmove, 1.0f , 1.0f);
	m_apScene2D[TYPE_THIRD_BG]->SetTexture(m_texsizeX, m_texsizeY + +m_fSlowMove, 1.0f , 1.0f);
	if (nPlayerState == CPlayer::STATE_NORMAL || nPlayerState == CPlayer::STATE_DAMAGE)
	{
		if (PlayerPos.x >= SCREEN_WIDTH / 2 && PlayerPos.x <= 880)
		{
			m_Farstpos.x -= 0.1f;
		}
		if (PlayerPos.x <= SCREEN_WIDTH / 2 && PlayerPos.x >= 400)
		{
			m_Farstpos.x += 0.1f;
		}
		if (pInputKeyboard->GetKeyboardPress(DIK_A))
		{
			m_move.x = 2.0f;
		}
		if (pInputKeyboard->GetKeyboardPress(DIK_D))
		{
			m_move.x = -2.0f;
		}
		if (pInputKeyboard->GetKeyboardRelease(DIK_A))
		{
			m_move.x = 0.0f;
		}
		if (pInputKeyboard->GetKeyboardRelease(DIK_D))
		{
			m_move.x = 0.0f;
		}
		if (PlayerPos.x >= 880)
		{
			m_move.x = 0.0f;
		}
		if (PlayerPos.x <= 400)
		{
			m_move.x = 0.0f;
		}
	}
	if (nPlayerState == CPlayer::STATE_RESPAWN || nPlayerState == CPlayer::STATE_DEAD)
	{
		m_move.x = 0.0f;
	}
	//一枚目の背景の位置更新
	m_Farstpos.x += m_move.x;
	m_Farstpos.y += m_move.y;
	//二枚目の背景の位置更新
	m_Secoundpos.x += m_move.x;
	m_Secoundpos.y += m_move.y;
	//三枚目の背景の位置更新
	m_Thirdpos.x += m_move.x;
	m_Thirdpos.y += m_move.y;
	//位置更新
	m_apScene2D[TYPE_FARST_BG]->SetPosition(m_Farstpos);
	//位置更新
	m_apScene2D[TYPE_SECOUND_BG]->SetPosition(m_Secoundpos);
	//位置更新
	m_apScene2D[TYPE_THIRD_BG]->SetPosition(m_Thirdpos);
}
//---------------------------------------------------
//描画
//---------------------------------------------------
void CBg::Draw(void)
{
}
