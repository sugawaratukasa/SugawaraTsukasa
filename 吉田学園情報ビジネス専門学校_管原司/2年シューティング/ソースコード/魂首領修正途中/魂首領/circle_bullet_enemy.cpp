//******************************************************************************
// 円形の弾を出す敵 [circle_bullet_enemy.cpp]
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
#include "player.h"
#include "bullet.h"
#include "enemy_normal_bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "game.h"
#include "item.h"
#include "circle_bullet_enemy.h"
//******************************************************************************
// コンストラクタ
//******************************************************************************
CCirecle_Bullet_Enemy::CCirecle_Bullet_Enemy(int nPriority)
{
	m_nAttackCount = 0;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CCirecle_Bullet_Enemy::~CCirecle_Bullet_Enemy()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CCirecle_Bullet_Enemy * CCirecle_Bullet_Enemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nLife, TEX_TYPE tex_type, DROP_ITEM drop_item)
{
	// CNormal_Enemyクラスのポインタ
	CCirecle_Bullet_Enemy * pCirecle_Bullet_Enemy;

	// メモリ確保
	pCirecle_Bullet_Enemy = new CCirecle_Bullet_Enemy;

	// 敵の情報設定
	pCirecle_Bullet_Enemy->SetEnemy(pos, rot, size, nLife, tex_type, CScene::OBJTYPE_ENEMY);

	// 落とすアイテム設定
	pCirecle_Bullet_Enemy->m_DropItem = drop_item;

	// 初期化
	pCirecle_Bullet_Enemy->Init();

	// ポインタを返す
	return pCirecle_Bullet_Enemy;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CCirecle_Bullet_Enemy::Init(void)
{
	// 初期化
	CEnemy::Init();
	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CCirecle_Bullet_Enemy::Uninit(void)
{
	// 終了
	CEnemy::Uninit();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CCirecle_Bullet_Enemy::Update(void)
{
	// 更新
	CEnemy::Update();

	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();

	// 移動量
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 2.0f, 0.0f);

	// 状態取得
	int nState = CEnemy::GetState();

	// インクリメント
	m_nAttackCount++;

	// カウント数が100の場合
	if (m_nAttackCount == 100)
	{
		// 20回繰り返す
		for (int nCount = 0; nCount < 20; nCount++)
		{
			CEnemy_Normal_Bullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)), ENEMY_NORMAL_BULLET_SIZE, D3DXVECTOR3(cosf(D3DXToRadian(nCount * (360 / 20)))*5.0f, sinf(D3DXToRadian(nCount * (360 / 20)))*5.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CBullet::TEX_TYPE_ENEMY_NORMAL);
		}
		// カウント数を0にする
		m_nAttackCount = 0;
	}

	// 死亡状態なら
	if (nState == STATE_DEATH)
	{
		if (m_DropItem == DROP_ITEM_POWERUP)
		{

		}
		if (m_DropItem == DROP_ITEM_BOM)
		{

		}
	}
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CCirecle_Bullet_Enemy::Draw(void)
{
	// 描画
	CEnemy::Draw();
}