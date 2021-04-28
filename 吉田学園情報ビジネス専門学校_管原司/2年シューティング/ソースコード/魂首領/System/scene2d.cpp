//******************************************************************************
// Scene2dの処理 [scene2d.cpp]
// Author : 管原　司
//******************************************************************************

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "manager.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define SCALE_VALUE			(1.0f)								// 拡大率値
#define TEXTURE_ANIM_VALUE	(1.0f)								// テクスチャ値
#define DEVIDE_VALUE		(2)									// 除算値
//******************************************************************************
// コンストラクタ
//******************************************************************************
CScene2d::CScene2d(int nPriority) : CScene(nPriority)
{
	m_pTexture	= NULL;
	m_pVtxBuff	= NULL;
	m_pos		= INIT_D3DXVECTOR3;
	m_rot		= INIT_D3DXVECTOR3;
	m_size		= INIT_D3DXVECTOR3;
	m_col		= INIT_COLOR;
	m_fAngle	= INIT_FLOAT;
	m_fLength	= INIT_FLOAT;
	m_fTexX		= INIT_FLOAT;
	m_fTexY		= INIT_FLOAT;
	m_fTexAnimX = INIT_FLOAT;
	m_fTexAnimY = INIT_FLOAT;
	m_fScale	= INIT_FLOAT;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CScene2d::~CScene2d()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CScene2d * CScene2d::Create()
{
	// CScene2dクラスポインタ
	CScene2d * pScene2D;

	// メモリ確保
	pScene2D = new CScene2d;

	// 初期化
	pScene2D->Init();

	// ポインタを返す
	return pScene2D;

}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CScene2d::Init()
{

	m_fTexAnimX = TEXTURE_ANIM_VALUE;
	m_fTexAnimY = TEXTURE_ANIM_VALUE;

	// 角度計算
	m_fAngle = atan2f((m_size.y / DEVIDE_VALUE), (m_size.x / DEVIDE_VALUE));

	// 半径計算
	m_fLength = sqrtf((float)(((m_size.x / DEVIDE_VALUE) * (m_size.x / DEVIDE_VALUE)) + ((m_size.y / DEVIDE_VALUE) * (m_size.y / DEVIDE_VALUE))));

	// 拡大率を1.0fに設定
	m_fScale = SCALE_VALUE;

	//レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	//頂点情報を設定
	VERTEX_2D *pVtx;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 位置座標
	pVtx[0].pos.x = m_pos.x - cosf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	pVtx[0].pos.y = m_pos.y - sinf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + cosf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	pVtx[1].pos.y = m_pos.y - sinf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x - cosf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	pVtx[2].pos.y = m_pos.y + sinf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + cosf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	pVtx[3].pos.y = m_pos.y + sinf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	pVtx[3].pos.z = 0.0f;

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
void CScene2d::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	// リリース
	Release();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CScene2d::Update(void)
{ 
	// レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	// 頂点情報を設定
	VERTEX_2D *pVtx;
	// 頂点バッファをロック
 	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 位置座標
	pVtx[0].pos.x = m_pos.x - cosf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	pVtx[0].pos.y = m_pos.y - sinf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + cosf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	pVtx[1].pos.y = m_pos.y - sinf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x - cosf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	pVtx[2].pos.y = m_pos.y + sinf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + cosf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	pVtx[3].pos.y = m_pos.y + sinf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	pVtx[3].pos.z = 0.0f;

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
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CScene2d::Draw(void)
{
	// レンダラー取得
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
// 位置座標設定関数
//******************************************************************************
void CScene2d::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//******************************************************************************
// UV座標設定関数
//******************************************************************************
void CScene2d::SetTexture(float fTexX, float fTexY, float fTexAnimX ,float fTexAnimY)
{
	m_fTexX = fTexX;
	m_fTexY = fTexY;
	m_fTexAnimX = fTexAnimX;
	m_fTexAnimY = fTexAnimY;
}
//******************************************************************************
// カラー設定関数
//******************************************************************************
void CScene2d::SetRGBA(D3DXCOLOR col)
{
	m_col = col;
}
//******************************************************************************
// 向き設定関数
//******************************************************************************
void CScene2d::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}
//******************************************************************************
// サイズ設定
//******************************************************************************
void CScene2d::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}
//******************************************************************************
// 拡大率設定関数
//******************************************************************************
void CScene2d::SetScale(float fScale)
{
	m_fScale = fScale;
}
//******************************************************************************
// テクスチャ割り当て関数
//******************************************************************************
void CScene2d::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}
