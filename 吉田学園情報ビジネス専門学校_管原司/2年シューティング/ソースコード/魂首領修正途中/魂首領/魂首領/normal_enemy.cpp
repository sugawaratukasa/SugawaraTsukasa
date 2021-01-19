//******************************************************************************
// 通常の敵 [normal_enemy.cpp]
// Author : 管原　司
//******************************************************************************
//******************************************************************************
// マクロ定義
//******************************************************************************
#define BULLET_MOVE_VALUE (D3DXVECTOR3(5.0f,5.0f,0.0f))
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "player.h"
#include "bullet.h"
#include "enemy_traking_bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "game.h"
#include "normal_enemy.h"
//******************************************************************************
// コンストラクタ
//******************************************************************************
CNormal_Enemy::CNormal_Enemy(int nPriority) : CEnemy(nPriority)
{
	m_nAttackCount = 0;
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
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 2.0f, 0.0f);

	// インクリメント
	m_nAttackCount++;

	// 60あまり0の時
	if (m_nAttackCount % 60 == 0)
	{
		// 二発生成
		for (int nCount = 0; nCount < 2; nCount++)
		{
			CEnemy_Traking_Bullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z),
				D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)),
				ENEMY_TRAKING_BULLET_SIZE,
				D3DXVECTOR3(BULLET_MOVE_VALUE.x + nCount, BULLET_MOVE_VALUE.y + nCount, BULLET_MOVE_VALUE.z),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				CBullet::TEX_TYPE_ENEMY_NORMAL);
		}
		// カウントを0にする
		m_nAttackCount = 0;
	}

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