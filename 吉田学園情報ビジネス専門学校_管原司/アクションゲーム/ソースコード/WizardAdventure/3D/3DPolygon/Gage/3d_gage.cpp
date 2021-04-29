//******************************************************************************
// 3Dゲージ [3d_gage.cpp]
// Author : 管原司
//******************************************************************************

//******************************************************************************
//インクルードファイル
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "3d_gage.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define NOR				(D3DXVECTOR3(0, 1, 0))	// 法線
#define DEVIDE_VALUE	(2.0f)					// 割る値
#define TEX_VALUE		(1.0f)					// テクスチャ値
#define ALPHA			(0)						// 透過値
#define SUB_GAGE		(1)						// ゲージの値を引く値
#define GAGE_MUT		(1.0f)					// 掛ける値
//******************************************************************************
// コンストラクタ
//******************************************************************************
C3D_Gage::C3D_Gage(int nPriority) : CScene(nPriority)
{
	m_pTexture		= NULL;
	m_pVtxBuff		= NULL;
	m_pos			= INIT_D3DXVECTOR3;
	m_rot			= INIT_D3DXVECTOR3;
	m_size			= INIT_D3DXVECTOR3;
	m_col			= INIT_COLOR;
	m_nGageNum		= INIT_INT;
	m_fMaxGageNum	= INIT_FLOAT;
	m_fGageNum		= INIT_FLOAT;
	m_fTex_X		= INIT_FLOAT;
	m_fTex_X2		= INIT_FLOAT;
	m_fTex_Y		= INIT_FLOAT;
	m_fTex_Y2		= INIT_FLOAT;
	m_bDraw			= true;
	memset(m_mtxWorld, NULL, sizeof(m_mtxWorld));
}

//******************************************************************************
// デストラクタ
//******************************************************************************
C3D_Gage::~C3D_Gage()
{
}

//******************************************************************************
// 初期化処理
//******************************************************************************
HRESULT C3D_Gage::Init(void)
{
	// テクスチャ座標を1.0fに設定
	m_fTex_X2 = TEX_VALUE;
	m_fTex_Y2 = TEX_VALUE;

	// floatに変換
	m_fMaxGageNum = m_nGageNum * GAGE_MUT;

	// ゲージの値算出
	m_fGageNum = m_nGageNum / m_fMaxGageNum;

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

	// 位置とサイズ
	pVtx[0].pos = D3DXVECTOR3((-m_size.x / DEVIDE_VALUE),(m_size.y / DEVIDE_VALUE), m_size.z);
	pVtx[1].pos = D3DXVECTOR3((m_size.x / DEVIDE_VALUE) - (m_size.x) * (SUB_GAGE - m_fGageNum),(m_size.y / DEVIDE_VALUE), m_size.z);
	pVtx[2].pos = D3DXVECTOR3((-m_size.x / DEVIDE_VALUE), (-m_size.y / DEVIDE_VALUE), m_size.z);
	pVtx[3].pos = D3DXVECTOR3((m_size.x / DEVIDE_VALUE) - (m_size.x) * (SUB_GAGE - m_fGageNum),(-m_size.y / DEVIDE_VALUE), m_size.z);

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
void C3D_Gage::Uninit(void)
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
void C3D_Gage::Update(void)
{
	// カメラの位置取得
	D3DXVECTOR3 CameraPos = CManager::GetCamera()->GetPos();

	// 頂点情報を設定
	VERTEX_3D *pVtx = NULL;

	// 頂点バッファのロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 位置とサイズ
	pVtx[0].pos = D3DXVECTOR3((-m_size.x / DEVIDE_VALUE), (m_size.y / DEVIDE_VALUE), m_size.z);
	pVtx[1].pos = D3DXVECTOR3((m_size.x / DEVIDE_VALUE) - (m_size.x) * (SUB_GAGE - m_fGageNum), (m_size.y / DEVIDE_VALUE), m_size.z);
	pVtx[2].pos = D3DXVECTOR3((-m_size.x / DEVIDE_VALUE), (-m_size.y / DEVIDE_VALUE), m_size.z);
	pVtx[3].pos = D3DXVECTOR3((m_size.x / DEVIDE_VALUE) - (m_size.x) * (SUB_GAGE - m_fGageNum), (-m_size.y / DEVIDE_VALUE), m_size.z);

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

	// ゲージの値算出
	m_fGageNum = m_nGageNum / m_fMaxGageNum;

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
void C3D_Gage::Draw(void)
{
	// trueの場合
	if (m_bDraw == true)
	{
		// レンダラー取得
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
		D3DXMATRIX mtxRot, mtxTrans; //行列計算用のマトリクス

		//ライト無効
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		// アルファテスト
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, ALPHA);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		// セットテクスチャ
		pDevice->SetTexture(0, m_pTexture);

		// 頂点バッファをデバイスのデータストリームに設定
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		// ワールドマトリクスの初期化
		D3DXMatrixIdentity(&m_mtxWorld);

		// 回転の逆行列
		pDevice->GetTransform(D3DTS_VIEW, &mtxRot);
		D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxRot);

		m_mtxWorld._41 = 0;
		m_mtxWorld._42 = 0;
		m_mtxWorld._43 = 0;

		// 向き反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		// ポリゴン描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		// アルファテスト無効化
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

		// ライト有効
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
}
//******************************************************************************
// 場所
//******************************************************************************
void C3D_Gage::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//******************************************************************************
// 角度
//******************************************************************************
void C3D_Gage::SetRotation(D3DXVECTOR3 rot)
{
	m_rot = rot;
}
//******************************************************************************
// サイズ
//******************************************************************************
void C3D_Gage::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}
//******************************************************************************
// 色設定
//******************************************************************************
void C3D_Gage::SetColor(D3DXCOLOR col)
{
	m_col = col;
}
//******************************************************************************
// テクスチャUV座標設定
//******************************************************************************
void C3D_Gage::SetTexture(float tex_x, float tex_x2, float tex_y, float tex_y2)
{
	m_fTex_X = tex_x;
	m_fTex_X2 = tex_x2;
	m_fTex_Y = tex_y;
	m_fTex_Y2 = tex_y2;
}
//******************************************************************************
// テクスチャ
//******************************************************************************
void C3D_Gage::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}
//******************************************************************************
// 情報設定
//******************************************************************************
void C3D_Gage::SetGage(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, int nGageNum)
{
	// 位置座標設定
	m_pos = pos;

	// 向き設定
	m_rot = rot;

	// サイズ設定
	m_size = size;

	// 色設定
	m_col = col;

	// ゲージの値設定
	m_nGageNum = nGageNum;
}
//******************************************************************************
// ゲージの値設定
//******************************************************************************
void C3D_Gage::SetGageNum(int nGageNum)
{
	m_nGageNum = nGageNum;
}