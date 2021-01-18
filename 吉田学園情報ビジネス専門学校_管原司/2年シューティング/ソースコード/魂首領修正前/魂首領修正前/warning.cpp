//---------------------------------------------------
// Warning
// warning.cpp
// Author:	管原司
//---------------------------------------------------
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
#include "sound.h"
#include "life.h"
#include "game.h"
#include "explosion.h"
#include "bomui.h"
#include "continue.h"
#include "score.h"
#include "boss.h"
#include "enemy.h"
#include "warning.h"
LPDIRECT3DTEXTURE9 CWarning::m_pTexture = NULL;
//------------------------------------------------
//コンストラクタ
//------------------------------------------------
CWarning::CWarning(int nPriority) : CScene2d(nPriority)
{
	m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_bColor = false;
	m_nWarnigCount = 0;
}
//------------------------------------------------
//デストラクタ
//------------------------------------------------
CWarning::~CWarning()
{
}
//------------------------------------------------
//生成関数
//------------------------------------------------
CWarning * CWarning::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//CWarningクラスのポインタ
	CWarning * pWarning;
	//メモリ確保
	pWarning = new CWarning;
	//初期化
	pWarning->Init(pos, rot, sizeX, sizeY);
	return nullptr;
}
//------------------------------------------------
//テクスチャ読み込み
//------------------------------------------------
HRESULT CWarning::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data/Texture/warning.png", &m_pTexture);
	return S_OK;
}
//------------------------------------------------
//テクスチャ破棄
//------------------------------------------------
void CWarning::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
//------------------------------------------------
//初期化関数
//------------------------------------------------
HRESULT CWarning::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//初期化
	CScene2d::Init(pos, rot, sizeX, sizeY);
	SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	BindTexture(m_pTexture);
	SetTexture(0.0f, 0.0f, 1.0f, 1.0f);
	m_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	return S_OK;
}
//------------------------------------------------
//終了関数
//------------------------------------------------
void CWarning::Uninit(void)
{
	//終了
	CScene2d::Uninit();
}
//------------------------------------------------
//更新関数
//------------------------------------------------
void CWarning::Update(void)
{
	//更新
	CScene2d::Update();
	//falseの場合
	if (m_bColor == false)
	{
		m_color.a -= 0.05f;
		if (m_color.a <= 0.1f)
		{
			m_bColor = true;
		}
	}
	//trueの場合
	else
	{
		m_color.a += 0.05f;
		if (m_color.a >= 1.0f)
		{
			m_bColor = false;
		}
		m_nWarnigCount++;
	}
	if (m_nWarnigCount == 50)
	{
		//ボス取得
		CBoss *pBoss = CGame::GetBoss();
		pBoss->SetBoss(1);
		//終了
		Uninit();
		//他の処理を通らないように
		return;
	}
	SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_color.a));
}
//------------------------------------------------
//描画関数
//------------------------------------------------
void CWarning::Draw(void)
{
	//描画
	CScene2d::Draw();
}