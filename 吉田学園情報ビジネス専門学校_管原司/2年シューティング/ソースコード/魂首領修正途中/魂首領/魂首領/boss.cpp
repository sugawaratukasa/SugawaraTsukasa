//******************************************************************************
// ボス [boss.cpp]
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
#include "bullet.h"
#include "enemy_traking_bullet.h"
#include "enemy_normal_bullet.h"
#include "enemy_diffusion_bullet.h"
#include "explosion.h"
#include "player.h"
#include "game.h"
#include "boss.h"
//******************************************************************************
// 静的メンバ変数
//******************************************************************************
LPDIRECT3DTEXTURE9 CBoss::m_apTexture[MAX_BOSS] = {};
//******************************************************************************
// コンストラクタ
//******************************************************************************
CBoss::CBoss(int nPriority) : CScene(nPriority)
{
	memset(m_apScene2D, 0, sizeof(m_apScene2D));
	m_pos					= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rightpos				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Leftpos				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size					= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move					= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife					= 0;
	m_nAttackCount			= 0;
	m_nAttackCount2			= 0;
	m_nDamageCount			= 0;
	m_nSetCount				= 0;
	m_State					= STATE_NONE;
	m_bMove					= false;
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
	D3DXCreateTextureFromFile(pDevice, "data/Texture/BossMain2.png", &m_apTexture[TYPE_MAIN]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/BossRight2.png", &m_apTexture[TYPE_RIGHT]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/BossLeft2.png", &m_apTexture[TYPE_LEFT]);
	return S_OK;
}
//******************************************************************************
// テクスチャ破棄
//******************************************************************************
void CBoss::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_BOSS; nCnt++)
	{
		// テクスチャの破棄
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
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

	// 位置座標代入
	pBoss->m_pos = pos;

	// サイズ代入
	pBoss->m_size = size;

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
	// 体力
	m_nLife = BOSS_LIFE;
	// 状態
	m_State = STATE_MOVE;

	// メモリ確保
	m_apScene2D[TYPE_MAIN] = new CScene2d;
	m_apScene2D[TYPE_RIGHT] = new CScene2d;
	m_apScene2D[TYPE_LEFT] = new CScene2d;

	// 位置座標の設定
	m_apScene2D[TYPE_MAIN]->SetPosition(m_pos);
	m_apScene2D[TYPE_RIGHT]->SetPosition(m_pos);
	m_apScene2D[TYPE_LEFT]->SetPosition(m_pos);

	// サイズの設定
	m_apScene2D[TYPE_MAIN]->SetSize(m_size);
	m_apScene2D[TYPE_RIGHT]->SetSize(m_size);
	m_apScene2D[TYPE_LEFT]->SetSize(m_size);

	// RGBAの設定
	m_apScene2D[TYPE_MAIN]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apScene2D[TYPE_RIGHT]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apScene2D[TYPE_LEFT]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// テクスチャの受け渡し
	m_apScene2D[TYPE_MAIN]->BindTexture(m_apTexture[TYPE_MAIN]);
	m_apScene2D[TYPE_RIGHT]->BindTexture(m_apTexture[TYPE_RIGHT]);
	m_apScene2D[TYPE_LEFT]->BindTexture(m_apTexture[TYPE_LEFT]);
	
	// オブジェクトタイプの設定
	m_apScene2D[TYPE_MAIN]->SetObjType(OBJTYPE_BOSS);
	m_apScene2D[TYPE_RIGHT]->SetObjType(OBJTYPE_BOSS);
	m_apScene2D[TYPE_LEFT]->SetObjType(OBJTYPE_BOSS);

	// 初期化
	m_apScene2D[TYPE_MAIN]->Init();
	m_apScene2D[TYPE_RIGHT]->Init();
	m_apScene2D[TYPE_LEFT]->Init();
	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CBoss::Uninit(void)
{
	//終了
	Release();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CBoss::Update(void)
{
	if (m_nSetCount == 1)
	{
		// 更新
		m_apScene2D[TYPE_MAIN]->Update();
		m_apScene2D[TYPE_RIGHT]->Update();
		m_apScene2D[TYPE_LEFT]->Update();

		// ボスの中心
		m_pos = m_apScene2D[TYPE_MAIN]->GetPosition();
		// ボスの右
		m_Rightpos = m_apScene2D[TYPE_RIGHT]->GetPosition();
		// ボスの左
		m_Leftpos = m_apScene2D[TYPE_LEFT]->GetPosition();

		// 状態処理
		State();

		// 位置更新
		m_pos.x += m_move.x;
		m_pos.y += m_move.y;

		// 座標設定
		m_apScene2D[TYPE_MAIN]->SetPosition(m_pos);
		m_apScene2D[TYPE_RIGHT]->SetPosition(D3DXVECTOR3(m_pos.x + BOSS_RIGHT_SIZE.x, m_pos.y, m_pos.z));
		m_apScene2D[TYPE_LEFT]->SetPosition(D3DXVECTOR3(m_pos.x - BOSS_LEFT_SIZE.x, m_pos.y, m_pos.z));

	}
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CBoss::Draw(void)
{
}
//******************************************************************************
// ヒット処理
//******************************************************************************
void CBoss::HitBoss(int nDamage)
{
	if (m_State != STATE_MOVE)
	{
		// 体力減算
		m_nLife -= nDamage;
		// StateをDamageに
		m_State = STATE_DAMAGE;
	}
}
//******************************************************************************
// ボス更新開始
//******************************************************************************
void CBoss::SetBoss(int nSetCount)
{
	m_nSetCount = nSetCount;
}
//******************************************************************************
// 攻撃処理関数
//******************************************************************************
void CBoss::Attack(void)
{

	// プレイヤー取得
	CPlayer * pPlayer = CGame::GetPlayer();

	// プレイヤーのbomをボス専用に変更
	pPlayer->SetBossBom(true);

	// ライフが半分以上の場合
	if (m_nLife >= BOSS_LIFE / 2)
	{
		// インクリメント
		m_nAttackCount++;

		// 60あまり0の場合
		if (m_nAttackCount % 60 == 0)
		{
			// 左右2発弾発射
			for (int nCount = 0; nCount < 2; nCount++)
			{
				// 右
				CEnemy_Normal_Bullet::Create(D3DXVECTOR3(m_Rightpos.x + BOSS_RIGHT_SIZE.x / 2, m_Rightpos.y + BOSS_RIGHT_SIZE.y / 2, m_Rightpos.z),
					D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)),
					ENEMY_NORMAL_BULLET_SIZE,
					D3DXVECTOR3(-2.0f - nCount, 6.0f, 0.0f),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					CBullet::TEX_TYPE_ENEMY_NORMAL);

				// 左
				CEnemy_Normal_Bullet::Create(D3DXVECTOR3(m_Leftpos.x + BOSS_LEFT_SIZE.x / 2, m_Leftpos.y + BOSS_LEFT_SIZE.y / 2, m_Leftpos.z),
					D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)),
					ENEMY_NORMAL_BULLET_SIZE,
					D3DXVECTOR3(2.0f + nCount, 6.0f, 0.0f),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					CBullet::TEX_TYPE_ENEMY_NORMAL);
			}
		}
		//100あまり0の場合
		if (m_nAttackCount % 100 == 0)
		{
			// 3回繰り返す
			for (int nCount = 0; nCount < 3; nCount++)
			{
				// 狙い撃ち弾生成
				CEnemy_Traking_Bullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z),
					D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)),
					ENEMY_TRAKING_BULLET_SIZE,
					D3DXVECTOR3(6.0f + nCount, 6.0f + nCount, 0.0f),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					CBullet::TEX_TYPE_ENEMY_NORMAL);
			}
		}
		//拡散弾
		if (m_nAttackCount % 250 == 0)
		{
			// 拡散弾生成
			CEnemy_Diffusion_Bullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z),
				D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)),
				FIFFUSION_BULLET_SIZE,
				D3DXVECTOR3(0.0f, 2.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				CBullet::TEX_TYPE_ENEMY_NORMAL);
		}
	}
		// ライフが半分以下の場合
	if (m_nLife <= BOSS_LIFE / 2)
	{
		m_nAttackCount2++;
		//100あまり0の場合
		if (m_nAttackCount2 % 60 == 0)
		{
			for (int nCount = 0; nCount < 4; nCount++)
			{
				// 狙い撃ち弾生成
				CEnemy_Traking_Bullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z),
					D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)),
					ENEMY_TRAKING_BULLET_SIZE,
					D3DXVECTOR3(6.0f + nCount, 6.0f + nCount, 0.0f),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					CBullet::TEX_TYPE_ENEMY_NORMAL);
			}
		}

		// カウントが100以上の場合
		if (m_nAttackCount2 >= 100)
		{
			// 3あまり0の時
			if (m_nAttackCount2 % 3 == 0)
			{
				// 回転弾生成
				CEnemy_Normal_Bullet::Create(D3DXVECTOR3(m_Rightpos.x + BOSS_LEFT_SIZE.x / 2, m_Rightpos.y + BOSS_LEFT_SIZE.y / 2, m_Rightpos.z),
					D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)),
					ENEMY_NORMAL_BULLET_SIZE,
					D3DXVECTOR3(cosf(D3DXToRadian(m_nAttackCount2 / 3 * (360 / 20)))*3.0f, sinf(D3DXToRadian(m_nAttackCount2 / 3 * (360 / 20)))*3.0f, 0.0f),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					CBullet::TEX_TYPE_ENEMY_NORMAL);

				// 回転弾生成
				CEnemy_Normal_Bullet::Create(D3DXVECTOR3(m_Leftpos.x + BOSS_LEFT_SIZE.x / 2, m_Leftpos.y + BOSS_LEFT_SIZE.y / 2, m_Leftpos.z),
					D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)),
					ENEMY_NORMAL_BULLET_SIZE,
					D3DXVECTOR3(cosf(D3DXToRadian(m_nAttackCount2 / 3 * (360 / 20)))* -3.0f, sinf(D3DXToRadian(m_nAttackCount2 / 3 * (360 / 20)))* -3.0f, 0.0f),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					CBullet::TEX_TYPE_ENEMY_NORMAL);

			}
		}
	}
}
//******************************************************************************
// 状態処理関数
//******************************************************************************
void CBoss::State(void)
{
	//最初の移動
	if (m_State == STATE_MOVE)
	{
		m_move.y = 2.0f;
		if (m_pos.y == 200.0f)
		{
			m_move.y = 0;
			m_State = STATE_NORMAL;
		}
	}
	//ボスが移動しきったら
	if (m_State != STATE_MOVE)
	{
		// 移動処理
		Move();

		// 攻撃処理
		Attack();
	}
	// Stateがノーマルの場合
	if (m_State == STATE_NORMAL)
	{
		//カラーを通常にする
		m_apScene2D[TYPE_MAIN]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_apScene2D[TYPE_RIGHT]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_apScene2D[TYPE_LEFT]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	//StateがDamageの場合
	if (m_State == STATE_DAMAGE)
	{
		//ダメージカウントのインクリメント
		m_nDamageCount++;

		// 赤くする
		m_apScene2D[TYPE_MAIN]->SetRGBA(D3DCOLOR_RGBA(255, 0, 0, 255));
		m_apScene2D[TYPE_RIGHT]->SetRGBA(D3DCOLOR_RGBA(255, 0, 0, 255));
		m_apScene2D[TYPE_LEFT]->SetRGBA(D3DCOLOR_RGBA(255, 0, 0, 255));

		//カウントが2あまり0の時
		if (m_nDamageCount % 2 == 0)
		{
			//カラーを通常に戻す
			m_apScene2D[TYPE_MAIN]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_apScene2D[TYPE_RIGHT]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_apScene2D[TYPE_LEFT]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}

		// カウントが10になったら
		if (m_nDamageCount == 10)
		{
			// Stateをノーマルに
			m_State = STATE_NORMAL;
			// カウントが0になったら
			m_nDamageCount = 0;
		}
	}
	// ライフが0になった場合
	if (m_nLife <= 0)
	{
		// 爆発生成
		CExplosion::Create(m_pos, BOSS_MAIN_SIZE);
		CExplosion::Create(m_Rightpos, BOSS_LEFT_SIZE);
		CExplosion::Create(m_Leftpos, BOSS_RIGHT_SIZE);

		// 死亡状態に
		m_State = STATE_DEAD;

		// 死亡状態の場合
		if (m_State == STATE_DEAD)
		{
			// フェード開始
			CSceneManager::StartFade(CSceneManager::MODE_RESULT);
			// 終了
			Uninit();
			return;
		}
	}
}
//******************************************************************************
// 移動処理関数
//******************************************************************************
void CBoss::Move(void)
{
	// falseの場合
	if (m_bMove == false)
	{
		m_move.x = 3.0f;
	}
	//左移動
	if (m_Rightpos.x + BOSS_RIGHT_SIZE.x / 2 >= MAX_GAME_WIDTH)
	{
		m_move.x = -3.0f;
		m_bMove = true;
	}
	// 右移動
	if (m_Leftpos.x - BOSS_LEFT_SIZE.x / 2 <= MIN_GAME_WIDTH)
	{
		m_move.x = 3.0f;
		m_bMove = true;
	}
}