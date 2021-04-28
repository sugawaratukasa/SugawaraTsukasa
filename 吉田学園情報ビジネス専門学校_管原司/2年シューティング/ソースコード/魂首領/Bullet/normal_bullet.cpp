//******************************************************************************
// 弾 [normal_bullet.cpp]
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
#include "../Enemy/normal_enemy.h"
#include "../Enemy/enemy.h"
#include "../Player/player.h"
#include "normal_bullet.h"
#include "../Boss/boss.h"
#include "../Boss/boss_left.h"
#include "../Boss/boss_right.h"
#include "../UI/score.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define ENEMY_DAMAGE			(10)		// 敵に与えるダメージ
#define BOSS_MAIN_DAMAGE		(40)		// ボスの中心に与えるダメージ
#define BOSS_DAMAGE				(20)		// ボスの中心に与えるダメージ
#define ADD_SCORE				(100)		// スコア加算値
//******************************************************************************
// コンストラクタ
//******************************************************************************
CNormal_Bullet::CNormal_Bullet(int nPriority) : CBullet(nPriority)
{
	m_move = INIT_D3DXVECTOR3;
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
	// レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();

	// 加算合成の設定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// 描画
	CBullet::Draw();

	// 元に戻す
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
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
					((CEnemy*)pScene)->HitEnemy(ENEMY_DAMAGE);
					// スコア加算
					pScore->AddScore(ADD_SCORE);
					// 弾を消す
					Uninit();
					return;
				}
			}
		}
	} while (pScene != NULL);

	// ボスの当たり判定
	do
	{
		// オブジェタイプが敵の場合
		pScene = GetScene(OBJTYPE_BOSS);
		if (pScene != NULL)
		{
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_BOSS)
			{
				// 座標とサイズ取得
				D3DXVECTOR3 BossPos = ((CBoss*)pScene)->GetPosition();
				D3DXVECTOR3 BossSize = ((CBoss*)pScene)->GetSize();

				// 当たり判定
				if (Collision(pos, BossPos, size, BossSize) == true)
				{
					// 敵にダメージを与える
					((CBoss*)pScene)->HitBoss(BOSS_MAIN_DAMAGE);
					// スコア加算
					pScore->AddScore(ADD_SCORE);
					// 弾を消す
					Uninit();
					return;
				}
			}
		}
	} while (pScene != NULL);

	// ボスの右当たり判定
	do
	{
		// オブジェタイプが敵の場合
		pScene = GetScene(OBJTYPE_BOSS_RIGHT);
		if (pScene != NULL)
		{
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_BOSS_RIGHT)
			{
				// 座標とサイズ取得
				D3DXVECTOR3 BossRightPos = ((CBoss_Right*)pScene)->GetPosition();
				D3DXVECTOR3 BossRightSize = ((CBoss_Right*)pScene)->GetSize();

				// 当たり判定
				if (Collision(pos, BossRightPos, size, BossRightSize) == true)
				{
					// 敵にダメージを与える
					((CBoss_Right*)pScene)->Hit(BOSS_DAMAGE);
					// スコア加算
					pScore->AddScore(ADD_SCORE);
					// 弾を消す
					Uninit();
					return;
				}
			}
		}
	} while (pScene != NULL);

	// ボスの左当たり判定
	do
	{
		// オブジェタイプが敵の場合
		pScene = GetScene(OBJTYPE_BOSS_LEFT);
		if (pScene != NULL)
		{
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_BOSS_LEFT)
			{
				// 座標とサイズ取得
				D3DXVECTOR3 BossLeftPos = ((CBoss_Left*)pScene)->GetPosition();
				D3DXVECTOR3 BossLeftSize = ((CBoss_Left*)pScene)->GetSize();

				// 当たり判定
				if (Collision(pos, BossLeftPos, size, BossLeftSize) == true)
				{
					// 敵にダメージを与える
					((CBoss_Left*)pScene)->Hit(BOSS_DAMAGE);
					// スコア加算
					pScore->AddScore(ADD_SCORE);
					// 弾を消す
					Uninit();
					return;
				}
			}
		}
	} while (pScene != NULL);
}