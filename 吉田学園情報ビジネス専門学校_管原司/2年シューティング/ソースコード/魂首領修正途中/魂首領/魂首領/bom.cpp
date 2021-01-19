//******************************************************************************
// ボム [bom.h]
// Author : 管原　司
//******************************************************************************
//******************************************************************************
// ファイルインクルード
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "game.h"
#include "bullet.h"
#include "enemy.h"
#include "bom.h"
#include "score.h"
//******************************************************************************
// コンストラクタ
//******************************************************************************
CBom::CBom(int nPriority) : CBullet(nPriority)
{
	m_nPatternCount = 0;
	m_nAnimCount	= 0;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CBom::~CBom()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CBom * CBom::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, CBullet::TEX_TYPE textype)
{
	// CNormal_Bulletポインタ
	CBom * pBom;

	// メモリ確保
	pBom = new CBom;

	// 弾の情報設定
	pBom->SetBullet(pos, rot, size, D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), textype, CScene::OBJTYPE_PLAYER_BULLET);

	// テクスチャ設定
	pBom->SetTexture(0.0f, 0.5f, 0.2f, 1.0f);

	// 初期化
	pBom->Init();

	// ポインタを返す
	return pBom;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CBom::Init(void)
{
	// 初期化
	CBullet::Init();

	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CBom::Uninit(void)
{
	// 終了
	CBullet::Uninit();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CBom::Update(void)
{
	// 更新
	CBullet::Update();

	// ヒット判定
	HitEnemy();

	// カウントインクリメント
	m_nAnimCount++;

	//カウントが4以上になったら
	if (m_nAnimCount > 4)
	{
		// カウントを0に
		m_nAnimCount = 0;

		// パターンが4以下の場合
		if (m_nPatternCount <= 4)
		{
			// テクスチャ設定
			SetTexture(m_nPatternCount * 0.2f, 0.0, 0.2f, 0.5f);
		}
		// パターンが5以上の場合
		if (m_nPatternCount >= 5)
		{
			// テクスチャの設定
			SetTexture(m_nPatternCount * 0.2f, 0.5, 0.2f, 1.0f);

		}
		// パターンのインクリメント
		m_nPatternCount++;
	}


	// パターンが10以上になったら
	if (m_nPatternCount >= 10)
	{
		// 終了処理
		Uninit();
		return;
	}
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CBom::Draw(void)
{
	// 描画
	CBullet::Draw();
}
//******************************************************************************
// ヒット判定
//******************************************************************************
void CBom::HitEnemy(void)
{
	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();

	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	// スコアの取得
	CScore * pScore = CGame::GetScore();

	// CScene型のポインタ
	CScene *pScene = NULL;

	// 敵の判定
	do
	{
		// オブジェタイプが敵の場合
		pScene = GetScene(OBJTYPE_ENEMY);

		// NULLチェック
		if (pScene != NULL)
		{
			// オブジェタイプ取得
			OBJTYPE objType = pScene->GetObjType();
			// オブジェクトタイプが敵
			if (objType == OBJTYPE_ENEMY)
			{
				// 座標とサイズ取得
				D3DXVECTOR3 EnemyPos = ((CEnemy*)pScene)->GetPosition();
				D3DXVECTOR3 EnemySize = ((CEnemy*)pScene)->GetSize();

				// 当たり判定
				if (Collision(pos, EnemyPos, size, EnemySize) == true)
				{
					// 敵にダメージを与える
					((CEnemy*)pScene)->HitEnemy(100);
					// スコア加算
					pScore->AddScore(100);
				}
			}
		}
	} while (pScene != NULL);


	// 敵の弾の判定
	do
	{
		// オブジェタイプが敵の場合
		pScene = GetScene(OBJTYPE_ENEMY_BULLET);

		// NULLチェック
		if (pScene != NULL)
		{
			// オブジェタイプ取得
			OBJTYPE objType = pScene->GetObjType();
			// オブジェクトタイプが敵
			if (objType == OBJTYPE_ENEMY_BULLET)
			{
				// 座標とサイズ取得
				D3DXVECTOR3 Enemy_Bullet_Pos = ((CBullet*)pScene)->GetPosition();
				D3DXVECTOR3 Enemy_Bullet_Size = ((CBullet*)pScene)->GetSize();

				// 当たり判定
				if (Collision(pos, Enemy_Bullet_Pos, size, Enemy_Bullet_Size) == true)
				{
					// 敵にダメージを与える
					((CBullet*)pScene)->Uninit();
					// スコア加算
					pScore->AddScore(100);
				}
			}
		}
	} while (pScene != NULL);
}