//******************************************************************************
// 敵 [enemy.cpp]
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
#include "enemy.h"
#include "../Polygon/item.h"
#include "../Particle/particle.h"
#include "../Particle/particle_explosion.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define NORMAL_ENEMY_TEXTURE	("data/Texture/Enemy/enemy1.png")	// 通常の敵
#define ENEMY_BLUE_TEXTURE		("data/Texture/Enemy/enemy2.png")	// 青色の敵
#define ENEMY_RED_TEXTURE		("data/Texture/Enemy/enemy3.png")	// 赤色の敵
#define BATTERY_TEXTURE			("data/Texture/Enemy/Wepon1.png")	// 固定砲台
#define EXPLOSION_SIZE			(size / 10)							// 爆発サイズ
#define COLOR					(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	// 色
#define DAMAGE_COLOR			(D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))	// ダメージ状態の色
#define DAMAGE_COUNT			(10)								// ダメージ状態のカウント
#define INIT_DAMAGE_COUNT		(0)									// ダメージカウントを0
#define DAMAGE_COUNT_DEVIDE		(2)									// 割る数
#define DAMAGE_COUNT_REMAINDER	(0)									// 余り
#define LIFE_MIN				(0)									// ライフ最小値
//******************************************************************************
// 静的メンバ変数
//******************************************************************************
LPDIRECT3DTEXTURE9 CEnemy::m_apTexture[TEX_TYPE_MAX] = {};
//******************************************************************************
// コンストラクタ
//******************************************************************************
CEnemy::CEnemy(int nPriority) : CScene2d(nPriority)
{
	m_TexType		= TEX_TYPE_NONE;
	m_state			= STATE_NONE;
	m_nLife			= INIT_INT;
	m_nDamageCount	= INIT_INT;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CEnemy::~CEnemy()
{
}
//******************************************************************************
// テクスチャ読み込み
//******************************************************************************
HRESULT CEnemy::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, NORMAL_ENEMY_TEXTURE, &m_apTexture[TEX_TYPE_NORMAL]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_BLUE_TEXTURE, &m_apTexture[TEX_TYPE_BLUE]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_RED_TEXTURE, &m_apTexture[TEX_TYPE_RED]);
	D3DXCreateTextureFromFile(pDevice, BATTERY_TEXTURE, &m_apTexture[TEX_TYPE_SHIP_BATTERY]);
	return S_OK;
}
//******************************************************************************
// テクスチャ破棄
//******************************************************************************
void CEnemy::Unload(void)
{
	for (int nCnt = INIT_INT; nCnt < TEX_TYPE_MAX; nCnt++)
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
// 初期化関数
//******************************************************************************
HRESULT CEnemy::Init(void)
{
	// 通常状態に
	m_state = STATE_NORMAL;

	//初期化
	CScene2d::Init();

	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CEnemy::Uninit(void)
{
	//終了
	CScene2d::Uninit();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CEnemy::Update(void)
{
	// 更新
	CScene2d::Update();

	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();

	// サイズ座標取得
	D3DXVECTOR3 size = GetSize();
	// Stateがノーマルの場合
	if (m_state == STATE_NORMAL)
	{
		// カラー設定
		SetRGBA(COLOR);
	}
	// ダメージ状態の場合
	if (m_state == STATE_DAMAGE)
	{
		// インクリメント
		m_nDamageCount++;

		// カラー設定赤にする
		SetRGBA(DAMAGE_COLOR);

		// 2あまり0の時
		if (m_nDamageCount % DAMAGE_COUNT_DEVIDE == DAMAGE_COUNT_REMAINDER)
		{
			// カラー設定
			SetRGBA(COLOR);
		}

		// カウントが10の場合
		if (m_nDamageCount == DAMAGE_COUNT)
		{
			// 状態をNORMALにする
			m_state = STATE_NORMAL;

			// 0に
			m_nDamageCount = INIT_DAMAGE_COUNT;
		}
	}
	// ライフが0以下になった場合
	if (m_nLife <= LIFE_MIN)
	{
		// 爆発の生成
		CParticle_Explosion::CreateExplosionEffect(pos, EXPLOSION_SIZE,CParticle_Explosion::TYPE_ENEMY);

		// 死亡状態に設定
		m_state = STATE_DEATH;

		// 終了
		Uninit();
		return;
	}
	// 画面外
	if (pos.y - size.y > SCREEN_HEIGHT)
	{
		// 終了
		Uninit();
		return;
	}
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CEnemy::Draw(void)
{
	//描画
	CScene2d::Draw();
}
//******************************************************************************
// ヒット処理関数
//******************************************************************************
void CEnemy::HitEnemy(int nDamage)
{
	// ダメージ減算
	m_nLife -= nDamage;

	// stateをダメージに
	m_state = STATE_DAMAGE;
}
//******************************************************************************
// 敵情報の設定
//******************************************************************************
void CEnemy::SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nLife, TEX_TYPE tex_type, CScene::OBJTYPE objtype)
{
	// 位置座標設定
	SetPosition(pos);

	// 向き設定
	SetRot(rot);

	// サイズ設定
	SetSize(size);

	// カラー設定
	SetRGBA(COLOR);

	// ライフ設定
	m_nLife = nLife;

	// テクスチャタイプ代入
	m_TexType = tex_type;

	// テクスチャ設定
	BindTexture(m_apTexture[m_TexType]);

	// オブジェタイプ設定
	SetObjType(objtype);
}
