//******************************************************************************
// 弾 [normal_bullet.cpp]
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
#include "normal_enemy.h"
#include "enemy.h"
#include "player.h"
#include "normal_bullet.h"
#include "boss.h"
#include "score.h"
//******************************************************************************
// コンストラクタ
//******************************************************************************
CNormal_Bullet::CNormal_Bullet(int nPriority) : CBullet(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CNormal_Bullet::~CNormal_Bullet()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CNormal_Bullet * CNormal_Bullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DCOLOR col, CBullet::TEX_TYPE textype)
{
	// CNormal_Bulletポインタ
	CNormal_Bullet * pNormalBullet;

	// メモリ確保
	pNormalBullet = new CNormal_Bullet;

	// 弾の情報設定
	pNormalBullet->SetBullet(pos, rot, size, col, textype, CScene::OBJTYPE_PLAYER_BULLET);

	// 移動量代入
	pNormalBullet->m_move = move;

	// 初期化
	pNormalBullet->Init();

	// ポインタを返す
	return pNormalBullet;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CNormal_Bullet::Init(void)
{
	// 初期化
	CBullet::Init();

	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CNormal_Bullet::Uninit(void)
{
	// 終了
	CBullet::Uninit();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CNormal_Bullet::Update(void)
{
	// 更新
	CBullet::Update();

	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();

	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	// ヒット処理
	HitEnemy();

	//位置更新
	pos.x += m_move.x;
	pos.y += m_move.y;

	// 位置座標設定
	SetPosition(pos);
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CNormal_Bullet::Draw(void)
{
	// 描画
	CBullet::Draw();
}
//******************************************************************************
// ヒット判定処理
//******************************************************************************
void CNormal_Bullet::HitEnemy(void)
{
	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();

	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	// スコアの取得
	CScore * pScore = CGame::GetScore();

	//ゲーム取得
	CGame * pGame = CSceneManager::GetGame();

	// ボス取得
	CBoss * pBoss = CGame::GetBoss();

	// CScene型のポインタ
	CScene *pScene = NULL;
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
					((CEnemy*)pScene)->HitEnemy(10);
					// スコア加算
					pScore->AddScore(100);
					// 弾を消す
					Uninit();
					return;
				}
			}
		}
	} while (pScene != NULL);

	// ボスの位置座標とサイズ取得
	D3DXVECTOR3 BossPos = pBoss->GetPosition();
	D3DXVECTOR3 BossSize = pBoss->GetSize();

	// 当たり判定
	if (Collision(pos, BossPos, size, BossPos) == true)
	{
		// ボスにダメージを与える
		pBoss->HitBoss(30);
		// スコア加算
		pScore->AddScore(100);
		// 弾を消す
		Uninit();
		return;
	}
}