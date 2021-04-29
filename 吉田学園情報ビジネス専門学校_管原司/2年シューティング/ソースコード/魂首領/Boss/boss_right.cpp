//******************************************************************************
// ボス右 [boss_right.h]
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
#include "../Bullet/bullet.h"
#include "../Bullet/enemy_traking_bullet.h"
#include "../Bullet/enemy_normal_bullet.h"
#include "../Bullet/enemy_diffusion_bullet.h"
#include "../Player/player.h"
#include "../Mode/game.h"
#include "boss.h"
#include "boss_left.h"
#include "boss_right.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define TEXTURE						("data/Texture/Enemy/BossRight2.png")// テクスチャ
#define BULLET_NORMAL_MOVE_VALUE	(D3DXVECTOR3(2.0f,6.0f,0.0f))		// 通常弾の移動量
#define BULLET_SPINING_MOVE_VALUE	(D3DXVECTOR3(3.0f,3.0f,0.0f))		// 回転弾の移動量
#define BOSS_RIGHT_SIZE				(D3DXVECTOR3(150.0f,150.0f,0.0f))	// ボスの右のサイズ
#define BULLET_ROT					(D3DXVECTOR3(0.0f,0.0f,0.0f))		// 弾の向き
#define ENEMY_NORMAL_BULLET_SIZE	(D3DXVECTOR3(20.0f,20.0f,0.0f))		// 弾のサイズ
#define COLOR						(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	// 色
#define RED_COLOR					(D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))	// 赤色
#define DEVIDE_VALUE				(2)									// 割る量
#define REMAINDER_VALUE				(0)									// 余り
#define DAMAGE_COUNT				(10)								// ダメージカウント
#define INIT_DAMAGE_COUNT			(0)									// ダメージカウント初期化
#define ATTACK_COUNT				(60)								// 攻撃カウント
#define ATTACK_COUNT2				(100)								// 攻撃カウント2
#define BULLET_NUMBER				(2)									// 弾の数
#define BULLET_DEVIDE_BALUE			(3)									// 弾発射間隔
#define BULLET_RADIAN				(360)								// 弾の発射弧度
#define BULLET_RADIAN_DEVIDE		(20)								// 弧度の除算値
// 回転弾
#define ROTATION_BULLET_MOVE		(D3DXVECTOR3(cosf(D3DXToRadian(m_nHalfLife_AttackCount / BULLET_DEVIDE_BALUE * (BULLET_RADIAN / BULLET_RADIAN_DEVIDE)))*BULLET_SPINING_MOVE_VALUE.x,sinf(D3DXToRadian(m_nHalfLife_AttackCount / BULLET_DEVIDE_BALUE * (BULLET_RADIAN / BULLET_RADIAN_DEVIDE)))*BULLET_SPINING_MOVE_VALUE.y,0.0f))
//******************************************************************************
// 静的メンバ変数
//******************************************************************************
LPDIRECT3DTEXTURE9 CBoss_Right::m_pTexture = NULL;
//******************************************************************************
// コンストラクタ
//******************************************************************************
CBoss_Right::CBoss_Right(int nPriority) : CScene2d(nPriority)
{
	m_State					= STATE_NONE;
	m_nAttackCount			= INIT_INT;
	m_nDamageCount			= INIT_INT;
	m_nHalfLife_AttackCount = INIT_INT;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CBoss_Right::~CBoss_Right()
{
}
//******************************************************************************
// テクスチャ読み込み
//******************************************************************************
HRESULT CBoss_Right::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE, &m_pTexture);
	return S_OK;
}
//******************************************************************************
// テクスチャ破棄
//******************************************************************************
void CBoss_Right::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture!= NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
//******************************************************************************
// 生成関数
//******************************************************************************
CBoss_Right * CBoss_Right::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ボスポインタ
	CBoss_Right * pBoss_Right;

	// メモリ確保
	pBoss_Right = new CBoss_Right;

	// 位置座標設定
	pBoss_Right->SetPosition(pos);

	// サイズ設定
	pBoss_Right->SetSize(size);

	// カラー設定
	pBoss_Right->SetRGBA(COLOR);

	// オブジェタイプ設定
	pBoss_Right->SetObjType(OBJTYPE_BOSS_RIGHT);

	// テクスチャ受け渡し
	pBoss_Right->BindTexture(m_pTexture);

	// 初期化
	pBoss_Right->Init();

	// ポインタを返す
	return pBoss_Right;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CBoss_Right::Init(void)
{
	// 状態を通常に
	m_State = STATE_NORMAL;

	// 初期化
	CScene2d::Init();

	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CBoss_Right::Uninit(void)
{
	// 終了
	CScene2d::Uninit();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CBoss_Right::Update(void)
{
	// 更新
	CScene2d::Update();

	// プレイヤーの取得
	CBoss * pBoss = CGame::GetBoss();

	// プレイヤーの位置座標取得
	D3DXVECTOR3 BossPos = pBoss->GetPosition();

	// 状態処理
	State();

	// 攻撃処理
	Attack();

	// 位置座標設定
	SetPosition(D3DXVECTOR3(BossPos.x + BOSS_RIGHT_SIZE.x, BossPos.y, BossPos.z));

}
//******************************************************************************
// 描画関数
//******************************************************************************
void CBoss_Right::Draw(void)
{
	// 描画
	CScene2d::Draw();
}
//******************************************************************************
// ヒット処理関数
//******************************************************************************
void CBoss_Right::Hit(int nDamage)
{
	// プレイヤーの取得
	CBoss * pBoss = CGame::GetBoss();

	// ボスにダメージ
	pBoss->HitBoss(nDamage);

	// ダメージ状態に
	m_State = STATE_DAMAGE;
}
//******************************************************************************
// 状態処理関数
//******************************************************************************
void CBoss_Right::State(void)
{
	// 状態がノーマルの場合
	if (m_State == STATE_NORMAL)
	{
		// カラーを通常にする
		SetRGBA(COLOR);
	}
	// 状態がDamageの場合
	if (m_State == STATE_DAMAGE)
	{
		// カウントインクリメント
		m_nDamageCount++;

		// 赤くする
 		SetRGBA(RED_COLOR);

		//カウントが2あまり0の時
		if (m_nDamageCount % DEVIDE_VALUE == REMAINDER_VALUE)
		{
			// カラーを通常に戻す
			SetRGBA(COLOR);
		}

		// カウントが10になったら
		if (m_nDamageCount == DAMAGE_COUNT)
		{
			// 状態を通常に
			m_State = STATE_NORMAL;

			// カウントが0になったら
			m_nDamageCount = INIT_DAMAGE_COUNT;
		}
	}
}
//******************************************************************************
// 攻撃処理関数
//******************************************************************************
void CBoss_Right::Attack(void)
{
	// ボスの取得
	CBoss * pBoss = CGame::GetBoss();

	// ボスのライフ取得
	bool bHalfLife = pBoss->GetHalfLife();

	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();

	// ボスの状態取得
	int BossState = pBoss->GetState();

	// ボスの通常状態またはダメージ状態の場合
	if (BossState == CBoss::STATE_NORMAL || BossState == CBoss::STATE_DAMAGE)
	{
		// ライフが半分以上の場合
		if (bHalfLife == false)
		{
			// インクリメント
			m_nAttackCount++;

			// 60あまり0の場合
			if (m_nAttackCount % ATTACK_COUNT == REMAINDER_VALUE)
			{
				// 左右2発弾発射
				for (int nCount = INIT_INT; nCount < BULLET_NUMBER; nCount++)
				{
					// 弾生成
					CEnemy_Normal_Bullet::Create(D3DXVECTOR3(pos.x + BOSS_RIGHT_SIZE.x / DEVIDE_VALUE, pos.y + BOSS_RIGHT_SIZE.y / DEVIDE_VALUE, pos.z),
						BULLET_ROT,
						ENEMY_NORMAL_BULLET_SIZE,
						D3DXVECTOR3(-BULLET_NORMAL_MOVE_VALUE.x - nCount, BULLET_NORMAL_MOVE_VALUE.y, 0.0f),
						COLOR,
						CBullet::TEX_TYPE_ENEMY_NORMAL);
				}
			}
		}
		// ライフが半分以下の場合
		if (bHalfLife == true)
		{
			// インクリメント
			m_nHalfLife_AttackCount++;

			// カウントが100以上の場合
			if (m_nHalfLife_AttackCount >= ATTACK_COUNT2)
			{
				// 3あまり0の時
				if (m_nHalfLife_AttackCount % BULLET_DEVIDE_BALUE == REMAINDER_VALUE)
				{
					// 回転弾生成
					CEnemy_Normal_Bullet::Create(D3DXVECTOR3(pos.x + BOSS_RIGHT_SIZE.x / DEVIDE_VALUE, pos.y + BOSS_RIGHT_SIZE.y / DEVIDE_VALUE, pos.z),
						BULLET_ROT,
						ENEMY_NORMAL_BULLET_SIZE,
						ROTATION_BULLET_MOVE,
						COLOR,
						CBullet::TEX_TYPE_ENEMY_NORMAL);
				}
			}
		}
	}
}