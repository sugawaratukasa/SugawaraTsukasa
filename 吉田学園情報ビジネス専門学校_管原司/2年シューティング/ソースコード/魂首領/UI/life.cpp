//******************************************************************************
// ライフ処理 [life.cpp]
// Author : 管原 司
//******************************************************************************

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "../System/main.h"
#include "../System/manager.h"
#include "../System/renderer.h"
#include "../System/scene.h"
#include "../System/scene2d.h"
#include "../Player/player.h"
#include "life.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define LIFE_TEXTURE		("data/Texture/UI/PlayerLife.png")	// テクスチャ
#define COLOR_VALUE			(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	// 色の値
#define DAMAGE_COLOR_VALUE	(D3DXCOLOR(0.3f,0.3f,0.3f,1.0f))	// ライフが減っている時の色の値
#define INTERVAL_VALUE		(50.0f)								// ライフの間隔の値
#define LIFE_VALUE_MAX		(3)									// ライフの最大値
#define LIFE_VALUE_2		(2)									// ライフの数値2
#define LIFE_VALUE_1		(1)									// ライフの数値1
#define LIFE_VALUE_MIN		(0)									// ライフの最小値
//******************************************************************************
// 静的メンバ変数
//******************************************************************************
LPDIRECT3DTEXTURE9 CLife::m_pTexture = NULL;
//******************************************************************************
// テクスチャ読み込み
//******************************************************************************
HRESULT CLife::Load(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	// テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, LIFE_TEXTURE, &m_pTexture);
	return S_OK;
}
//******************************************************************************
// テクスチャ破棄
//******************************************************************************
void CLife::Unload(void)
{
	// テクスチャ破棄
	m_pTexture->Release();
	m_pTexture = NULL;
}
//******************************************************************************
// コンストラクタ
//******************************************************************************
CLife::CLife(int nPriority) : CScene(nPriority)
{
	memset(m_apScene2D, 0, sizeof(m_apScene2D));
	m_pos		= INIT_D3DXVECTOR3;
	m_size		= INIT_D3DXVECTOR3;
	m_nNumLife	= INIT_INT;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CLife::~CLife()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CLife * CLife::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CLifeクラスのポインタ
	CLife * pLife;

	// メモリ確保
	pLife = new CLife;

	// 位置座標代入
	pLife->m_pos = pos;

	// サイズ代入
	pLife->m_size = size;

	// 初期化
	pLife->Init();

	// ポインタを返す
	return pLife;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CLife::Init()
{
	// ライフ数を3に
	m_nNumLife = LIFE_VALUE_MAX;

	// 最大数分繰り返す

	for (int nCnt = INIT_INT; nCnt < MAX_LIFE; nCnt++)
	{
		//　メモリ確保
		m_apScene2D[nCnt] = new CScene2d(OBJTYPE_UI);

		// 位置座標設定
		m_apScene2D[nCnt]->SetPosition(D3DXVECTOR3((m_pos.x + INTERVAL_VALUE * nCnt), m_pos.y, m_pos.z));

		// サイズ設定
		m_apScene2D[nCnt]->SetSize(D3DXVECTOR3(m_size));

		// カラー設定
		m_apScene2D[nCnt]->SetRGBA(COLOR_VALUE);

		// テクスチャ受け渡し
		m_apScene2D[nCnt]->BindTexture(m_pTexture);

		//オブジェクトタイプの設定
		m_apScene2D[nCnt]->SetObjType(CScene::OBJTYPE_UI);

		// 初期化
		m_apScene2D[nCnt]->Init();
	}
	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CLife::Uninit(void)
{
	// 終了
	Release();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CLife::Update(void)
{

}
//******************************************************************************
// 描画関数
//******************************************************************************
void CLife::Draw(void)
{
}
//******************************************************************************
// ライフ加算関数
//******************************************************************************
void CLife::AddLife(int nLife)
{
	m_nNumLife = nLife;
	// ライフ設定
	SetLife();
}
//******************************************************************************
// ライフ減算関数
//******************************************************************************
void CLife::HitDamage(int Damage)
{
	m_nNumLife -= Damage;
	// ライフ設定
	SetLife();
}
//******************************************************************************
// ライフ設定関数
//******************************************************************************
void CLife::SetLife(void)
{
	// ライフが3の場合
	if (m_nNumLife == LIFE_VALUE_MAX)
	{
		m_apScene2D[0]->SetRGBA(COLOR_VALUE);
		m_apScene2D[1]->SetRGBA(COLOR_VALUE);
		m_apScene2D[2]->SetRGBA(COLOR_VALUE);
	}
	// ライフが2の場合
	if (m_nNumLife == LIFE_VALUE_2)
	{
		m_apScene2D[2]->SetRGBA(DAMAGE_COLOR_VALUE);
	}
	// ライフが1の場合
	if (m_nNumLife == LIFE_VALUE_1)
	{
		m_apScene2D[1]->SetRGBA(DAMAGE_COLOR_VALUE);
	}
	// ライフが0の場合
	if (m_nNumLife == LIFE_VALUE_MIN)
	{
		m_apScene2D[0]->SetRGBA(DAMAGE_COLOR_VALUE);
	}
}
