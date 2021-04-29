//******************************************************************************
// 背景 [bg.cpp]
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
#include "bg.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define BG_TEXTURE_1	("data/Texture/BackGround/bg2.png")		// テクスチャ1
#define BG_TEXTURE_2	("data/Texture/BackGround/bg101.png")	// テクスチャ2
#define BG_TEXTURE_3	("data/Texture/BackGround/bg102.png")	// テクスチャ3
#define COLOR_VALUE		(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))		// 色
#define TEXTURE_MOVE	(0.005f)								// 移動量
#define TEXTURE_MOVE2	(0.0005f)								// 移動量２
#define MOVE_MAX		(1.0f)									// 移動量最大値
#define MOVE_MIN		(0.0f)									// 移動量最小値
#define TEX_1			(0.0f)									// テクスチャ1
#define TEX_2			(0.0f)									// テクスチャ2
#define TEX_3			(1.0f)									// テクスチャ3
#define TEX_4			(1.0f)									// テクスチャ4
//******************************************************************************
// 静的メンバ変数
//******************************************************************************
LPDIRECT3DTEXTURE9 CBg::m_apTexture[TYPE_MAX] = {};
//******************************************************************************
// テクスチャ読み込み
//******************************************************************************
HRESULT CBg::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURE_1, &m_apTexture[TYPE_FARST_BG]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURE_2, &m_apTexture[TYPE_SECOUND_BG]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURE_3, &m_apTexture[TYPE_THIRD_BG]);
	return S_OK;
}
//******************************************************************************
// テクスチャ破棄
//******************************************************************************
void CBg::Unload(void)
{
	for (int nCnt = INIT_INT; nCnt < TYPE_MAX; nCnt++)
	{
		// テクスチャの破棄
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}
//******************************************************************************
// 生成関数
//******************************************************************************
CBg * CBg::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ポインタ
	CBg * pBg;

	// メモリ確保
	pBg = new CBg;

	// 位置座標代入
	pBg->m_pos = pos;

	// サイズ代入
	pBg->m_size = size;

	// 初期化
	pBg->Init();

	// ポインタを返す
	return pBg;
}
//******************************************************************************
// コンストラクタ
//******************************************************************************
CBg::CBg(int nPriority) : CScene(nPriority)
{
	memset(m_apScene2D, 0, sizeof(m_apScene2D));
	m_type		= TYPE_NONE;
	m_pos		= INIT_D3DXVECTOR3;
	m_size		= INIT_D3DXVECTOR3;
	m_fSlowMove = INIT_FLOAT;
	m_fmove		= INIT_FLOAT;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CBg::~CBg()
{
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CBg::Init(void)
{
	// メモリ確保
	m_apScene2D[TYPE_FARST_BG] = new CScene2d(OBJTYPE_BG);
	m_apScene2D[TYPE_SECOUND_BG] = new CScene2d(OBJTYPE_BG);
	m_apScene2D[TYPE_THIRD_BG] = new CScene2d(OBJTYPE_BG);

	// 位置座標設定
	m_apScene2D[TYPE_FARST_BG]->SetPosition(m_pos);
	m_apScene2D[TYPE_SECOUND_BG]->SetPosition(m_pos);
	m_apScene2D[TYPE_THIRD_BG]->SetPosition(m_pos);

	// 位置座標設定
	m_apScene2D[TYPE_FARST_BG]->SetSize(m_size);
	m_apScene2D[TYPE_SECOUND_BG]->SetSize(m_size);
	m_apScene2D[TYPE_THIRD_BG]->SetSize(m_size);

	// カラー設定
	m_apScene2D[TYPE_FARST_BG]->SetRGBA(COLOR_VALUE);
	m_apScene2D[TYPE_SECOUND_BG]->SetRGBA(COLOR_VALUE);
	m_apScene2D[TYPE_THIRD_BG]->SetRGBA(COLOR_VALUE);

	// テクスチャの受け渡し
	m_apScene2D[TYPE_FARST_BG]->BindTexture(m_apTexture[TYPE_FARST_BG]);
	m_apScene2D[TYPE_SECOUND_BG]->BindTexture(m_apTexture[TYPE_SECOUND_BG]);
	m_apScene2D[TYPE_THIRD_BG]->BindTexture(m_apTexture[TYPE_THIRD_BG]);

	// オブジェクトタイプの設定
	m_apScene2D[TYPE_FARST_BG]->SetObjType(CScene::OBJTYPE_BG);
	m_apScene2D[TYPE_SECOUND_BG]->SetObjType(CScene::OBJTYPE_BG);
	m_apScene2D[TYPE_THIRD_BG]->SetObjType(CScene::OBJTYPE_BG);

	// 初期化
	m_apScene2D[TYPE_FARST_BG]->Init();
	m_apScene2D[TYPE_SECOUND_BG]->Init();
	m_apScene2D[TYPE_THIRD_BG]->Init();

	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CBg::Uninit(void)
{
	//終了
	Release();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CBg::Update(void)
{
	// 更新
	m_apScene2D[TYPE_FARST_BG]->Update();
	m_apScene2D[TYPE_SECOUND_BG]->Update();
	m_apScene2D[TYPE_THIRD_BG]->Update();

	// 普通
	m_fmove += TEXTURE_MOVE;

	// 遅い
	m_fSlowMove += TEXTURE_MOVE2;

	// テクスチャ移動
	if (m_fmove >= MOVE_MAX)
	{
		m_fmove = MOVE_MIN;
	}
	// テクスチャ移動
	if (m_fSlowMove >= MOVE_MAX)
	{
		m_fSlowMove = MOVE_MIN;
	}

	m_apScene2D[TYPE_SECOUND_BG]->SetTexture(TEX_1, TEX_2 + +m_fmove, TEX_3, TEX_4);
	m_apScene2D[TYPE_THIRD_BG]->SetTexture(TEX_1, TEX_2 + +m_fSlowMove, TEX_3, TEX_4);

}
//******************************************************************************
// 描画関数
//******************************************************************************
void CBg::Draw(void)
{
}