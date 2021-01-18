//---------------------------------------------------
// bom
// bom.cpp
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
#include "bomui.h"
LPDIRECT3DTEXTURE9 CBom::m_pTexture = NULL;
//-----------------------------------------
//コンストラクタ
//-----------------------------------------
CBom::CBom(int nPriority) : CScene(nPriority)
{
	memset(m_apScene2D, 0, sizeof(m_apScene2D));
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nBom_Posession = 0;
}
//-----------------------------------------
//デストラクタ
//-----------------------------------------
CBom::~CBom()
{
}
//-----------------------------------------
//インスタンス生成
//-----------------------------------------
CBom * CBom::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//CPlayerクラスのポインタ
	CBom * pBom;
	//メモリ確保
	pBom = new CBom;
	//初期化
	pBom->Init(pos, rot, sizeX, sizeY);
	return pBom;
}
//-----------------------------------------
//テクスチャ読み込み
//-----------------------------------------
HRESULT CBom::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data/Texture/bom3.png", &m_pTexture);
	return S_OK;
}
//-----------------------------------------
//テクスチャ破棄
//-----------------------------------------
void CBom::Unload(void)
{
	m_pTexture->Release();
	m_pTexture = NULL;
}
//-----------------------------------------
//初期化
//-----------------------------------------
HRESULT CBom::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	m_pos = pos;
	m_nBom_Posession = MAX_BOM;
	for (int nCnt = 0; nCnt < MAX_BOM; nCnt++)
	{
		m_apScene2D[nCnt] = new CScene2d;
		m_apScene2D[nCnt]->Init(pos, rot, sizeX, sizeY);
		m_apScene2D[nCnt]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
		m_apScene2D[nCnt]->BindTexture(m_pTexture);
		m_apScene2D[nCnt]->SetTexture(0.0f, 0.0f, 1.0f, 1.0f);
		m_apScene2D[nCnt]->SetPosition(D3DXVECTOR3((m_pos.x + 40 * nCnt), m_pos.y, m_pos.z));
		//オブジェクトタイプの設定
		m_apScene2D[nCnt]->SetObjType(CScene::OBJTYPE_LIFE);
	}
	return S_OK;
}
//-----------------------------------------
//終了
//-----------------------------------------
void CBom::Uninit(void)
{
	Release();
}
//-----------------------------------------
//更新
//-----------------------------------------
void CBom::Update(void)
{

}
//-----------------------------------------
//描画
//-----------------------------------------
void CBom::Draw(void)
{
}
//-----------------------------------------
//ボムのセット
//-----------------------------------------
void CBom::SetBomUI(int mBomPossesion)
{
	//ボムの所持数を取得
	m_nBom_Posession = mBomPossesion;
	
	if (m_nBom_Posession == MAX_BOM)
	{
		for (int nCount = 0; nCount < MAX_BOM; nCount++)
		{
			m_apScene2D[nCount]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
	if (m_nBom_Posession == 4)
	{
		for (int nCount = 0; nCount < 4; nCount++)
		{
			m_apScene2D[nCount]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		m_apScene2D[4]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
	}
	if (m_nBom_Posession == 3)
	{
		for (int nCount = 0; nCount < 3; nCount++)
		{
			m_apScene2D[nCount]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		m_apScene2D[3]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
		m_apScene2D[4]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
	}
	if (m_nBom_Posession == 2)
	{
		for (int nCount = 0; nCount < 2; nCount++)
		{
			m_apScene2D[nCount]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		m_apScene2D[2]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
		m_apScene2D[3]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
		m_apScene2D[4]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
	}
	if (m_nBom_Posession == 1)
	{
			m_apScene2D[0]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			for (int nCount = 1; nCount < MAX_BOM; nCount++)
			{
				m_apScene2D[nCount]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
				m_apScene2D[nCount]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
				m_apScene2D[nCount]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
				m_apScene2D[nCount]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
			}
	}
	if (m_nBom_Posession == 0)
	{
		for (int nCount = 0; nCount < MAX_BOM; nCount++)
		{
			m_apScene2D[nCount]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
		}
	}
}