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
CEnemy_Traking_Bullet::CEnemy_Traking_Bullet(int nPriority) : CBullet(nPriority)
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
	pEnemy_Traking_Bullet->SetBullet(pos, rot, size, col, textype, CScene::OBJTYPE_ENEMY_BULLET);

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

	//ゲーム取得
	CGame * pGame = CSceneManager::GetGame();

	//プレイヤーの取得
	CPlayer * pPlayer = CGame::GetPlayer();
	
	// プレイヤーの位置座標取得
	D3DXVECTOR3 PlayerPos = pPlayer->GetPosition();

	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();

	m_fAngle = atan2f(PlayerPos.y - pos.y, PlayerPos.x - pos.x);

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

	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();

	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	// ヒット処理判定
	HitPlayer();

	// 角度代入
	float fRad = m_fAngle;

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
// ヒット処理関数
//******************************************************************************
void CEnemy_Traking_Bullet::HitPlayer(void)
{
	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();

	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	//ゲーム取得
	CGame * pGame = CSceneManager::GetGame();

	//プレイヤーの取得
	CPlayer * pPlayer = CGame::GetPlayer();

	// プレイヤーの位置座標取得
	D3DXVECTOR3 PlayerPos = pPlayer->GetPosition();

	// プレイヤーのサイズ取得
	D3DXVECTOR3 PlayerSize = pPlayer->GetCollisionSize();

	// 当たり判定
	if (Collision(pos, PlayerPos, size, PlayerSize) == true)
	{
		// プレイヤーにダメージを与える
		pPlayer->HitPlayer();

		// 弾を消す
		Uninit();
		return;
	}
}