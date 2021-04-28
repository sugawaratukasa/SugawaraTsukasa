//******************************************************************************
// ボム [bom.h]
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
#include "../Mode/game.h"
#include "bullet.h"
#include "../Enemy/enemy.h"
#include "bom.h"
#include "../UI/score.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define ANIM_COUNT				(4)		// アニメーションカウント
#define INIT_ANIM_COUNT			(0)		// アニメーションカウント初期化
#define PATTERN_COUNT			(4)		// パターンカウント
#define PATTERN_COUNT2			(5)		// パターンカウント2
#define PATTERN_COUNT_MAX		(10)	// パターンカウント最大値
#define INIT_TEX				(0.0f)	// テクスチャ初期
#define TEX_X					(0.2f)	// テクスチャX
#define TEX_X2					(0.5f)	// テクスチャX2
#define TEX_Y					(0.5f)	// テクスチャY
#define TEX_Y2					(1.0f)	// テクスチャY2
#define ENEMY_DAMAGE			(100)	// 敵に与えるダメージ
#define ADD_SCORE				(100)	// 加算スコア
//******************************************************************************
// コンストラクタ
//******************************************************************************
CBom::CBom(int nPriority) : CBullet(nPriority)
{
	m_nPatternCount = INIT_INT;
	m_nAnimCount	= INIT_INT;
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

	// テクスチャ設定
	SetTexture(m_nPatternCount * TEX_X, INIT_TEX, TEX_X, TEX_Y);

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
	if (m_nAnimCount > ANIM_COUNT)
	{
		// カウントを0に
		m_nAnimCount = INIT_ANIM_COUNT;

		// パターンが4以下の場合
		if (m_nPatternCount <= PATTERN_COUNT)
		{
			// テクスチャ設定
			SetTexture(m_nPatternCount * TEX_X, INIT_TEX, TEX_X, TEX_Y);
		}
		// パターンが5以上の場合
		if (m_nPatternCount >= PATTERN_COUNT2)
		{
			// テクスチャの設定
			SetTexture(m_nPatternCount * TEX_X, TEX_X2, TEX_X, TEX_Y2);

		}
		// パターンのインクリメント
		m_nPatternCount++;
	}
	// パターンが10以上になったら
	if (m_nPatternCount >= PATTERN_COUNT_MAX)
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
					((CEnemy*)pScene)->HitEnemy(ENEMY_DAMAGE);
					// スコア加算
					pScore->AddScore(ADD_SCORE);
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
					pScore->AddScore(ADD_SCORE);
				}
			}
		}
	} while (pScene != NULL);
}