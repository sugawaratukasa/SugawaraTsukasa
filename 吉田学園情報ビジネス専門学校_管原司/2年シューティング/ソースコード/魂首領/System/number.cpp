//******************************************************************************
// ナンバー処理 [number.cpp]
// Author : 管原　司
//******************************************************************************

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "main.h"
#include "renderer.h"
#include "number.h"
#include "scene.h"
#include "scene2d.h"
#include "manager.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define TEXTURE_X		(0.10f)	// テクスチャX値
#define TEXTURE_Y		(0.0f)	// テクスチャY値
#define TEXTURE_Y2		(1.0f)	// テクスチャY値
#define DEVIDE_VALUE	(2)		// 割る値
//******************************************************************************
// 静的メンバ変数
//******************************************************************************
LPDIRECT3DTEXTURE9 CNumber::m_pTexture = NULL;
//******************************************************************************
// コンストラクタ
//******************************************************************************
CNumber::CNumber()
{
	m_pVtxBuff	= NULL;
	m_pos		= INIT_D3DXVECTOR3;
	m_size		= INIT_D3DXVECTOR3;
	m_nNumber	= INIT_INT;
	m_col		= INIT_COLOR;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CNumber::~CNumber()
{

}
//******************************************************************************
// テクスチャ読み込み
//******************************************************************************
HRESULT CNumber::Load(void)
{
	//レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data/Texture/UI/number000.png", &m_pTexture);
	return S_OK;
}
//******************************************************************************
// テクスチャ破棄
//******************************************************************************
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
//******************************************************************************
// 生成関数
//******************************************************************************
CNumber * CNumber::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col)
{
	// CNumberのポインタ
	CNumber * pNumber;

	// メモリ確保
	pNumber = new CNumber;

	// 位置座標設定
	pNumber->SetPosition(pos);

	// サイズ設定
	pNumber->SetSize(size);

	// カラー設定
	pNumber->SetColor(col);

	//初期化
	pNumber->Init();

	// pNumberを返す
	return pNumber;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CNumber::Init(void)
{
	// レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	// 頂点情報を設定
	VERTEX_2D *pVtx;

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + (-m_size.x/ DEVIDE_VALUE), m_pos.y + (-m_size.y / DEVIDE_VALUE), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / DEVIDE_VALUE), m_pos.y + (-m_size.y / DEVIDE_VALUE), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + (-m_size.x / DEVIDE_VALUE), m_pos.y + (m_size.y / DEVIDE_VALUE), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / DEVIDE_VALUE), m_pos.y + (m_size.y / DEVIDE_VALUE), 0.0f);

	// rhw
	pVtx[0].rhw = RHW_VALUE;
	pVtx[1].rhw = RHW_VALUE;
	pVtx[2].rhw = RHW_VALUE;
	pVtx[3].rhw = RHW_VALUE;

	// 頂点カラーの設定 ※いつものやつ
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// テクスチャ
	pVtx[0].tex = D3DXVECTOR2(m_nNumber * TEXTURE_X, TEXTURE_Y);
	pVtx[1].tex = D3DXVECTOR2(m_nNumber * TEXTURE_X + TEXTURE_X, TEXTURE_Y);
	pVtx[2].tex = D3DXVECTOR2(m_nNumber * TEXTURE_X, TEXTURE_Y2);
	pVtx[3].tex = D3DXVECTOR2(m_nNumber * TEXTURE_X + TEXTURE_X, TEXTURE_Y2);

	// 頂点バッファのアンロック
	m_pVtxBuff->Unlock();
	return S_OK;
}
//******************************************************************************
//終了関数
//******************************************************************************
void CNumber::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		// m_pVtxBuffリリース
		m_pVtxBuff->Release();
		// m_pVtxBuffをNULL
		m_pVtxBuff = NULL;
	}
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CNumber::Update(void)
{
	// 頂点情報を設定
	VERTEX_2D *pVtx;

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + (-m_size.x / DEVIDE_VALUE), m_pos.y + (-m_size.y / DEVIDE_VALUE), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / DEVIDE_VALUE), m_pos.y + (-m_size.y / DEVIDE_VALUE), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + (-m_size.x / DEVIDE_VALUE), m_pos.y + (m_size.y / DEVIDE_VALUE), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / DEVIDE_VALUE), m_pos.y + (m_size.y / DEVIDE_VALUE), 0.0f);

	// rhw
	pVtx[0].rhw = RHW_VALUE;
	pVtx[1].rhw = RHW_VALUE;
	pVtx[2].rhw = RHW_VALUE;
	pVtx[3].rhw = RHW_VALUE;

	// 頂点カラーの設定 ※いつものやつ
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// テクスチャ
	pVtx[0].tex = D3DXVECTOR2(m_nNumber * TEXTURE_X, TEXTURE_Y);
	pVtx[1].tex = D3DXVECTOR2(m_nNumber * TEXTURE_X + TEXTURE_X, TEXTURE_Y);
	pVtx[2].tex = D3DXVECTOR2(m_nNumber * TEXTURE_X, TEXTURE_Y2);
	pVtx[3].tex = D3DXVECTOR2(m_nNumber * TEXTURE_X + TEXTURE_X, TEXTURE_Y2);

	// 頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}
//******************************************************************************
// 描画関数
//******************************************************************************
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
//******************************************************************************
// ナンバー設定
//******************************************************************************
void CNumber::SetNumber(int nNumber)
{
	// nNumber代入
	m_nNumber = nNumber;

	// 頂点情報を設定
	VERTEX_2D *pVtx;

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャ
	pVtx[0].tex = D3DXVECTOR2(m_nNumber * TEXTURE_X, TEXTURE_Y);
	pVtx[1].tex = D3DXVECTOR2(m_nNumber * TEXTURE_X + TEXTURE_X, TEXTURE_Y);
	pVtx[2].tex = D3DXVECTOR2(m_nNumber * TEXTURE_X, TEXTURE_Y2);
	pVtx[3].tex = D3DXVECTOR2(m_nNumber * TEXTURE_X + TEXTURE_X, TEXTURE_Y2);

	// 頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}
//******************************************************************************
// 位置座標設定
//******************************************************************************
void CNumber::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//******************************************************************************
// サイズ設定
//******************************************************************************
void CNumber::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}
//******************************************************************************
// 色設定
//******************************************************************************
void CNumber::SetColor(D3DXCOLOR col)
{
	m_col = col;
}