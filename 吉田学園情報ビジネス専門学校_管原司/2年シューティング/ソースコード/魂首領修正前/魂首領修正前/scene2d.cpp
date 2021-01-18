//---------------------------------------------------
// Create
// scene2d.cpp
// Author:	管原司
//---------------------------------------------------
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "manager.h"
#include "input.h"
#include "inputkeyboard.h"
//---------------------------------------------------
//生成関数
//---------------------------------------------------
CScene2d * CScene2d::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	CScene2d * pScene2d;
	pScene2d = new CScene2d;
	pScene2d->Init(pos, rot, sizeX, sizeY);
	pScene2d->SetPosition(pos);
	return pScene2d;
}
//---------------------------------------------------
//コンストラクタ
//---------------------------------------------------
CScene2d::CScene2d(int nPriority) : CScene(nPriority)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_nsizeX = 0;
	m_nsizeY = 0;
	m_fAngle = 0.0f;
	m_fLength = 0.0f;
	m_fTexX = 0.0f;
	m_fTexY = 0.0f;
	m_fTexAnimX = 0.0f;
	m_fTexAnimY = 0;
	m_fScale = 0.0f;
	m_nCount = 0;
}
//---------------------------------------------------
//デストラクタ
//---------------------------------------------------
CScene2d::~CScene2d()
{
}
//---------------------------------------------------
//初期化
//---------------------------------------------------
HRESULT CScene2d::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//位置座標
	m_pos = pos;
	//サイズ
	m_nsizeX = sizeX;
	m_nsizeY = sizeY;
	m_rot = rot;
	m_fAngle = atan2f((m_nsizeY / 2), (m_nsizeX / 2));
	m_fLength = sqrtf((float)(((m_nsizeX / 2) * (m_nsizeX / 2)) + ((m_nsizeY / 2) * (m_nsizeY / 2))));
	m_fScale = 1.0f;
	//レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	//頂点情報を設定
	VERTEX_2D *pVtx;
	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

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

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//頂点カラー
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;
	//テクスチャ
	//テクスチャ
	pVtx[0].tex = D3DXVECTOR2(m_fTexX, m_fTexY);
	pVtx[1].tex = D3DXVECTOR2(m_fTexX + m_fTexAnimX, m_fTexY);
	pVtx[2].tex = D3DXVECTOR2(m_fTexX, m_fTexAnimY);
	pVtx[3].tex = D3DXVECTOR2(m_fTexX + m_fTexAnimX, m_fTexAnimY);

	pVtx += 4;
	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
	CScene::SetPosition(pos);
	return S_OK;
}
//---------------------------------------------------
//終了
//---------------------------------------------------
void CScene2d::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	//リリース
	Release();
}
//---------------------------------------------------
//更新
//---------------------------------------------------
void CScene2d::Update(void)
{ 
	//レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//頂点情報を設定
	VERTEX_2D *pVtx;
	//頂点バッファをロック
 	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

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

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//頂点カラーの設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//テクスチャ
	pVtx[0].tex = D3DXVECTOR2(m_fTexX, m_fTexY);
	pVtx[1].tex = D3DXVECTOR2(m_fTexX + m_fTexAnimX, m_fTexY);
	pVtx[2].tex = D3DXVECTOR2(m_fTexX, m_fTexAnimY);
	pVtx[3].tex = D3DXVECTOR2(m_fTexX + m_fTexAnimX, m_fTexAnimY);

	pVtx += 4;
	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
	CScene::SetPosition(m_pos);
}
//---------------------------------------------------
//描画
//---------------------------------------------------
void CScene2d::Draw(void)
{
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
//----------------------------------------------------
//セット
//----------------------------------------------------
void CScene2d::SetPosition(D3DXVECTOR3 pos)
{
	//代入
	m_pos = pos;
}
//----------------------------------------------------
//テクスチャセット
//----------------------------------------------------
void CScene2d::SetTexture(float fTexX, float fTexY, float fTexAnimX ,float fTexAnimY)
{
	//代入
	m_fTexX = fTexX;
	m_fTexY = fTexY;
	m_fTexAnimX = fTexAnimX;
	m_fTexAnimY = fTexAnimY;
}
//----------------------------------------------------
//RGBAのセット
//----------------------------------------------------
void CScene2d::SetRGBA(D3DXCOLOR col)
{
	m_col = col;
}
//----------------------------------------------------
//向きの設定
//----------------------------------------------------
void CScene2d::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}
//----------------------------------------------------
//拡大
//----------------------------------------------------
void CScene2d::SetScale(float fScale)
{
	m_fScale += fScale;
}
//----------------------------------------------------
//テクスチャの割り当て
//----------------------------------------------------
void CScene2d::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	//割り当て
	m_pTexture = pTexture;
}
