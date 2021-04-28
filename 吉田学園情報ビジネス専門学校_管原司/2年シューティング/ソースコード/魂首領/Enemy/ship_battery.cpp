//******************************************************************************
// 船の砲台 [ship_battery_enemy.cpp]
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
#include "../Player/player.h"
#include "../Bullet/bullet.h"
#include "../Bullet/enemy_traking_bullet.h"
#include "../Mode/game.h"
#include "enemy.h"
#include "ship.h"
#include "ship_battery.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define BULLET_MOVE_VALUE			(D3DXVECTOR3(5.0f + nCount,5.0f + nCount,0.0f))		// 弾スピード
#define ENEMY_TRAKING_BULLET_SIZE	(D3DXVECTOR3(20.0f,20.0f,0.0f))						// レベル1の弾のサイズ
#define BULLET_COLOR_VALUE			(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))					// 弾の色
#define BULLET_ROT_VALUE			(D3DXVECTOR3(0.0f,0.0f,0.0f))						// 向きの値
#define BULLET_SHOT_COUNT			(4)													// 発射数
#define ATTACK_COUNT				(100)												// 攻撃カウント
#define HALF_DEVIDE					(2)													// 割る2
#define COUNT_REMAINDER				(0)													// 余り
#define RADIAN						(90.0f)												// 角度
#define ROT_RATE_MOVE				(0.2f)												// 向き

//******************************************************************************
// コンストラクタ
//******************************************************************************
CShip_Battery::CShip_Battery(int nPriority) : CEnemy(nPriority)
{
	m_pos			= INIT_D3DXVECTOR3;
	m_nAttackCount	= INIT_INT;
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

	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	// プレイヤーの取得
	CPlayer * pPlayer = CGame::GetPlayer();

	// プレイヤーの座標取得
	D3DXVECTOR3 PlayerPos = pPlayer->GetPosition();

	// プレイヤーの情報取得
	int nPlayerState = INIT_INT;
	nPlayerState = pPlayer->GetPlayerState();

	// プレイヤーの状態が通常またはダメージ状態の場合
	if (nPlayerState == CPlayer::STATE_NORMAL || nPlayerState == CPlayer::STATE_DAMAGE)
	{
		// プレイヤーへの角度
		float fAngle = atan2f(PlayerPos.x - pos.x, PlayerPos.y - pos.y);

		// 銃口への半径
		float fLength = size.y / HALF_DEVIDE;

		// 銃口のpos
		D3DXVECTOR3 Battery_Muzle_Pos = INIT_D3DXVECTOR3;

		// 向き
		D3DXVECTOR3 rot = GetRot();

		// 前の向き
		D3DXVECTOR3 rotDest = INIT_D3DXVECTOR3;

		// 攻撃カウントインクリメント
		m_nAttackCount++;

		//座標を求める
		Battery_Muzle_Pos.x = pos.x - cosf(fAngle + D3DXToRadian(RADIAN)) * fLength;
		Battery_Muzle_Pos.y = pos.y + sinf(fAngle + D3DXToRadian(RADIAN)) * fLength;

		// 向き
		rotDest.z = fAngle;

		// rotに角度を代入
		rot.z += (rotDest.z - rot.z) * ROT_RATE_MOVE;

		//攻撃処理
		if (m_nAttackCount % ATTACK_COUNT == COUNT_REMAINDER)
		{
			for (int nCount = INIT_INT; nCount < BULLET_SHOT_COUNT; nCount++)
			{
				// 4発狙い撃ち弾発射
				CEnemy_Traking_Bullet::Create(D3DXVECTOR3(Battery_Muzle_Pos.x, Battery_Muzle_Pos.y, Battery_Muzle_Pos.z),
					BULLET_ROT_VALUE,
					ENEMY_TRAKING_BULLET_SIZE,
					BULLET_MOVE_VALUE,
					BULLET_COLOR_VALUE,
					CBullet::TEX_TYPE_ENEMY_NORMAL);
			}
		}
		// 向きの設定
		SetRot(rot);
	}
}