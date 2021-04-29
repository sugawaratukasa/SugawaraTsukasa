//******************************************************************************
// 円形の弾を出す敵 [circle_bullet_enemy.cpp]
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
#include "../Mode/game.h""
#include "../Player/player.h"
#include "../Bullet/bullet.h"
#include "../Bullet/enemy_normal_bullet.h"
#include "enemy.h"
#include "../Mode/game.h"
#include "../Polygon/item.h"
#include "circle_bullet_enemy.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define BULLET_MOVE_VALUE			(D3DXVECTOR3(5.0f,5.0f,0.0f))		// 弾の移動量
#define MOVE_VALUE					(D3DXVECTOR3(0.0f,2.0f,0.0f))		// 移動量
#define BULLET_ROT					(D3DXVECTOR3(0.0f,0.0f,0.0f))		// 弾の向き
#define ITEM_SIZE					(D3DXVECTOR3(40.0f,40.0f,0.0f))		// アイテムサイズ
#define ENEMY_NORMAL_BULLET_SIZE	(D3DXVECTOR3(20.0f,20.0f,0.0f))		// 弾のサイズ
#define BULLET_COLOR				(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	// 弾の色
#define ATTACK_COUNT				(100)								// 攻撃カウント
#define BULLET_NUMBER				(20)								// 弾数
#define BULLET_RADIAN				(360)								// 角度

// 弾の移動
#define BULLET_MOVE		(D3DXVECTOR3(cosf(D3DXToRadian(nCount * (BULLET_RADIAN / BULLET_NUMBER)))*BULLET_MOVE_VALUE.x, sinf(D3DXToRadian(nCount * (BULLET_RADIAN / BULLET_NUMBER)))*BULLET_MOVE_VALUE.y, 0.0f))
//******************************************************************************
// コンストラクタ
//******************************************************************************
CCirecle_Bullet_Enemy::CCirecle_Bullet_Enemy(int nPriority) : CEnemy(nPriority)
{
	m_nAttackCount = INIT_INT;
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
	D3DXVECTOR3 move = MOVE_VALUE;

	// 状態取得
	int nState = CEnemy::GetState();

	// 攻撃処理
	Attack();

	// 死亡状態なら
	if (nState == STATE_DEATH)
	{
		// DROP_ITEM_POWERUPの場合
		if (m_DropItem == DROP_ITEM_POWERUP)
		{
			// パワーアップアイテム生成
			CItem::Create(pos, ITEM_SIZE, CItem::TYPE_POWERUP);
		}
		// DROP_ITEM_BOMの場合
		if (m_DropItem == DROP_ITEM_BOM)
		{
			CItem::Create(pos, ITEM_SIZE, CItem::TYPE_BOM);
		}
	}

	// 移動
	pos.x += move.x;
	pos.y += move.y;

	// 位置座標設定
	SetPosition(pos);
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CCirecle_Bullet_Enemy::Draw(void)
{
	// 描画
	CEnemy::Draw();
}
//******************************************************************************
// 攻撃処理関数
//******************************************************************************
void CCirecle_Bullet_Enemy::Attack(void)
{
	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();

	// インクリメント
	m_nAttackCount++;

	// カウント数が100の場合
	if (m_nAttackCount == ATTACK_COUNT)
	{
		// 20回繰り返す
		for (int nCount = INIT_INT; nCount < BULLET_NUMBER; nCount++)
		{
			// 弾生成
			CEnemy_Normal_Bullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z),
				BULLET_ROT,
				ENEMY_NORMAL_BULLET_SIZE,
				BULLET_MOVE,
				BULLET_COLOR,
				CBullet::TEX_TYPE_ENEMY_NORMAL);
		}
		// カウント数を0にする
		m_nAttackCount = 0;
	}
}