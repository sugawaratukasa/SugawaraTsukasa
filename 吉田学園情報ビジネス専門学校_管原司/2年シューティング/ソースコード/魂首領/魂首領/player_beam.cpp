//******************************************************************************
// 弾 [normal_bullet.cpp]
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
#include "game.h"
#include "bullet.h"
#include "enemy.h"
#include "normal_enemy.h"
#include "player.h"
#include "normal_bullet.h"
#include "player_beam.h"
#include "boss.h"
#include "boss_left.h"
#include "boss_right.h"
#include "score.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define DEATH_COUNT			(15)	// 死亡カウント
#define ENEMY_DAMAGE		(5)		// 敵に与えるダメージ
#define BOSS_MAIN_DAMAGE	(10)	// ボスの中心与えるダメージ
#define BOSS_DAMAGE			(5)		// ボスに与えるダメージ
#define ADD_SCORE			(100)	// スコア加算値
//******************************************************************************
// 静的メンバ変数
//******************************************************************************
bool CPlayer_Beam::m_bUseBeam = true;
//******************************************************************************
// コンストラクタ
//******************************************************************************
CPlayer_Beam::CPlayer_Beam(int nPriority) : CBullet(nPriority)
{
	m_move			= INIT_D3DXVECTOR3;
	m_nDeathCount	= INIT_INT;
	m_bHit			= false;
	m_bUseBeam		= true;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CPlayer_Beam::~CPlayer_Beam()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CPlayer_Beam * CPlayer_Beam::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DCOLOR col, CBullet::TEX_TYPE textype)
{
	// CNormal_Bulletポインタ
	CPlayer_Beam * pPlayer_Beam;

	// メモリ確保
	pPlayer_Beam = new CPlayer_Beam;

	// 弾の情報設定
	pPlayer_Beam->SetBullet(pos, rot, size, col, textype, CScene::OBJTYPE_PLAYER_BULLET);

	// 移動量代入
	pPlayer_Beam->m_move = move;

	// 初期化
	pPlayer_Beam->Init();

	// ポインタを返す
	return pPlayer_Beam;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CPlayer_Beam::Init(void)
{
	// 初期化
	CBullet::Init();

	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CPlayer_Beam::Uninit(void)
{
	// 終了
	CBullet::Uninit();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CPlayer_Beam::Update(void)
{
	// 更新
	CBullet::Update();

	//プレイヤーの取得
	CPlayer * pPlayer = CGame::GetPlayer();

	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();

	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	// x座標をプレイヤーに合わせる
	pos.x = pPlayer->GetPosition().x;

	// ヒット判定
	HitEnemy();
	if (m_bHit == true)
	{
		// インクリメント
		m_nDeathCount++;
		// カウントが15の時
		if (m_nDeathCount == DEATH_COUNT)
		{
			// 終了
			Uninit();
			return;
		}
	}
	// falseの場合
	if (m_bUseBeam == false)
	{
		// 終了
		Uninit();
		return;
	}

	//位置更新
	pos.x += m_move.x;
	pos.y += m_move.y;

	// 位置座標設定
	SetPosition(pos);
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CPlayer_Beam::Draw(void)
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
// ビーム使用状態設定
//******************************************************************************
void CPlayer_Beam::SetUseBeam(bool bUseBeam)
{
	m_bUseBeam = bUseBeam;
}
//******************************************************************************
// ヒット判定処理
//******************************************************************************
void CPlayer_Beam::HitEnemy(void)
{
	//プレイヤーの取得
	CPlayer * pPlayer = CGame::GetPlayer();

	// ボス取得
	CBoss * pBoss = CGame::GetBoss();

	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();

	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	// スコアの取得
	CScore * pScore = CGame::GetScore();

	// CScene型のポインタ
	CScene *pScene = NULL;

	// falseの場合
	if (m_bHit == false)
	{
		// 敵の当たり判定
		do
		{
			// オブジェタイプが敵の場合
			pScene = GetScene(OBJTYPE_ENEMY);
			if (pScene != NULL)
			{
				OBJTYPE objType = pScene->GetObjType();
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

						// trueに
						m_bHit = true;
					}
				}
			}
		} while (pScene != NULL);
	}
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

	// ボスの当たり判定
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

	// ボスの当たり判定
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