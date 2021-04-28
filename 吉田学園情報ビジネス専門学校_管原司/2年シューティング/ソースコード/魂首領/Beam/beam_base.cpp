//******************************************************************************
// ビームのベース [beam_base.cpp]
// Author : 管原　司
//******************************************************************************

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "../System/main.h"
#include "../System/renderer.h"
#include "../System/scene.h"
#include "beam_base.h"
#include "../System/manager.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define SCALE_VALUE			(1.0f)		// 拡大率値
#define TEXTURE_ANIM_VALUE	(1.0f)		// テクスチャ値
#define DEVIDE_VALUE		(2.0f)		// 除算値
#define ADD_SIZE_VALUE		(30.0f)		// サイズ加算量
#define ADD_TEX_VALUE		(0.1f)		// テクスチャ加算量
#define MAX_TEX_Y			(1.0f)		// Yテクスチャの最大値
#define MIN_TEX_Y			(0.0f)		// Yテクスチャの最大値
#define MAX_ANIM_TEX_Y		(2.0f)		// Yテクスチャの最大値
#define MIN_ANIM_TEX_Y		(1.0f)		// Yテクスチャの最大値
//******************************************************************************
// コンストラクタ
//******************************************************************************
CBeam_Base::CBeam_Base(int nPriority) : CScene(nPriority)
{
	m_pTexture		= NULL;
	m_pVtxBuff		= NULL;
	m_pos			= INIT_D3DXVECTOR3;
	m_rot			= INIT_D3DXVECTOR3;
	m_size			= INIT_D3DXVECTOR3;
	m_col			= INIT_COLOR;
	m_fAddSize		= INIT_FLOAT;
	m_fTexX			= INIT_FLOAT;
	m_fTexY			= INIT_FLOAT;
	m_fTexAnimX		= INIT_FLOAT;
	m_fTexAnimY		= INIT_FLOAT;
	m_bAddSize_Stop = false;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CBeam_Base::~CBeam_Base()
{
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CBeam_Base::Init()
{
	// テクスチャの値代入
	m_fTexAnimX = TEXTURE_ANIM_VALUE;
	m_fTexAnimY = TEXTURE_ANIM_VALUE;

	// サイズY代入
	m_fSizeY = m_size.y;

	//レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	//頂点情報を設定
	VERTEX_2D *pVtx;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 場所の設定
	pVtx[0].pos = m_pos + D3DXVECTOR3((-m_size.x / DEVIDE_VALUE), (-m_fSizeY / DEVIDE_VALUE), (m_size.z / DEVIDE_VALUE)) ;
	pVtx[1].pos = m_pos + D3DXVECTOR3((m_size.x / DEVIDE_VALUE), (-m_fSizeY / DEVIDE_VALUE), (m_size.z / DEVIDE_VALUE)) ;
	pVtx[2].pos = m_pos + D3DXVECTOR3((-m_size.x / DEVIDE_VALUE), (m_size.y / DEVIDE_VALUE), (m_size.z / DEVIDE_VALUE));
	pVtx[3].pos = m_pos + D3DXVECTOR3((m_size.x / DEVIDE_VALUE), (m_size.y / DEVIDE_VALUE), (m_size.z / DEVIDE_VALUE));

	pVtx[0].rhw = RHW_VALUE;
	pVtx[1].rhw = RHW_VALUE;
	pVtx[2].rhw = RHW_VALUE;
	pVtx[3].rhw = RHW_VALUE;

	// 頂点カラー
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// テクスチャ
	pVtx[0].tex = D3DXVECTOR2(m_fTexX, m_fTexY);
	pVtx[1].tex = D3DXVECTOR2(m_fTexX + m_fTexAnimX, m_fTexY);
	pVtx[2].tex = D3DXVECTOR2(m_fTexX, m_fTexAnimY);
	pVtx[3].tex = D3DXVECTOR2(m_fTexX + m_fTexAnimX, m_fTexAnimY);

	// 頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CBeam_Base::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		// 破棄
		m_pVtxBuff->Release();

		// NULLに
		m_pVtxBuff = NULL;
	}
	// 破棄
	Release();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CBeam_Base::Update(void)
{
	// レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();

	// 頂点情報を設定
	VERTEX_2D *pVtx;

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 場所の設定
	pVtx[0].pos = m_pos + D3DXVECTOR3((-m_size.x / DEVIDE_VALUE), (-m_fSizeY / DEVIDE_VALUE), (m_size.z / DEVIDE_VALUE));
	pVtx[1].pos = m_pos + D3DXVECTOR3((m_size.x / DEVIDE_VALUE), (-m_fSizeY / DEVIDE_VALUE), (m_size.z / DEVIDE_VALUE));
	pVtx[2].pos = m_pos + D3DXVECTOR3((-m_size.x / DEVIDE_VALUE), (m_size.y / DEVIDE_VALUE), (m_size.z / DEVIDE_VALUE));
	pVtx[3].pos = m_pos + D3DXVECTOR3((m_size.x / DEVIDE_VALUE), (m_size.y / DEVIDE_VALUE), (m_size.z / DEVIDE_VALUE));

	pVtx[0].rhw = RHW_VALUE;
	pVtx[1].rhw = RHW_VALUE;
	pVtx[2].rhw = RHW_VALUE;
	pVtx[3].rhw = RHW_VALUE;

	// 頂点カラーの設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// テクスチャ
	pVtx[0].tex = D3DXVECTOR2(m_fTexX, m_fTexY);
	pVtx[1].tex = D3DXVECTOR2(m_fTexX + m_fTexAnimX, m_fTexY);
	pVtx[2].tex = D3DXVECTOR2(m_fTexX, m_fTexAnimY);
	pVtx[3].tex = D3DXVECTOR2(m_fTexX + m_fTexAnimX, m_fTexAnimY);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
	// 画面外に出た場合
	if (m_pos.y + -m_fSizeY / 2 >= WINDOW_POS_Y)
	{
		// 加算量代入
		m_fAddSize = ADD_SIZE_VALUE;

		// サイズ加算
		m_fSizeY += m_fAddSize;
	}

	// テクスチャ加算
	m_fTexY += ADD_TEX_VALUE;
	m_fTexAnimY += ADD_TEX_VALUE;

	// 1.0f以上の場合
	if (m_fTexY >= MAX_TEX_Y)
	{
		// 0.0fに
		m_fTexY = MIN_TEX_Y;
	}
	// 2.0f以上の場合
	if (m_fTexAnimY >= MAX_ANIM_TEX_Y)
	{
		// 1.0fに
		m_fTexAnimY = MIN_ANIM_TEX_Y;
	}
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CBeam_Base::Draw(void)
{
	// レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	 
	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(NULL, m_pVtxBuff, NULL, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(NULL, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		NUM_POLYGON);
}
//******************************************************************************
// 情報設定
//******************************************************************************
void CBeam_Base::SetBeam(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col)
{
	m_pos = pos;
	m_size = size;
	m_col = col;
}
//******************************************************************************
// 位置座標設定関数
//******************************************************************************
void CBeam_Base::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//******************************************************************************
// UV座標設定関数
//******************************************************************************
void CBeam_Base::SetTexture(float fTexX, float fTexY, float fTexAnimX, float fTexAnimY)
{
	m_fTexX = fTexX;
	m_fTexY = fTexY;
	m_fTexAnimX = fTexAnimX;
	m_fTexAnimY = fTexAnimY;
}
//******************************************************************************
// カラー設定関数
//******************************************************************************
void CBeam_Base::SetRGBA(D3DXCOLOR col)
{
	m_col = col;
}
//******************************************************************************
// 向き設定関数
//******************************************************************************
void CBeam_Base::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}
//******************************************************************************
// サイズ設定
//******************************************************************************
void CBeam_Base::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}
//******************************************************************************
// サイズ設定
//******************************************************************************
void CBeam_Base::SetSizeY(float sizeY)
{
	m_fSizeY = sizeY;
}
//******************************************************************************
// テクスチャ割り当て関数
//******************************************************************************
void CBeam_Base::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}
