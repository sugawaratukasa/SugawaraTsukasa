//******************************************************************************
// 2D [scene2d.cpp]
// Author : 管原司
//******************************************************************************

//******************************************************************************
//インクルードファイル
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define DEFAULLT_COL	(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	// 標準の色
#define DEFAULT_SCALE	(1.0f)								// 標準の拡大率
//******************************************************************************
//コンストラクタ
//******************************************************************************
CScene2D::CScene2D(int nPriority) :CScene(nPriority)
{
	m_pTexture	= NULL;
	m_pVtxBuff	= NULL;
	m_pos		= INIT_D3DXVECTOR3;
	m_size		= INIT_D3DXVECTOR3;
	m_rot		= INIT_D3DXVECTOR3;
	m_color		= INIT_COLOR;
	m_fAngle	= INIT_FLOAT;
	m_fLength	= INIT_FLOAT;
	m_fScale	= INIT_FLOAT;
}

//******************************************************************************
//デストラクタ
//******************************************************************************
CScene2D::~CScene2D()
{

}

//******************************************************************************
//初期化処理
//******************************************************************************
HRESULT CScene2D::Init(void)
{
	// 拡大率を1.0fに
	m_fScale = DEFAULT_SCALE;

	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX * MAX_POLYGON,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_2D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&m_pVtxBuff,				// 頂点バッファへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	// 頂点情報を設定
	VERTEX_2D *pVtx = NULL;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos.x = m_pos.x - cosf(m_fAngle - m_rot.z) * m_fLength *m_fScale;
	pVtx[0].pos.y = m_pos.y - sinf(m_fAngle - m_rot.z) * m_fLength *m_fScale;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + cosf(m_fAngle + m_rot.z) * m_fLength *m_fScale;
	pVtx[1].pos.y = m_pos.y - sinf(m_fAngle + m_rot.z) * m_fLength *m_fScale;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x - cosf(m_fAngle + m_rot.z) * m_fLength *m_fScale;
	pVtx[2].pos.y = m_pos.y + sinf(m_fAngle + m_rot.z) * m_fLength *m_fScale;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + cosf(m_fAngle - m_rot.z) * m_fLength *m_fScale;
	pVtx[3].pos.y = m_pos.y + sinf(m_fAngle - m_rot.z) * m_fLength *m_fScale;
	pVtx[3].pos.z = 0.0f;

	//rhw
	pVtx[0].rhw = RHW_VALUE;
	pVtx[1].rhw = RHW_VALUE;
	pVtx[2].rhw = RHW_VALUE;
	pVtx[3].rhw = RHW_VALUE;
	//頂点カラーの設定 ※いつものやつ

	pVtx[0].col = m_color;
	pVtx[1].col = m_color;
	pVtx[2].col = m_color;
	pVtx[3].col = m_color;

	//テクスチャ
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//******************************************************************************
// ポリゴンの終了処理
//******************************************************************************
void CScene2D::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	// 破棄
	Release();
}

//******************************************************************************
// ポリゴンの更新処理
//******************************************************************************
void CScene2D::Update(void)
{
	// 頂点情報を設定
	VERTEX_2D *pVtx;
	//角度取得
	m_fAngle = atan2f((m_size.y / 2), (m_size.x / 2));

	//半径取得
	m_fLength = sqrtf((float)(((m_size.x / 2) * (m_size.x / 2)) + ((m_size.y / 2) * (m_size.y / 2))));

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos.x = m_pos.x - cosf(m_fAngle - m_rot.z) * m_fLength *m_fScale;
	pVtx[0].pos.y = m_pos.y - sinf(m_fAngle - m_rot.z) * m_fLength *m_fScale;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + cosf(m_fAngle + m_rot.z) * m_fLength *m_fScale;
	pVtx[1].pos.y = m_pos.y - sinf(m_fAngle + m_rot.z) * m_fLength *m_fScale;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x - cosf(m_fAngle + m_rot.z) * m_fLength *m_fScale;
	pVtx[2].pos.y = m_pos.y + sinf(m_fAngle + m_rot.z) * m_fLength *m_fScale;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + cosf(m_fAngle - m_rot.z) * m_fLength *m_fScale;
	pVtx[3].pos.y = m_pos.y + sinf(m_fAngle - m_rot.z) * m_fLength *m_fScale;
	pVtx[3].pos.z = 0.0f;

	//rhw
	pVtx[0].rhw = RHW_VALUE;
	pVtx[1].rhw = RHW_VALUE;
	pVtx[2].rhw = RHW_VALUE;
	pVtx[3].rhw = RHW_VALUE;

	//頂点カラーの設定 
	pVtx[0].col = m_color;
	pVtx[1].col = m_color;
	pVtx[2].col = m_color;
	pVtx[3].col = m_color;

	//テクスチャ
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
	//位置座標設定
	SetPosition(m_pos);
}

//******************************************************************************
// ポリゴンの描画処理
//******************************************************************************
void CScene2D::Draw(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//******************************************************************************
//テクスチャの設定
//******************************************************************************
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//******************************************************************************
//アルファ値の設定
//******************************************************************************
void CScene2D::SetColor(D3DXCOLOR color)
{
	m_color = color;
}

//******************************************************************************
//向き設定
//******************************************************************************
void CScene2D::SetRotation(D3DXVECTOR3 rot)
{
	m_rot = rot;
}//******************************************************************************
// 拡大率設定
//******************************************************************************
void CScene2D::SetScale(float fScale)
{
	m_fScale = fScale;
}
//******************************************************************************
// 情報設定
//******************************************************************************
void CScene2D::SetPolygon(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR color)
{
	m_pos = pos;
	m_rot = rot;
	m_size = size;
	m_color = color;
}
//******************************************************************************
// 位置座標設定
//******************************************************************************
void CScene2D::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//******************************************************************************
// サイズ設定
//******************************************************************************
void CScene2D::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}