//******************************************************************************
// 拡散弾 [enemy_diffudion_bullet.cpp]
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
#include "enemy_normal_bullet.h"
#include "enemy_diffusion_bullet.h"
//******************************************************************************
// コンストラクタ
//******************************************************************************
CEnemy_Diffusion_Bullet::CEnemy_Diffusion_Bullet(int nPriority)
{
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
	if (m_nDifCount >= 80)
	{
		// 20回繰り返す
		for (int nCount = 0; nCount < 20; nCount++)
		{
			// 円形弾生成
			CEnemy_Normal_Bullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z),
				D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)),
				D3DXVECTOR3(cosf(D3DXToRadian(nCount * (360 / 20)))*5.0f, sinf(D3DXToRadian(nCount * (360 / 20)))*5.0f, 0.0f),
				ENEMY_NORMAL_BULLET_SIZE,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
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