//******************************************************************************
// 狙い撃ち弾 [enemy_traking_bullet.h]
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
#include "player.h"
#include "enemy_traking_bullet.h"
//******************************************************************************
// コンストラクタ
//******************************************************************************
CEnemy_Traking_Bullet::CEnemy_Traking_Bullet(int nPriority)
{
	m_move = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_fAngle = 0.0f;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CEnemy_Traking_Bullet::~CEnemy_Traking_Bullet()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CEnemy_Traking_Bullet * CEnemy_Traking_Bullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DCOLOR col, CBullet::TEX_TYPE textype)
{
	// CNormal_Bulletポインタ
	CEnemy_Traking_Bullet * pEnemy_Traking_Bullet;

	// メモリ確保
	pEnemy_Traking_Bullet = new CEnemy_Traking_Bullet;

	// 弾の情報設定
	pEnemy_Traking_Bullet->SetBullet(pos, rot, size, col, textype, CScene::OBJTYPE_PLAYER_BULLET);

	// 移動量代入
	pEnemy_Traking_Bullet->m_move = move;

	// 初期化
	pEnemy_Traking_Bullet->Init();

	// ポインタを返す
	return pEnemy_Traking_Bullet;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CEnemy_Traking_Bullet::Init(void)
{
	// 初期化
	CBullet::Init();

	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CEnemy_Traking_Bullet::Uninit(void)
{
	// 終了
	CBullet::Uninit();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CEnemy_Traking_Bullet::Update(void)
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

	// プレイヤーの状態取得
	int nPlayerState = 0;
	nPlayerState = pPlayer->GetPlayerState();

	// 角度代入
	float fRad = m_fAngle;
	// CScene型のポインタ
	CScene *pScene = NULL;
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
				if (Collision(pos, size, EnemyPos, EnemySize) == true)
				{
					// 敵にダメージを与える
					((CEnemy*)pScene)->HitEnemy(20);
					// 弾を消す
					Uninit();
					return;
				}
			}
		}
	} while (pScene != NULL);

	// 位置更新
	pos.x += m_move.x * cosf(fRad);
	pos.y += m_move.y * sinf(fRad);

	// 位置座標設定
	SetPosition(pos);
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CEnemy_Traking_Bullet::Draw(void)
{
	// 描画
	CBullet::Draw();
}
//******************************************************************************
// 当たり判定
//******************************************************************************
bool CEnemy_Traking_Bullet::Collision(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 size1, D3DXVECTOR3 size2)
{
	bool bHit = false;  //当たったかどうか

	D3DXVECTOR3 box1Max = D3DXVECTOR3(size1.x / 2, size1.y, size1.z / 2) + pos1;          //ぶつかる側の最大値
	D3DXVECTOR3 box1Min = D3DXVECTOR3(-size1.x / 2, -size1.y, -size1.z / 2) + pos1;       //ぶつかる側の最小値
	D3DXVECTOR3 box2Max = D3DXVECTOR3(size2.x / 2, size2.y / 2, size2.z / 2) + pos2;      //ぶつかられる側の最大値
	D3DXVECTOR3 box2Min = D3DXVECTOR3(-size2.x / 2, -size2.y / 2, -size2.z / 2) + pos2;   //ぶつかられる側の最小値

	if (box1Max.y > box2Min.y&&
		box1Min.y < box2Max.y&&
		box1Max.x > box2Min.x&&
		box1Min.x < box2Max.x&&
		box1Max.z > box2Min.z&&
		box1Min.z < box2Max.z)
	{
		bHit = true;
	}

	return bHit;    //当たったかどうかを返す
}
