//---------------------------------------------------
// life
// life.cpp
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
#include "explosion.h"
#include "sound.h"
#include "enemy.h"
#include "score.h"
#include "life.h"
LPDIRECT3DTEXTURE9 CLife::m_pTexture = NULL;
//-----------------------------------------
//コンストラクタ
//-----------------------------------------
CLife::CLife(int nPriority) : CScene(nPriority)
{
	memset(m_apScene2D, 0, sizeof(m_apScene2D));
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nNumLife = 0;
}
//-----------------------------------------
//デストラクタ
//-----------------------------------------
CLife::~CLife()
{
}
//-----------------------------------------
//インスタンス生成
//-----------------------------------------
CLife * CLife::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//CPlayerクラスのポインタ
	CLife * pLife;
	//メモリ確保
	pLife = new CLife;
	//初期化
	pLife->Init(pos, rot, sizeX, sizeY);
	return pLife;
}
//-----------------------------------------
//テクスチャ読み込み
//-----------------------------------------
HRESULT CLife::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data/Texture/PlayerLife.png", &m_pTexture);
	return S_OK;
}
//-----------------------------------------
//テクスチャ破棄
//-----------------------------------------
void CLife::Unload(void)
{
	m_pTexture->Release();
	m_pTexture = NULL;
}
//-----------------------------------------
//初期化
//-----------------------------------------
HRESULT CLife::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	m_pos = pos;
	m_nNumLife = PLAYER_LIFE;
	for (int nCnt = 0; nCnt < MAX_LIFE; nCnt++)
	{
		m_apScene2D[nCnt] = new CScene2d;
		m_apScene2D[nCnt]->Init(pos, rot, sizeX, sizeY);
		m_apScene2D[nCnt]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_apScene2D[nCnt]->BindTexture(m_pTexture);
		m_apScene2D[nCnt]->SetTexture(0.0f, 0.0f, 1.0f, 1.0f);
		m_apScene2D[nCnt]->SetPosition(D3DXVECTOR3((m_pos.x + 50 * nCnt), m_pos.y, m_pos.z));
		//オブジェクトタイプの設定
		m_apScene2D[nCnt]->SetObjType(CScene::OBJTYPE_LIFE);
	}
	return S_OK;
}
//-----------------------------------------
//終了
//-----------------------------------------
void CLife::Uninit(void)
{
	Release();
}
//-----------------------------------------
//更新
//-----------------------------------------
void CLife::Update(void)
{
	SetLife();
}
//-----------------------------------------
//描画
//-----------------------------------------
void CLife::Draw(void)
{
}
//-----------------------------------------
//ライフ加算
//-----------------------------------------
void CLife::AddLife(int nLife)
{
	m_nNumLife = nLife;
}
//-----------------------------------------
//ライフの減算
//-----------------------------------------
void CLife::HitDamage(int Damage)
{
	m_nNumLife -= Damage;
}
//-----------------------------------------
//ライフセット
//-----------------------------------------
void CLife::SetLife(void)
{
	//ライフが3の場合
	if (m_nNumLife == 3)
	{
		m_apScene2D[0]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_apScene2D[1]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_apScene2D[2]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	//ライフが2の場合
	if (m_nNumLife == 2)
	{
		m_apScene2D[2]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
	}
	//ライフが1の場合
	if (m_nNumLife == 1)
	{
		m_apScene2D[1]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
	}
	//ライフが0の場合
	if (m_nNumLife == 0)
	{
		m_apScene2D[0]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
	}
}
