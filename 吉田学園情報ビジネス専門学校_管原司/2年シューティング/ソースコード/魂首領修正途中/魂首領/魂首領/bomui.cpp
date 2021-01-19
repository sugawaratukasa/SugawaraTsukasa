//******************************************************************************
// ボムのUI [bomui.cpp]
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
#include "bomui.h"
//******************************************************************************
// 静的メンバ変数
//******************************************************************************
LPDIRECT3DTEXTURE9 CBomUI::m_pTexture = NULL;
//******************************************************************************
// コンストラクタ
//******************************************************************************
CBomUI::CBomUI(int nPriority) : CScene(nPriority)
{
	memset(m_apScene2D, 0, sizeof(m_apScene2D));
	m_pos				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nBom_Posession	= 0;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CBomUI::~CBomUI()
{
}

//******************************************************************************
// テクスチャ読み込み
//******************************************************************************
HRESULT CBomUI::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data/Texture/bom3.png", &m_pTexture);
	return S_OK;
}
//******************************************************************************
// テクスチャ破棄
//******************************************************************************
void CBomUI::Unload(void)
{
	m_pTexture->Release();
	m_pTexture = NULL;
}
//******************************************************************************
// 生成関数
//******************************************************************************
CBomUI * CBomUI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CBomUIクラスのポインタ
	CBomUI * pBomUI;

	// メモリ確保
	pBomUI = new CBomUI;

	// 位置座標代入
	pBomUI->m_pos = pos;

	// サイズ代入
	pBomUI->m_size = size;

	// 初期化
	pBomUI->Init();

	// ポインタを返す
	return pBomUI;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CBomUI::Init()
{
	// 最大数分繰り返す
	for (int nCnt = 0; nCnt < MAX_BOM; nCnt++)
	{
		// メモリ確保
		m_apScene2D[nCnt] = new CScene2d;

		// カラー設定
		m_apScene2D[nCnt]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));

		// テクスチャ受け渡し
		m_apScene2D[nCnt]->BindTexture(m_pTexture);

		// 位置設定
		m_apScene2D[nCnt]->SetPosition(D3DXVECTOR3((m_pos.x + BOM_UI_SIZE.x * nCnt), m_pos.y, m_pos.z));

		// サイズ設定
		m_apScene2D[nCnt]->SetSize(m_size);

		// オブジェクトタイプの設定
		m_apScene2D[nCnt]->SetObjType(CScene::OBJTYPE_UI);

		// 初期化
		m_apScene2D[nCnt]->Init();
	}
	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CBomUI::Uninit(void)
{
	// 終了
	Release();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CBomUI::Update(void)
{

}
//******************************************************************************
// 描画関数
//******************************************************************************
void CBomUI::Draw(void)
{
}
//******************************************************************************
// ボムの所持数設定
//******************************************************************************
void CBomUI::SetBomUI(int mBomPossesion)
{
	// ボムの所持数を取得
	m_nBom_Posession = mBomPossesion;
	
	// 所持数が5の場合
	if (m_nBom_Posession == MAX_BOM)
	{
		for (int nCount = 0; nCount < MAX_BOM; nCount++)
		{
			m_apScene2D[nCount]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
	// 所持数が4の場合
	if (m_nBom_Posession == 4)
	{
		for (int nCount = 0; nCount < 4; nCount++)
		{
			m_apScene2D[nCount]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		m_apScene2D[4]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
	}
	// 所持数が3の場合
	if (m_nBom_Posession == 3)
	{
		for (int nCount = 0; nCount < 3; nCount++)
		{
			m_apScene2D[nCount]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		m_apScene2D[3]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
		m_apScene2D[4]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
	}
	// 所持数が2の場合
	if (m_nBom_Posession == 2)
	{
		for (int nCount = 0; nCount < 2; nCount++)
		{
			m_apScene2D[nCount]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		m_apScene2D[2]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
		m_apScene2D[3]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
		m_apScene2D[4]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
	}
	// 所持数が1の場合
	if (m_nBom_Posession == 1)
	{
			m_apScene2D[0]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			for (int nCount = 1; nCount < MAX_BOM; nCount++)
			{
				m_apScene2D[nCount]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
				m_apScene2D[nCount]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
				m_apScene2D[nCount]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
				m_apScene2D[nCount]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
			}
	}
	// 所持数が0の場合
	if (m_nBom_Posession == 0)
	{
		for (int nCount = 0; nCount < MAX_BOM; nCount++)
		{
			m_apScene2D[nCount]->SetRGBA(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
		}
	}
}