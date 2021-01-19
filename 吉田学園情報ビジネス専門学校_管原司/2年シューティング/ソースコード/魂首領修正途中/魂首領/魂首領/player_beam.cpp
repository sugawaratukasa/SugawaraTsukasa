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
#include "enemy.h"
#include "normal_enemy.h"
#include "player.h"
#include "normal_bullet.h"
#include "player_beam.h"
#include "boss.h"
#include "score.h"
//******************************************************************************
// 静的メンバ変数
//******************************************************************************
bool CPlayer_Beam::m_bUseBeam = true;
//******************************************************************************
// コンストラクタ
//******************************************************************************
CPlayer_Beam::CPlayer_Beam(int nPriority) : CBullet(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bUseBeam = true;
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

	//ゲーム取得
	CGame * pGame = CSceneManager::GetGame();

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
	// 描画
	CBullet::Draw();
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
	//ゲーム取得
	CGame * pGame = CSceneManager::GetGame();

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
		pBoss->HitBoss(20);
		// スコア加算
		pScore->AddScore(100);
		// 弾を消す
		Uninit();
		return;
	}
}