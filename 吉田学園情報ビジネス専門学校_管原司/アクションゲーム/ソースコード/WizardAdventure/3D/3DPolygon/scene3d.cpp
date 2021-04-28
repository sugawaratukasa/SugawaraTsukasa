//******************************************************************************
// 3D [scene3d.cpp]
// Author : 管原司
//******************************************************************************

//******************************************************************************
//インクルードファイル
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "scene3d.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define NOR				(D3DXVECTOR3(0, 1, 0))	// 法線
#define DEVIDE_VALUE	(2.0f)					// 割る値
#define TEX_VALUE		(1.0f)					// テクスチャ値
#define SCALE_VALUE		(1.0f)					// 拡大率
//******************************************************************************
// コンストラクタ
//******************************************************************************
CScene3d::CScene3d(int nPriority) :CScene(nPriority)
{
	m_pTexture	= NULL;
	m_pVtxBuff	= NULL;
	m_pos		= INIT_D3DXVECTOR3;
	m_rot		= INIT_D3DXVECTOR3;
	m_size		= INIT_D3DXVECTOR3;
	m_col		= INIT_COLOR;
	m_fTex_X	= INIT_FLOAT;
	m_fTex_X2	= INIT_FLOAT;
	m_fTex_Y	= INIT_FLOAT;
	m_fTex_Y2	= INIT_FLOAT;
	m_fScale	= INIT_FLOAT;
	m_bDraw		= true;
	memset(m_mtxWorld, NULL, sizeof(m_mtxWorld));
}

//******************************************************************************
// デストラクタ
//******************************************************************************
CScene3d::~CScene3d()
{
}

//******************************************************************************
// 初期化処理
//******************************************************************************
HRESULT CScene3d::Init(void)
{
	// テクスチャ座標を1.0fに設定
	m_fTex_X2 = TEX_VALUE;
	m_fTex_Y2 = TEX_VALUE;

	// 拡大率を1.0fに設定
	m_fScale = SCALE_VALUE;

	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_POLYGON,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,																	// 頂点バッファの使用法　
		FVF_VERTEX_3D,																		// 使用する頂点フォーマット
		D3DPOOL_MANAGED,																	// リソースのバッファを保持するメモリクラスを指定
		&m_pVtxBuff,																		// 頂点バッファへのポインタ
		NULL)))																				// NULLに設定
	{
		return E_FAIL;
	}

	// 頂点情報を設定
	VERTEX_3D *pVtx = NULL;

	// 頂点バッファのロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 場所の設定
	pVtx[0].pos = D3DXVECTOR3((-m_size.x / DEVIDE_VALUE), (m_size.y / DEVIDE_VALUE), (-m_size.z / DEVIDE_VALUE)) * m_fScale;
	pVtx[1].pos = D3DXVECTOR3((m_size.x / DEVIDE_VALUE), (m_size.y / DEVIDE_VALUE), (-m_size.z / DEVIDE_VALUE)) * m_fScale;
	pVtx[2].pos = D3DXVECTOR3((-m_size.x / DEVIDE_VALUE), (-m_size.y / DEVIDE_VALUE), (m_size.z / DEVIDE_VALUE)) * m_fScale;
	pVtx[3].pos = D3DXVECTOR3((m_size.x / DEVIDE_VALUE), (-m_size.y / DEVIDE_VALUE), (m_size.z / DEVIDE_VALUE)) * m_fScale;

	// 法線の設定
	pVtx[0].nor = NOR;
	pVtx[1].nor = NOR;
	pVtx[2].nor = NOR;
	pVtx[3].nor = NOR;

	// カラーの設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(m_fTex_X, m_fTex_Y);
	pVtx[1].tex = D3DXVECTOR2(m_fTex_X2, m_fTex_Y);
	pVtx[2].tex = D3DXVECTOR2(m_fTex_X, m_fTex_Y2);
	pVtx[3].tex = D3DXVECTOR2(m_fTex_X2, m_fTex_Y2);

	// 頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//******************************************************************************
