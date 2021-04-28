//******************************************************************************
// 拡散弾 [enemy_diffudion_bullet.cpp]
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
#include "enemy_normal_bullet.h"
#include "enemy_diffusion_bullet.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define BULLET_ROT					(D3DXVECTOR3(0.0f,0.0f,0.0f))		// 弾の向き
#define ENEMY_NORMAL_BULLET_SIZE	(D3DXVECTOR3(20.0f,20.0f,0.0f))		// 弾のサイズ
#define BULLET_COLOR				(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	// 弾の色
#define DIFF_BULLET_COUNT			(80)								// 拡散弾カウント
#define BULLET_NUMBER				(20)								// 弾の数
#define BULLET_SPEED				(5.0f)								// 弾のスピード
#define BULLET_RADIAN				(360)								// 弧度
#define BULLET_RADIAN_DEVIDE		(20)								// 弧度の除算値
//******************************************************************************
// コンストラクタ
//******************************************************************************
CEnemy_Diffusion_Bullet::CEnemy_Diffusion_Bullet(int nPriority) : CBullet(nPriority)
{
	m_nDifCount = INIT_INT;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CEnemy_Diffusion_Bullet::~CEnemy_Diffusion_Bullet()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CEnemy_Diffusion_Bullet * CEnemy_Diffusion_Bullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DCOLOR col, CBullet::TEX_TYPE textype)
{
	// CNormal_Bulletポインタ
	CEnemy_Diffusion_Bullet * pEnemy_Diffusion_Bullet;

	// メモリ確保
	pEnemy_Diffusion_Bullet = new CEnemy_Diffusion_Bullet;

	// 弾の情報設定
	pEnemy_Diffusion_Bullet->SetBullet(pos, rot, size, col, textype, CScene::OBJTYPE_ENEMY_BULLET);

	// 移動量代入
	pEnemy_Diffusion_Bullet->m_move = move;

	// 初期化
	pEnemy_Diffusion_Bullet->Init();

	// ポインタを返す
	return pEnemy_Diffusion_Bullet;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CEnemy_Diffusion_Bullet::Init(void)
{
	// 初期化
	CBullet::Init();

	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CEnemy_Diffusion_Bullet::Uninit(void)
{
	// 終了
	CBullet::Uninit();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CEnemy_Diffusion_Bullet::Update(void)
{
	// 更新
	CBullet::Update();

	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();

	// インクリメント
	m_nDifCount++;

	// カウント80以上の場合
	if (m_nDifCount >= DIFF_BULLET_COUNT)
	{
		// 20回繰り返す
		for (int nCount = INIT_INT; nCount < BULLET_NUMBER; nCount++)
		{
			// 円形弾生成
			CEnemy_Normal_Bullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z),
				BULLET_ROT,
				ENEMY_NORMAL_BULLET_SIZE,
				D3DXVECTOR3(cosf(D3DXToRadian(nCount * (BULLET_RADIAN / BULLET_RADIAN_DEVIDE)))*BULLET_SPEED,
					sinf(D3DXToRadian(nCount * (BULLET_RADIAN / BULLET_RADIAN_DEVIDE)))*BULLET_SPEED, 
					0.0f),
				BULLET_COLOR,
				CBullet::TEX_TYPE_ENEMY_NORMAL);
		}

		//終了
		Uninit();
		return;
	}

	// 移動
	pos.x += m_move.x;
	pos.y += m_move.y;

	// 位置座標更新
	SetPosition(pos);
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CEnemy_Diffusion_Bullet::Draw(void)
{
	// 描画
	CBullet::Draw();
}