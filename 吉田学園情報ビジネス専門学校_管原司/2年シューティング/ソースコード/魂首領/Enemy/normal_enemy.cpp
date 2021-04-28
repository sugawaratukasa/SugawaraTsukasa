//******************************************************************************
// 通常の敵 [normal_enemy.cpp]
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
#include "../Player/player.h"
#include "../Bullet/bullet.h"
#include "../Bullet/enemy_traking_bullet.h"
#include "../Polygon/item.h"
#include "../Particle/particle.h"
#include "../Particle/particle_explosion.h"
#include "enemy.h"
#include "normal_enemy.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define BULLET_MOVE_VALUE			(D3DXVECTOR3(5.0f,5.0f,0.0f))		// 弾の移動量
#define MOVE_VALUE					(D3DXVECTOR3(0.0f,2.0f,0.0f))		// 移動量
#define BULLET_ROT					(D3DXVECTOR3(0.0f,0.0f,0.0f))		// 弾の向き
#define ENEMY_TRAKING_BULLET_SIZE	(D3DXVECTOR3(20.0f,20.0f,0.0f))		// レベル1の弾のサイズ
#define COLOR						(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	// 色
#define ATTACK_COUNT				(60)								// 攻撃カウント
#define BULLET_NUMDER				(2)									// 弾の数
#define INIT_ATTACK_COUNT			(0)									// 攻撃カウント初期化
//******************************************************************************
// コンストラクタ
//******************************************************************************
CNormal_Enemy::CNormal_Enemy(int nPriority) : CEnemy(nPriority)
{
	m_nAttackCount = INIT_INT;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CNormal_Enemy::~CNormal_Enemy()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CNormal_Enemy * CNormal_Enemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nLife, TEX_TYPE tex_type)
{
	// CNormal_Enemyクラスのポインタ
	CNormal_Enemy * pNormal_Enemy;

	// メモリ確保
	pNormal_Enemy = new CNormal_Enemy;

	// 敵の情報設定
	pNormal_Enemy->SetEnemy(pos, rot, size, nLife, tex_type, CScene::OBJTYPE_ENEMY);

	// 初期化
	pNormal_Enemy->Init();

	// ポインタを返す
	return pNormal_Enemy;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CNormal_Enemy::Init(void)
{
	// 初期化
	CEnemy::Init();

	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CNormal_Enemy::Uninit(void)
{
	// 終了
	CEnemy::Uninit();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CNormal_Enemy::Update(void)
{
	// 更新
	CEnemy::Update();

	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();

	// 移動量
	D3DXVECTOR3 move = MOVE_VALUE;

	// 攻撃処理
	Attack();

	// 移動
	pos.y += move.y;

	// 位置座標設定
	SetPosition(pos);
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CNormal_Enemy::Draw(void)
{
	// 描画
	CEnemy::Draw();
}
//******************************************************************************
// 攻撃処理関数
//******************************************************************************
void CNormal_Enemy::Attack(void)
{
	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();

	// インクリメント
	m_nAttackCount++;

	// 60あまり0の時
	if (m_nAttackCount == ATTACK_COUNT)
	{
		// 二発生成
		for (int nCount = INIT_INT; nCount < BULLET_NUMDER; nCount++)
		{
			CEnemy_Traking_Bullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z),
				BULLET_ROT,
				ENEMY_TRAKING_BULLET_SIZE,
				D3DXVECTOR3(BULLET_MOVE_VALUE.x + nCount, BULLET_MOVE_VALUE.y + nCount, BULLET_MOVE_VALUE.z),
				COLOR,
				CBullet::TEX_TYPE_ENEMY_NORMAL);
		}
		// カウントを0にする
		m_nAttackCount = INIT_ATTACK_COUNT;
	}
}