// 終了処理
//******************************************************************************
void CScene3d::Uninit(void)
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
// 更新処理
//******************************************************************************
void CScene3d::Update(void)
{
	// カメラの位置取得
	D3DXVECTOR3 CameraPos = CManager::GetCamera()->GetPos();

	// 頂点情報を設定
	VERTEX_3D *pVtx = NULL;

	// 頂点バッファのロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 場所の設定
	pVtx[0].pos = D3DXVECTOR3((-m_size.x / DEVIDE_VALUE), (m_size.y / DEVIDE_VALUE), (-m_size.z / DEVIDE_VALUE)) * m_fScale;
	pVtx[1].pos = D3DXVECTOR3((m_size.x / DEVIDE_VALUE), (m_size.y / DEVIDE_VALUE), (-m_size.z / DEVIDE_VALUE)) * m_fScale;
	pVtx[2].pos = D3DXVECTOR3((-m_size.x / DEVIDE_VALUE), (-m_size.y / DEVIDE_VALUE), (m_size.z / DEVIDE_VALUE)) * m_fScale;
	pVtx[3].pos = D3DXVECTOR3((m_size.x / DEVIDE_VALUE), (-m_size.y / DEVIDE_VALUE), (m_size.z / DEVIDE_VALUE)) * m_fScale;

	// 法線の設定
	pVtx[0].nor = NOR;
	pVtx[1].nor = NOR;
	pVtx[2].nor = NOR;
	pVtx[3].nor = NOR;

	// カラーの設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(m_fTex_X, m_fTex_Y);
	pVtx[1].tex = D3DXVECTOR2(m_fTex_X2, m_fTex_Y);
	pVtx[2].tex = D3DXVECTOR2(m_fTex_X, m_fTex_Y2);
	pVtx[3].tex = D3DXVECTOR2(m_fTex_X2, m_fTex_Y2);

	// 頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	// 描画判定
	// 範囲外の場合
	if (m_pos.x > CameraPos.x + SCREEN_WIDTH / CAMERA_POS_DEVIDE2 || m_pos.x < CameraPos.x - SCREEN_WIDTH / CAMERA_POS_DEVIDE2)
	{
		// trueの場合
		if (m_bDraw == true)
		{
			// falseに
			m_bDraw = false;
		}
	}
	// 範囲内の場合
	if (m_pos.x < CameraPos.x + SCREEN_WIDTH / CAMERA_POS_DEVIDE2 && m_pos.x > CameraPos.x - SCREEN_WIDTH / CAMERA_POS_DEVIDE2)
	{
		// falseの場合
		if (m_bDraw == false)
		{
			// trueに
			m_bDraw = true;
		}
	}
}

//******************************************************************************
// 描画処理
//******************************************************************************
void CScene3d::Draw(void)
{
	// trueの場合
	if (m_bDraw == true)
	{
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		D3DXMATRIX mtxRot, mtxTrans;

		// マトリックス初期化
		D3DXMatrixIdentity(&m_mtxWorld);

		// 向き
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		// 位置
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		// テクスチャ設定
		pDevice->SetTexture(0, m_pTexture);

		// 頂点バッファをデバイスのデータストリームに設定
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		// ポリゴン描画 
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}
//******************************************************************************
// 場所
//******************************************************************************
void CScene3d::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//******************************************************************************
// 角度
//******************************************************************************
void CScene3d::SetRotation(D3DXVECTOR3 rot)
{
	m_rot = rot;
}
//******************************************************************************
// サイズ
//******************************************************************************
void CScene3d::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}
//******************************************************************************
// 色設定
//******************************************************************************
void CScene3d::SetColor(D3DXCOLOR col)
{
	m_col = col;
}
//******************************************************************************
// 拡大率設定
//******************************************************************************
void CScene3d::SetScale(float scale)
{
	m_fScale = scale;
}
//******************************************************************************
// テクスチャUV座標設定
//******************************************************************************
void CScene3d::SetTexture(float tex_x, float tex_x2, float tex_y, float tex_y2)
{
	m_fTex_X = tex_x;
	m_fTex_X2 = tex_x2;
	m_fTex_Y = tex_y;
	m_fTex_Y2 = tex_y2;
}
//******************************************************************************
// テクスチャ
//******************************************************************************
void CScene3d::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}
//******************************************************************************
// 情報設定
//******************************************************************************
void CScene3d::SetPolygon(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col)
{
	// 位置座標設定
	m_pos = pos;

	// 向き設定
	m_rot = rot;

	// サイズ設定
	m_size = size;

	// 色設定
	m_col = col;
}