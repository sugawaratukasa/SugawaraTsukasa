//******************************************************************************
// フェード [fade.cpp]
// Author : 管原　司
//******************************************************************************

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "fade.h"
//******************************************************************************
// コンストラクタ
//******************************************************************************
CFade::CFade()
{
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fade = FADE_NONE;
	m_ModeNext = CSceneManager::MODE_NONE;
	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CFade::~CFade()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CFade * CFade::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CSceneManager::MODE mode)
{
	// CFadeクラスのポインタ
	CFade * pFade;

	//メモリ確保
	pFade = new CFade;

	// 位置座標代入
	pFade->m_pos = pos;

	// サイズ代入
	pFade->m_size = size;

	// モード代入
	pFade->m_ModeNext = mode;

	//初期化
	pFade->Init();

	// ポインタを返す
	return pFade;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CFade::Init(void)
{
	// フェードイン状態に
	m_fade = FADE_IN;
	//初期化
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	//頂点情報を設定
	VERTEX_2D *pVtx;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + (-m_size.x / 2), m_pos.y + (-m_size.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y + (-m_size.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + (-m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定 
	pVtx[0].col = m_colorFade;
	pVtx[1].col = m_colorFade;
	pVtx[2].col = m_colorFade;
	pVtx[3].col = m_colorFade;

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CFade::Uninit(void)
{
	//終了
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CFade::Update(void)
{
	//頂点情報を設定
	VERTEX_2D *pVtx;
	//モード
	m_ModeNext = CSceneManager::GetMode();
	//更新
	if (m_fade != FADE_NONE)
	{
		//フェードイン
		if (m_fade == FADE_IN)
		{
			//a値を加算
			m_colorFade.a += FADE_RATE;	
			//画面が黒くなったら
			if (m_colorFade.a >= 1.0f)
			{
				//遷移
				CSceneManager::SetMode(m_ModeNext);
				//フェード終了処理
				m_colorFade.a = 1.0f;
				m_fade = FADE_OUT;
			}
		}
		//フェードアウト
		if (m_fade == FADE_OUT)
		{
			//α値を減算
			m_colorFade.a -= FADE_RATE;
			//画面の透過
			if (m_colorFade.a <= 0.0f)
			{
				//フェード処理切り替え
				m_colorFade.a = 0.0f;
				//モード設定
				m_fade = FADE_IN;
				CSceneManager::StopFade();
			}
		}
		//頂点バッファをロック
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
		//頂点カラーの設定 
		pVtx[0].col = m_colorFade;
		pVtx[1].col = m_colorFade;
		pVtx[2].col = m_colorFade;
		pVtx[3].col = m_colorFade;
		//頂点バッファのアンロック
		m_pVtxBuff->Unlock();
	}
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CFade::Draw(void)
{
	//描画
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	// テクスチャの設定
	pDevice->SetTexture(0, NULL);
	// ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		NUM_POLYGON);
}
