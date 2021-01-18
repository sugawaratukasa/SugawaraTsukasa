//******************************************************************************
// 敵 [enemy.cpp]
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
#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "game.h"
#include "item.h"
//******************************************************************************
// 静的メンバ変数
//******************************************************************************
LPDIRECT3DTEXTURE9 CEnemy::m_apTexture[TEX_TYPE_MAX] = {};
//******************************************************************************
// コンストラクタ
//******************************************************************************
CEnemy::CEnemy(int nPriority) : CScene2d(nPriority)
{
	m_TexType = TEX_TYPE_NONE;
	m_state = STATE_NONE;
	m_nLife = 0;

}
//******************************************************************************
// デストラクタ
//******************************************************************************
CEnemy::~CEnemy()
{
}
//******************************************************************************
// テクスチャ読み込み
//******************************************************************************
HRESULT CEnemy::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data/Texture/enemy1.png", &m_apTexture[TEX_TYPE_NORMAL]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/enemy2.png", &m_apTexture[TEX_TYPE_BLUE]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/enemy3.png", &m_apTexture[TEX_TYPE_RED]);
	return S_OK;
}
//******************************************************************************
// テクスチャ破棄
//******************************************************************************
void CEnemy::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_ENEMY_TEX; nCnt++)
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
CEnemy * CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nLife, TEX_TYPE tex_type, CScene::OBJTYPE objtype)
{
	// CEnemyクラスのポインタ
	CEnemy * pEnemy;

	// メモリ確保
	pEnemy = new CEnemy;

	// 初期化
	pEnemy->Init();

	// ポインタを返す
	return pEnemy;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CEnemy::Init(void)
{
	// カラー設定
	SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// テクスチャ設定
	BindTexture(m_apTexture[m_TexType]);

	//初期化
	CScene2d::Init();

	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CEnemy::Uninit(void)
{
	//終了
	CScene2d::Uninit();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CEnemy::Update(void)
{
	// 更新
	CScene2d::Update();

	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();

	// Stateがノーマルの場合
	if (m_state == STATE_NORMAL)
	{
		// カラー設定
		SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	// ダメージ状態の場合
	if (m_state == STATE_DAMAGE)
	{
		// インクリメント
		m_nDamageCount++;
		// 2あまり0の時
		if (m_nDamageCount % 2 == 0)
		{
			// カラー設定
			SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		// あまり0の時
		if (m_nDamageCount % 1 == 0)
		{
			// カラー設定赤にする
			SetRGBA(D3DCOLOR_RGBA(255, 0, 0, 255));
		}
		// カウントが10の場合
		if (m_nDamageCount == 10)
		{
			// 状態をNORMALにする
			m_state = STATE_NORMAL;
			m_nDamageCount = 0;
		}
	}

	// ライフが0以下になった場合
	if (m_nLife <= 0)
	{
		// 爆発の生成
		CExplosion::Create(pos, EXPLOSION_SIZE);
		// 終了
		Uninit();
		return;
	}
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CEnemy::Draw(void)
{
	//描画
	CScene2d::Draw();
}
//******************************************************************************
// ヒット処理関数
//******************************************************************************
void CEnemy::HitEnemy(int nDamage)
{
	// ダメージ減算
	m_nLife -= nDamage;
	// stateをダメージに
	m_state = STATE_DAMAGE;
}
//******************************************************************************
// 敵情報の設定
//******************************************************************************
void CEnemy::SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nLife, TEX_TYPE tex_type, CScene::OBJTYPE objtype)
{
	// 位置座標設定
	SetPosition(pos);

	// 向き設定
	SetRot(rot);

	// サイズ設定
	SetSize(size);

	// ライフ設定
	m_nLife = nLife;

	// テクスチャタイプ代入
	m_TexType = tex_type;

	// オブジェタイプ設定
	SetObjType(objtype);
}
