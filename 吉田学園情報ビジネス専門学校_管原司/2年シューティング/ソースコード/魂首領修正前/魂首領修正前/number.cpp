//=============================================================================
//
// Number
// number.cpp
// Author : 管原司
//
//=============================================================================

//-----------------------------------------------------------------------------
//インクルードファイル
//-----------------------------------------------------------------------------
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "input.h"
#include "inputkeyboard.h"
#include "inputjoystick.h"
#include "player.h"
#include "bullet.h"
#include "sound.h"
#include "number.h"
#include "manager.h"
//-----------------------------------------------------------------------------
//静的メンバ変数宣言
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CNumber::m_pTexture = NULL;
//----------------------------------------------
//コンストラクタ
//----------------------------------------------
CNumber::CNumber()
{
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nSizeX = 0;
	m_nSizeY = 0;
	m_nNumber = 0;
}
//----------------------------------------------
//デストラクタ
//----------------------------------------------
CNumber::~CNumber()
{

}
//----------------------------------------------
//テクスチャ読み込み
//----------------------------------------------
HRESULT CNumber::Load(void)
{
	//レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data/Texture/number000.png", &m_pTexture);
	return S_OK;
}
//---------------------------------------------
//テクスチャの破棄
//---------------------------------------------
void CNumber::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		//テクスチャリリース
		m_pTexture->Release();
		//m_pTextureをNULLに
		m_pTexture = NULL;
	}
}
//---------------------------------------------
//生成関数
//---------------------------------------------
CNumber * CNumber::Create(D3DXVECTOR3 pos,int sizeX, int sizeY)
{
	//CNumberのポインタ
	CNumber * pNumber;
	//メモリ確保
	pNumber = new CNumber;
	//初期化
	pNumber->Init(pos, sizeX, sizeY);
	//pNumberを返す
	return pNumber;
}
//---------------------------------------------
//初　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　期化
//---------------------------------------------
HRESULT CNumber::Init(D3DXVECTOR3 pos, int sizeX, int sizeY)
{
	//レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	//頂点情報を設定
	VERTEX_2D *pVtx;
	//posを代入
	m_pos = pos;
	//サイズX代入
	m_nSizeX = sizeX;
	//サイズY代入
	m_nSizeY = sizeY;
	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + (-m_nSizeX / 2), m_pos.y + (-m_nSizeY / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_nSizeX / 2), m_pos.y + (-m_nSizeY / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + (-m_nSizeX / 2), m_pos.y + (m_nSizeY / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_nSizeX / 2), m_pos.y + (m_nSizeY / 2), 0.0f);
	//rhw
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//頂点カラーの設定 ※いつものやつ
	pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	//テクスチャ
	pVtx[0].tex = D3DXVECTOR2(m_nNumber * 0.10f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_nNumber * 0.10f + 0.10f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(m_nNumber * 0.10f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_nNumber * 0.10f + 0.10f, 1.0f);
	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
	return S_OK;
}
//---------------------------------------------
//終了
//---------------------------------------------
void CNumber::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		//m_pVtxBuffリリース
		m_pVtxBuff->Release();
		//m_pVtxBuffをNULL
		m_pVtxBuff = NULL;
	}
}
//---------------------------------------------
//更新
//---------------------------------------------
void CNumber::Update(void)
{

}
//---------------------------------------------
//描画
//---------------------------------------------
void CNumber::Draw(void)
{
	//レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);
	// ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		NUM_POLYGON);
}
//---------------------------------------------
//セット
//---------------------------------------------
void CNumber::SetNumber(int nNumber)
{
	//nNumber代入
	m_nNumber = nNumber;
	//頂点情報を設定
	VERTEX_2D *pVtx;
	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//テクスチャ
	pVtx[0].tex = D3DXVECTOR2(m_nNumber * 0.10f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_nNumber * 0.10f + 0.10f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(m_nNumber * 0.10f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_nNumber * 0.10f + 0.10f, 1.0f);
	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}