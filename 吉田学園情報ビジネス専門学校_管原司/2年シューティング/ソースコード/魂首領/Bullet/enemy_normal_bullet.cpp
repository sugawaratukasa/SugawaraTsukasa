//******************************************************************************
// 敵の弾 [enemy_normal_bullet.cpp]
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
#include "../Enemy/enemy.h"
#include "../Player/player.h"
#include "normal_bullet.h"
#include "enemy_normal_bullet.h"
//******************************************************************************
// コンストラクタ
//******************************************************************************
CEnemy_Normal_Bullet::CEnemy_Normal_Bullet(int nPriority) : CBullet(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CEnemy_Normal_Bullet::~CEnemy_Normal_Bullet()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CEnemy_Normal_Bullet * CEnemy_Normal_Bullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DCOLOR col, CBullet::TEX_TYPE textype)
{
	// CNormal_Bulletポインタ
	CEnemy_Normal_Bullet * pEnemy_Normal_Bullet;

	// メモリ確保
	pEnemy_Normal_Bullet = new CEnemy_Normal_Bullet;

	// 弾の情報設定
	pEnemy_Normal_Bullet->SetBullet(pos, rot, size, col, textype, CScene::OBJTYPE_ENEMY_BULLET);

	// 移動量代入
	pEnemy_Normal_Bullet->m_move = move;

	// 初期化
	pEnemy_Normal_Bullet->Init();

	// ポインタを返す
	return pEnemy_Normal_Bullet;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CEnemy_Normal_Bullet::Init(void)
{
	// 初期化
	CBullet::Init();

	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CEnemy_Normal_Bullet::Uninit(void)
{
	// 終了
	CBullet::Uninit();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CEnemy_Normal_Bullet::Update(void)
{
	// 更新
	CBullet::Update();

	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();

	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	// ヒット処理
	HitPlayer();

	//位置更新
	pos.x += m_move.x;
	pos.y += m_move.y;

	// 位置座標設定
	SetPosition(pos);
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CEnemy_Normal_Bullet::Draw(void)
{
	// 描画
	CBullet::Draw();
}
//******************************************************************************
// ヒット処理関数
//******************************************************************************
void CEnemy_Normal_Bullet::HitPlayer(void)
{
	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();

	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	// CSceneクラスのポインタ
	CScene * pScene = NULL;

	// 敵の当たり判定
	do
	{
		// オブジェタイプが敵の場合
		pScene = GetScene(OBJTYPE_PLAYER);
		if (pScene != NULL)
		{
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_PLAYER)
			{
				// 座標とサイズ取得
				D3DXVECTOR3 PlayerPos = ((CPlayer*)pScene)->GetPosition();
				D3DXVECTOR3 PlayerSize = ((CPlayer*)pScene)->GetCollisionSize();

				// 当たり判定
				if (Collision(pos, PlayerPos, size, PlayerSize) == true)
				{
					// 敵にダメージを与える
					((CPlayer*)pScene)->HitPlayer();
					// 弾を消す
					Uninit();
					return;
				}
			}
		}
	} while (pScene != NULL);
}
