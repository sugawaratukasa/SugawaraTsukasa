//******************************************************************************
// ボムのUI [bomui.cpp]
// Author : 管原　司
//******************************************************************************

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "../System/main.h"
#include "../System/manager.h"
#include "../System/renderer.h"
#include "../System/scene.h"
#include "../System/scene2d.h"
#include "bomui.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define BOM_UI_TEXTURE				( "data/Texture/UI/bom3.png")		// ボムUIテクスチャ
#define NOT_POSESSION_COLOR_VALUE	(D3DXCOLOR(0.3f,0.3f,0.3f,1.0f))	// ボムを所持してない時の色
#define POSESSION_COLOR_VALUE		(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	//	ボムを所持しているときの色
#define BOM_UI_SIZE					(D3DXVECTOR3(40.0f,40.0f,0.0f))		// サイズ
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
	m_pos				= INIT_D3DXVECTOR3;
	m_size				= INIT_D3DXVECTOR3;
	m_nBom_Posession	= INIT_INT;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CBomUI::~CBomUI()
{
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
// テクスチャ読み込み
//******************************************************************************
HRESULT CBomUI::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, BOM_UI_TEXTURE, &m_pTexture);
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
// 初期化関数
//******************************************************************************
HRESULT CBomUI::Init()
{
	// 最大数分繰り返す
	for (int nCnt = INIT_INT; nCnt < MAX_BOM; nCnt++)
	{
		// メモリ確保
		m_apScene2D[nCnt] = new CScene2d(OBJTYPE_UI);

		// カラー設定
		m_apScene2D[nCnt]->SetRGBA(NOT_POSESSION_COLOR_VALUE);

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
	if (m_nBom_Posession == POSESSION_MAX)
	{
		for (int nCount = INIT_INT; nCount < POSESSION_MAX; nCount++)
		{
			m_apScene2D[nCount]->SetRGBA(POSESSION_COLOR_VALUE);
		}
	}
	// 所持数が4の場合
	if (m_nBom_Posession == POSESSION_4)
	{
		for (int nCount = INIT_INT; nCount < POSESSION_4; nCount++)
		{
			m_apScene2D[nCount]->SetRGBA(POSESSION_COLOR_VALUE);
		}
		m_apScene2D[4]->SetRGBA(NOT_POSESSION_COLOR_VALUE);
	}
	// 所持数が3の場合
	if (m_nBom_Posession == POSESSION_3)
	{
		for (int nCount = INIT_INT; nCount < POSESSION_3; nCount++)
		{
			m_apScene2D[nCount]->SetRGBA(POSESSION_COLOR_VALUE);
		}
		m_apScene2D[3]->SetRGBA(NOT_POSESSION_COLOR_VALUE);
		m_apScene2D[4]->SetRGBA(NOT_POSESSION_COLOR_VALUE);
	}
	// 所持数が2の場合
	if (m_nBom_Posession == POSESSION_2)
	{
		for (int nCount = INIT_INT; nCount < POSESSION_2; nCount++)
		{
			m_apScene2D[nCount]->SetRGBA(POSESSION_COLOR_VALUE);
		}
		m_apScene2D[2]->SetRGBA(NOT_POSESSION_COLOR_VALUE);
		m_apScene2D[3]->SetRGBA(NOT_POSESSION_COLOR_VALUE);
		m_apScene2D[4]->SetRGBA(NOT_POSESSION_COLOR_VALUE);
	}
	// 所持数が1の場合
	if (m_nBom_Posession == POSESSION_1)
	{
			m_apScene2D[0]->SetRGBA(POSESSION_COLOR_VALUE);

			for (int nCount = POSESSION_1; nCount < MAX_BOM; nCount++)
			{
				m_apScene2D[nCount]->SetRGBA(NOT_POSESSION_COLOR_VALUE);
				m_apScene2D[nCount]->SetRGBA(NOT_POSESSION_COLOR_VALUE);
				m_apScene2D[nCount]->SetRGBA(NOT_POSESSION_COLOR_VALUE);
				m_apScene2D[nCount]->SetRGBA(NOT_POSESSION_COLOR_VALUE);
			}
	}
	// 所持数が0の場合
	if (m_nBom_Posession == POSESSION_NONE)
	{
		for (int nCount = INIT_INT; nCount < MAX_BOM; nCount++)
		{
			m_apScene2D[nCount]->SetRGBA(NOT_POSESSION_COLOR_VALUE);
		}
	}
}