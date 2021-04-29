//******************************************************************************
// ボス [boss.cpp]
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
#include "../Polygon/fade.h"
#include "../Particle/particle.h"
#include "../Particle/particle_explosion.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define TEXTURE						("data/Texture/Enemy/BossMain2.png")// テクスチャ
#define BOSS_MAIN_SIZE				(D3DXVECTOR3(150.0f,150.0f,0.0f))	// ボスの中央のサイズ
#define BOSS_LEFT_SIZE				(D3DXVECTOR3(150.0f,150.0f,0.0f))	// ボスの左のサイズ
#define BOSS_RIGHT_SIZE				(D3DXVECTOR3(150.0f,150.0f,0.0f))	// ボスの右のサイズ
#define BULLET_MOVE_VALUE			(D3DXVECTOR3(5.0f,5.0f,0.0f))		// 移動量
#define BULLET_TRAKING_MOVE_VALUE	(D3DXVECTOR3(6.0f,6.0f,0.0f))		// 狙い撃ち弾の移動量
#define BULLET_DIFFUSION_MOVE_VALUE	(D3DXVECTOR3(0.0f,2.0f,0.0f))		// 拡散弾の移動量
#define INIT_MOVE					(D3DXVECTOR3(0.0f,0.0f,0.0f))		// 移動初期化
#define BULLET_ROT					(D3DXVECTOR3(0.0f,0.0f,0.0f))		// 弾の向き
#define ENEMY_TRAKING_BULLET_SIZE	(D3DXVECTOR3(20.0f,20.0f,0.0f))		// レベル1の弾のサイズ
#define FIFFUSION_BULLET_SIZE		(D3DXVECTOR3(100.0f,100.0f,0.0f))	// 弾のサイズ
#define COLOR						(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	// 色
#define RED_COLOR					(D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))	// 赤色
#define BULLET_COLOR				(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	// 弾の色
#define BOSS_LIFE					(4000)								// ボスのライフ
#define DIVIDE_VALUE				(2)									// 除算値
#define INIT_ATTACK_COUNT			(0)									// 攻撃を0
#define REMAINDER_VALUE				(0)									// あまり0
#define ATTACK_COUNT				(60)								// 攻撃カウント
#define ATTACK_COUNT2				(100)								// 攻撃カウント2
#define ATTACK_COUNT3				(250)								// 攻撃カウント3
#define BULLET_TRAKING_TIMES		(3)									// 狙い撃ち弾の数
#define BULLET_TRAKING_TIMES2		(4)									// 狙い撃ち弾の数2
#define DAMAGE_COUNT_MIN			(0)									// ダメージカウント最小
#define DAMAGE_COUNT				(10)								// ダメージカウント
#define LIFE_MIN					(0)									// ライフ最小値
#define DEATH_COUNT					(90)								// 死亡カウント
#define EXPLOSION_COUNT				(4)									// 爆発カウント
#define RANDUM_POSX_VALUE			(600)								// 位置座標Xランダム数値
#define RANDUM_POSX_VALUE2			(300)								// 位置座標Xランダム数値2
#define RANDUM_POSY_VALUE			(200)								// 位置座標Yランダム数値
#define RANDUM_POSY_VALUE2			(100)								// 位置座標Yランダム数値2
#define RANDUM_SIZE_VALUE_MIN		(5)									// ランダムサイズ
#define RANDUM_SIZE_VALUE_MAX		(8)									// ランダムサイズ2
#define STATE_MOVE_VALUE			(2.0f)								// 移動量
#define STATE_MOVE_VALUE_MIN		(0.0f)								// 移動量
#define STATE_POS_VALUE				(200.0f)							// 位置量
#define MOVE_VALUE					(3.0f)								// 移動量
#define SIZE_DEVIDE_VALUE			(3)									// サイズを割る数
//******************************************************************************
// 静的メンバ変数
//******************************************************************************
LPDIRECT3DTEXTURE9 CBoss::m_pTexture = NULL;
//******************************************************************************
// コンストラクタ
//******************************************************************************
CBoss::CBoss(int nPriority) : CScene2d(nPriority)
{
	m_CollisionSize			= INIT_D3DXVECTOR3;
	m_move					= INIT_D3DXVECTOR3;
	m_nLife					= INIT_INT;
	m_nAttackCount			= INIT_INT;
	m_nDamageCount			= INIT_INT;
	m_nSetCount				= INIT_INT;
	m_nDeathCount			= INIT_INT;
	m_State					= STATE_NONE;
	m_bMove					= false;
	m_bLifeHalf				= false;
}
//******************************************************************************
//デストラクタ
//******************************************************************************
CBoss::~CBoss()
{
}
//******************************************************************************
// テクスチャ読み込み
//******************************************************************************
HRESULT CBoss::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE, &m_pTexture);
	return S_OK;
}
//******************************************************************************
// テクスチャ破棄
//******************************************************************************
void CBoss::Unload(void)
{
		// テクスチャの破棄
		if (m_pTexture != NULL)
		{
			m_pTexture->Release();
			m_pTexture = NULL;
		}
}
//******************************************************************************
// 生成関数
//******************************************************************************
CBoss * CBoss::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ボスポインタ
	CBoss * pBoss;

	// メモリ確保
	pBoss = new CBoss;

	// 位置座標設定
	pBoss->SetPosition(pos);

	// サイズ設定
	pBoss->SetSize(size);

	// 代入
	pBoss->m_CollisionSize = size;

	// カラー設定
	pBoss->SetRGBA(COLOR);

	// テクスチャ受け渡し
	pBoss->BindTexture(m_pTexture);

	// カラー設定
	pBoss->SetObjType(OBJTYPE_BOSS);

	// 初期化
	pBoss->Init();

	// ポインタを返す
	return pBoss;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CBoss::Init()
{

	// 当たり判定
	m_CollisionSize.y = m_CollisionSize.y / SIZE_DEVIDE_VALUE;

	// 体力
	m_nLife = BOSS_LIFE;

	// 状態
	m_State = STATE_MOVE;

	// 初期化
	CScene2d::Init();

	// 左生成
	CBoss_Left::Create(BOSS_LEFT_SIZE, BOSS_LEFT_SIZE);

	// 右生成
	CBoss_Right::Create(BOSS_RIGHT_SIZE, BOSS_RIGHT_SIZE);

	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CBoss::Uninit(void)
{
	//終了
	CScene2d::Uninit();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CBoss::Update(void)
{
	// 更新
	CScene2d::Update();

	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();

	// 状態処理
	State();

	// 位置更新
	pos.x += m_move.x;
	pos.y += m_move.y;

	// 座標設定
	SetPosition(pos);

}
//******************************************************************************
// 描画関数
//******************************************************************************
void CBoss::Draw(void)
{
	// 描画
	CScene2d::Draw();
}
//******************************************************************************
// ヒット処理
//******************************************************************************
void CBoss::HitBoss(int nDamage)
{
	// 移動状態でない場合
	if (m_State != STATE_MOVE)
	{
		// 体力減算
		m_nLife -= nDamage;

		// StateをDamageに
		m_State = STATE_DAMAGE;
	}
}
//******************************************************************************
// 攻撃処理関数
//******************************************************************************
void CBoss::Attack(void)
{
	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();

	// プレイヤー取得
	CPlayer * pPlayer = CGame::GetPlayer();

	// プレイヤーのbomをボス専用に変更
	pPlayer->SetBossBom(true);

	if (m_State == STATE_NORMAL|| m_State == STATE_DAMAGE)
	{
		// ライフが半分以上の場合
		if (m_bLifeHalf == false)
		{
			// インクリメント
			m_nAttackCount++;

			// 100あまり0の場合
			if (m_nAttackCount % ATTACK_COUNT2 == REMAINDER_VALUE)
			{
				// 3回繰り返す
				for (int nCount = INIT_INT; nCount < BULLET_TRAKING_TIMES; nCount++)
				{
					// 狙い撃ち弾生成
					CEnemy_Traking_Bullet::Create(pos,
						BULLET_ROT,
						ENEMY_TRAKING_BULLET_SIZE,
						D3DXVECTOR3(BULLET_TRAKING_MOVE_VALUE.x + nCount, BULLET_TRAKING_MOVE_VALUE.y + nCount, BULLET_TRAKING_MOVE_VALUE.z),
						BULLET_COLOR,
						CBullet::TEX_TYPE_ENEMY_NORMAL);
				}
			}
			// 拡散弾
			if (m_nAttackCount % ATTACK_COUNT3 == REMAINDER_VALUE)
			{
				// 拡散弾生成
				CEnemy_Diffusion_Bullet::Create(pos,
					BULLET_ROT,
					FIFFUSION_BULLET_SIZE,
					D3DXVECTOR3(BULLET_DIFFUSION_MOVE_VALUE.x, BULLET_DIFFUSION_MOVE_VALUE.y, BULLET_DIFFUSION_MOVE_VALUE.z),
					BULLET_COLOR,
					CBullet::TEX_TYPE_ENEMY_NORMAL);
			}
		}
		// ライフが半分以下になった場合
		if (m_nLife <= BOSS_LIFE / DIVIDE_VALUE)
		{
			// カウントを0に
			m_nAttackCount = INIT_ATTACK_COUNT;
			// trueに
			m_bLifeHalf = true;
		}
		// ライフが半分以下の場合
		if (m_bLifeHalf == true)
		{
			// インクリメント
			m_nAttackCount++;

			// 60あまり0の場合
			if (m_nAttackCount % ATTACK_COUNT == REMAINDER_VALUE)
			{
				for (int nCount = INIT_INT; nCount < BULLET_TRAKING_TIMES2; nCount++)
				{
					// 狙い撃ち弾生成
					CEnemy_Traking_Bullet::Create(pos,
						BULLET_ROT,
						ENEMY_TRAKING_BULLET_SIZE,
						D3DXVECTOR3(BULLET_TRAKING_MOVE_VALUE.x + nCount, BULLET_TRAKING_MOVE_VALUE.y + nCount, BULLET_TRAKING_MOVE_VALUE.z),
						BULLET_COLOR,
						CBullet::TEX_TYPE_ENEMY_NORMAL);
				}
			}
		}
	}
}
//******************************************************************************
// 状態処理関数
//******************************************************************************
void CBoss::State(void)
{
	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();

	// 最初の移動
	if (m_State == STATE_MOVE)
	{
		// 移動量を2.0fに
		m_move.y = STATE_MOVE_VALUE;

		// 位置座標が200.0fになった場合
		if (pos.y >= STATE_POS_VALUE)
		{
			// 移動量を0に
			m_move.y = STATE_MOVE_VALUE_MIN;

			// 通常状態に
			m_State = STATE_NORMAL;
		}
	}
	// ボスが移動しきったら
	if (m_State == STATE_NORMAL || m_State == STATE_DAMAGE)
	{
		// 移動処理
		Move();

		// 攻撃処理
		Attack();
	}
	// Stateがノーマルの場合
	if (m_State == STATE_NORMAL)
	{
		// カラーを通常にする
		SetRGBA(COLOR);
	}
	// StateがDamageの場合
	if (m_State == STATE_DAMAGE)
	{
		// ダメージカウントのインクリメント
		m_nDamageCount++;

		// 赤くする
		SetRGBA(RED_COLOR);

		// カウントが2あまり0の時
		if (m_nDamageCount % DIVIDE_VALUE == REMAINDER_VALUE)
		{
			// カラーを通常に戻す
			SetRGBA(COLOR);
		}
		// カウントが10になったら
		if (m_nDamageCount == DAMAGE_COUNT)
		{
			// Stateをノーマルに
			m_State = STATE_NORMAL;

			// カウントが0になったら
			m_nDamageCount = DAMAGE_COUNT_MIN;
		}
	}
	// 死亡演出状態の場合
	if (m_State == STATE_DEATH_EFFECT)
	{
		// 移動量を0に
		m_move = INIT_MOVE;

		// 弾全破棄
		CBullet::AllReleaseBullet();
	}
	// ライフが0になった場合
	if (m_nLife <= LIFE_MIN)
	{
		// 死亡エフェクト生成状態
		m_State = STATE_DEATH_EFFECT;

		// 死亡処理
		Death();
	}
	// 死亡状態の場合
	if (m_State == STATE_DEATH)
	{
		// フェード開始
		CFade::Create(FADE_POS, FADE_SIZE, CSceneManager::MODE_RESULT);

		// 終了
		Uninit();
		return;
	}
}
//******************************************************************************
// 移動処理関数
//******************************************************************************
void CBoss::Move(void)
{
	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();
	
	if (m_State != STATE_MOVE ||  m_State != STATE_DEATH_EFFECT || m_State != STATE_DEATH )
	{
		// falseの場合
		if (m_bMove == false)
		{
			m_move.x = MOVE_VALUE;
		}
		// 左移動
		if (pos.x + BOSS_RIGHT_SIZE.x + BOSS_RIGHT_SIZE.x / DIVIDE_VALUE >= MAX_GAME_WIDTH)
		{
			m_move.x = -MOVE_VALUE;
			m_bMove = true;
		}
		// 右移動
		if (pos.x - BOSS_LEFT_SIZE.x - BOSS_LEFT_SIZE.x / DIVIDE_VALUE <= MIN_GAME_WIDTH)
		{
			m_move.x = MOVE_VALUE;
			m_bMove = true;
		}
		// 座標設定
		SetPosition(pos);
	}
}
//******************************************************************************
// 死亡処理
//******************************************************************************
void CBoss::Death(void)
{
	// 位置座標
	D3DXVECTOR3 pos = GetPosition();

	// サイズランダムに
	float fSize = float(rand() % RANDUM_SIZE_VALUE_MIN + RANDUM_SIZE_VALUE_MAX);
	// 位置をランダムに
	float fPosX = float(rand() % RANDUM_POSX_VALUE - RANDUM_POSX_VALUE2);
	float fPosY = float(rand() % RANDUM_POSY_VALUE - RANDUM_POSY_VALUE2);

	// サイズ
	D3DXVECTOR3 size = D3DXVECTOR3(fSize, fSize, 0.0f);

	// 位置
	D3DXVECTOR3 Explosion_Pos = D3DXVECTOR3(pos.x + fPosX, pos.y + fPosY, 0.0f);

	// インクリメント
	m_nDeathCount++;

	// 3あまり0
	if (m_nDeathCount % EXPLOSION_COUNT == REMAINDER_VALUE)
	{
		// 爆発生成
		CParticle_Explosion::CreateExplosionEffect(Explosion_Pos,size,CParticle_Explosion::TYPE_ENEMY);
	}
	// m_nDeathCountが60になった場合
	if (m_nDeathCount == DEATH_COUNT)
	{
		m_State = STATE_DEATH;
	}
}