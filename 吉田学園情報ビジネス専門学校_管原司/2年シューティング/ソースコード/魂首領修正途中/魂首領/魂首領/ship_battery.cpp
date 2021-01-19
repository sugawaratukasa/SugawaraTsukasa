//******************************************************************************
// 船の砲台 [ship_battery_enemy.cpp]
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
#include "enemy_traking_bullet.h"
#include "game.h"
#include "ship.h"
#include "ship_battery.h"
//******************************************************************************
// コンストラクタ
//******************************************************************************
CShip_Battery::CShip_Battery(int nPriority) : CEnemy(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_nAttackCount = 0;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CShip_Battery::~CShip_Battery()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CShip_Battery * CShip_Battery::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nLife, TEX_TYPE tex_type)
{
	// CShip_Batteryクラスのポインタ
	CShip_Battery * pShip_Battery;

	// メモリ確保
	pShip_Battery = new CShip_Battery;

	// 敵の情報設定
	pShip_Battery->SetEnemy(pos, rot, size, nLife, tex_type, CScene::OBJTYPE_ENEMY);

	// 位置座標代入
	pShip_Battery->m_pos = pos;

	// 初期化
	pShip_Battery->Init();

	// ポインタを返す
	return pShip_Battery;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CShip_Battery::Init(void)
{
	// 初期化
	CEnemy::Init();

	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CShip_Battery::Uninit(void)
{
	// 終了
	CEnemy::Uninit();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CShip_Battery::Update(void)
{
	// 更新
	CEnemy::Update();

	// 船の取得
	CShip * pShip = CGame::GetShip();

	// 船の座標取得
	D3DXVECTOR3 ShipPos;
	ShipPos = pShip->GetPosition();

	// 位置座標設定
	SetPosition(ShipPos + m_pos);

	// 攻撃処理
	Attack();
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CShip_Battery::Draw(void)
{
	// 描画
	CEnemy::Draw();
}
//******************************************************************************
// 攻撃処理関数
//******************************************************************************
void CShip_Battery::Attack(void)
{
	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();

	// プレイヤーの取得
	CPlayer * pPlayer = CGame::GetPlayer();

	// プレイヤーの座標取得
	D3DXVECTOR3 PlayerPos;
	PlayerPos = pPlayer->GetPosition();

	// プレイヤーの情報取得
	int nPlayerState = 0;
	nPlayerState = pPlayer->GetPlayerState();

	if (nPlayerState == CPlayer::STATE_NORMAL || nPlayerState == CPlayer::STATE_DAMAGE)
	{
		// プレイヤーへの角度
		float fAngle = atan2f(PlayerPos.x - pos.x, PlayerPos.y - pos.y);

		// 銃口への半径
		float fLength = SHIP_BATTERY_SIZE.y / 2;

		// 銃口のpos
		D3DXVECTOR3 Battery_Muzle_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// 向き
		D3DXVECTOR3 rot = D3DXVECTOR3(0.0f,0.0f,0.0f);

		// 攻撃カウントインクリメント
		m_nAttackCount++;

		//座標を求める
		Battery_Muzle_Pos.x = pos.x - cosf(fAngle + D3DXToRadian(90.0f)) * fLength;
		Battery_Muzle_Pos.y = pos.y + sinf(fAngle + D3DXToRadian(90.0f)) * fLength;

		//rotに角度を代入
		rot.z = fAngle;

		//向きの設定
		SetRot(rot);

		//攻撃処理
		if (m_nAttackCount % 100 == 0)
		{
			for (int nCount = 0; nCount < 4; nCount++)
			{
				// 4発狙い撃ち弾発射
				CEnemy_Traking_Bullet::Create(D3DXVECTOR3(Battery_Muzle_Pos.x, Battery_Muzle_Pos.y, Battery_Muzle_Pos.z)
					, D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)),
					ENEMY_TRAKING_BULLET_SIZE,
					D3DXVECTOR3(5.0f + nCount, 5.0f + nCount, 0.0f),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					CBullet::TEX_TYPE_ENEMY_NORMAL);
			}
		}
	}
}