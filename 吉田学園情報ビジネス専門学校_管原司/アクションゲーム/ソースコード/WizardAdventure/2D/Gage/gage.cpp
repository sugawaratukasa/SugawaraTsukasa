//******************************************************************************
// ゲージ [gage.cpp]
// Author : 管原司
//******************************************************************************
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "manager.h"
#include "renderer.h"
#include "gage.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define DEFAULLT_COL	(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	// 標準の色
#define TEX_VALUE		(1.0f)								// テクスチャ値
#define DEVIDE_VALUE	(2)									// 割る値
#define POS_Z			(0.0f)								// Zの値
#define SUB_GAGE		(1)									// ゲージの値を引く値
#define MUT_GAGE		(1.03f)								// ゲージに掛ける値
#define GAGE_MUT		(1.0f)								// 掛ける値
//******************************************************************************
// コンストラクタ
//******************************************************************************
CGage::CGage(int nPriority) : CScene(nPriority)
{
	m_pTexture		= NULL;
	m_pVtxBuff		= NULL;
	m_pos			= INIT_D3DXVECTOR3;
	m_size			= INIT_D3DXVECTOR3;
	m_color			= INIT_COLOR;
	m_nGageNum		= INIT_INT;
	m_fMaxGageNum	= INIT_FLOAT;
	m_fGageNum		= INIT_FLOAT;
	m_fTex_X		= INIT_FLOAT;
	m_fTex_X2		= INIT_FLOAT;
	m_fTex_Y		= INIT_FLOAT;
	m_fTex_Y2		= INIT_FLOAT;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CGage::~CGage()
{
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CGage::Init(void)
{
	// テクスチャ座標を1.0fに設定
	m_fTex_X2 = TEX_VALUE;
	m_fTex_Y2 = TEX_VALUE;

	// floatに変換
	m_fMaxGageNum = m_nGageNum * GAGE_MUT;

	// ゲージの値算出
	m_fGageNum = m_nGageNum / m_fMaxGageNum;

	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX * MAX_POLYGON,// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,																// 頂点バッファの使用法　
		FVF_VERTEX_2D,																	// 使用する頂点フォーマット
		D3DPOOL_MANAGED,																// リソースのバッファを保持するメモリクラスを指定
		&m_pVtxBuff,																	// 頂点バッファへのポインタ
		NULL)))																			// NULLに設定
	{
		return E_FAIL;
	}

	// 頂点情報を設定
	VERTEX_2D *pVtx = NULL;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 位置とサイズ
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + (-m_size.x / DEVIDE_VALUE), m_pos.y + (m_size.y / DEVIDE_VALUE), POS_Z);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / DEVIDE_VALUE) - (m_size.x) * (SUB_GAGE - m_fGageNum), m_pos.y + (m_size.y / DEVIDE_VALUE), POS_Z);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + (-m_size.x / DEVIDE_VALUE), m_pos.y + (-m_size.y / DEVIDE_VALUE), POS_Z);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / DEVIDE_VALUE) - (m_size.x) * (SUB_GAGE - m_fGageNum), m_pos.y + (-m_size.y / DEVIDE_VALUE), POS_Z);

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

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(m_fTex_X, m_fTex_Y);
	pVtx[1].tex = D3DXVECTOR2(m_fTex_X2, m_fTex_Y);
	pVtx[2].tex = D3DXVECTOR2(m_fTex_X, m_fTex_Y2);
	pVtx[3].tex = D3DXVECTOR2(m_fTex_X2, m_fTex_Y2);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CGage::Uninit(void)
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
// 更新関数
//******************************************************************************
void CGage::Update(void)
{
	// 頂点情報を設定
	VERTEX_2D *pVtx = NULL;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 位置とサイズ
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + (-m_size.x / DEVIDE_VALUE), m_pos.y + (m_size.y / DEVIDE_VALUE), POS_Z);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / DEVIDE_VALUE) - (m_size.x) * (SUB_GAGE - m_fGageNum), m_pos.y + (m_size.y / DEVIDE_VALUE), POS_Z);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + (-m_size.x / DEVIDE_VALUE), m_pos.y + (-m_size.y / DEVIDE_VALUE), POS_Z);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / DEVIDE_VALUE) - (m_size.x) * (SUB_GAGE - m_fGageNum), m_pos.y + (-m_size.y / DEVIDE_VALUE), POS_Z);

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

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(m_fTex_X, m_fTex_Y);
	pVtx[1].tex = D3DXVECTOR2(m_fTex_X2, m_fTex_Y);
	pVtx[2].tex = D3DXVECTOR2(m_fTex_X, m_fTex_Y2);
	pVtx[3].tex = D3DXVECTOR2(m_fTex_X2, m_fTex_Y2);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	// ゲージの値算出
	m_fGageNum = m_nGageNum / m_fMaxGageNum;

	//位置座標設定
	SetPosition(m_pos);
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CGage::Draw(void)
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
// テクスチャ受け渡し
//******************************************************************************
void CGage::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}
//******************************************************************************
// テクスチャUV座標設定
//******************************************************************************
void CGage::SetTexture(float tex_x, float tex_x2, float tex_y, float tex_y2)
{
	m_fTex_X	= tex_x;
	m_fTex_X2	= tex_x2;
	m_fTex_Y	= tex_y;
	m_fTex_Y2	= tex_y2;
}
//******************************************************************************
// 位置設定関数
//******************************************************************************
void CGage::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//******************************************************************************
// サイズ設定関数
//******************************************************************************
void CGage::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}
//******************************************************************************
// 色設定関数
//******************************************************************************
void CGage::SetColor(D3DXCOLOR color)
{
	m_color = color;
}
//******************************************************************************
// ゲージ総数設定関数
//******************************************************************************
void CGage::SetGageNum(int nGageNum)
{
	m_nGageNum = nGageNum;
}
//******************************************************************************
// 情報設定関数
//******************************************************************************
void CGage::SetGage(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color, int nGageNum)
{
	// 位置
	m_pos = pos;

	// サイズ
	m_size = size;

	// 色
	m_color = color;

	// ゲージの値
	m_nGageNum = nGageNum;
}