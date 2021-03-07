//******************************************************************************
// ボス戦用のボム [boss_bom.h]
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
#include "player.h"
#include "enemy.h"
#include "normal_enemy.h"
#include "circle_bullet_enemy.h"
#include "bom.h"
#include "boss_bom.h"
#include "boss.h"
#include "boss_left.h"
#include "boss_right.h"
#include "score.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define COLOR				(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	// 色
#define ADD_SCORE			(100)								// 加算スコア
#define BOSS_MAIN_DAMAGE	(20)								// ボスに中心に与えるダメージ
#define BOSS_DAMAGE			(10)								// ボスに与えるダメージ
//******************************************************************************
// 静的メンバ変数
//******************************************************************************
bool CBoss_Bom::m_bUseBoss_Bom = true;
//******************************************************************************
// コンストラクタ
//******************************************************************************
CBoss_Bom::CBoss_Bom(int nPriority) : CBullet(nPriority)
{
	m_move			= INIT_D3DXVECTOR3;
	m_bUseBoss_Bom	= true;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CBoss_Bom::~CBoss_Bom()
{
}
//******************************************************************************
// 初期化関数
//******************************************************************************
CBoss_Bom * CBoss_Bom::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXVECTOR3 move, CBullet::TEX_TYPE textype)
{
	// CNormal_Bulletポインタ
	CBoss_Bom * pBoss_Bom;

	// メモリ確保
	pBoss_Bom = new CBoss_Bom;

	// 弾の情報設定
	pBoss_Bom->SetBullet(pos, rot, size, COLOR, textype, CScene::OBJTYPE_PLAYER_BULLET);

	// 移動量代入
	pBoss_Bom->m_move = move;

	// 初期化
	pBoss_Bom->Init();

	// ポインタを返す
	return pBoss_Bom;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CBoss_Bom::Init(void)
{
	// 初期化
	CBullet::Init();

	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CBoss_Bom::Uninit(void)
{
	// 終了
	CBullet::Uninit();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CBoss_Bom::Update(void)
{
	// 更新
	CBullet::Update();;

	//プレイヤーの取得
	CPlayer * pPlayer = CGame::GetPlayer();

	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();

	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	// x座標をプレイヤーに合わせる
	pos.x = pPlayer->GetPosition().x;

	// ヒット判定
	HitBoss();

	// falseの場合
	if (m_bUseBoss_Bom == false)
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
void CBoss_Bom::Draw(void)
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
// 使用状態設定
//******************************************************************************
void CBoss_Bom::SetUseBoss_Bom(bool bUseBoss_Bom)
{
	m_bUseBoss_Bom = bUseBoss_Bom;
}
//******************************************************************************
// ボスのヒット判定処理
//******************************************************************************
void CBoss_Bom::HitBoss(void)
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

	// ボスの位置座標とサイズ取得
	D3DXVECTOR3 BossPos = pBoss->GetPosition();
	D3DXVECTOR3 BossSize = pBoss->GetSize();

	// CScene型のポインタ
	CScene *pScene = NULL;

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
					//スコア加算
					pScore->AddScore(ADD_SCORE);
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
				D3DXVECTOR3 BossSize = ((CBoss*)pScene)->GetCollision_Size();

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