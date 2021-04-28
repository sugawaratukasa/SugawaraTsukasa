//******************************************************************************
// プレイヤーのビームの処理 [player_beam.cpp]
// Author : 管原　司
//******************************************************************************

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "../System/main.h"
#include "../System/renderer.h"
#include "../System/scene.h"
#include "../System/scene2d.h"
#include "../Enemy/enemy.h"
#include "beam.h"
#include "../Particle/particle.h"
#include "../Particle/particle_beam.h"
#include "../Boss/boss.h"
#include "../Boss/boss_left.h"
#include "../Boss/boss_right.h"
#include "player_beam.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define EFFECT_POS			(D3DXVECTOR3(EnemyPos.x, EnemyPos.y + EnemySize.y / 2, EnemyPos.z))	// エフェクトの位置
#define EFFECT_POS2			(D3DXVECTOR3(pos.x, BossPos.y + BossSize.y / 2, pos.z))				// エフェクトの位置
#define EFFECT_POS3			(D3DXVECTOR3(pos.x, Boss_RightPos.y + Boss_RightSize.y / 2, pos.z))	// エフェクトの位置
#define EFFECT_POS4			(D3DXVECTOR3(pos.x, Boss_LeftPos.y + Boss_LeftSize.y / 2, pos.z))	// エフェクトの位置
#define EFFECT_ROT			(D3DXVECTOR3(0.0f,0.0f,fAngle))										// エフェクトの向き
#define EFFECT_SIZE			(size * 1.5f)														// エフェクトサイズ
#define BEAM_COLOR			(D3DXCOLOR(0.0f,0.5f,1.0f,1.0f))									// ビームの色
#define BEAM_COLOR2			(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))									// ビームの色
#define EFFECT_COLOR		(D3DXCOLOR(0.0f,0.1f,1.0f,1.0f))									// ビームの色
#define EFFECT_COLOR2		(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))									// ビームの色
#define BEAM_NUM_0			(0)																	// 配列の1番目
#define BEAM_NUM_1			(1)																	// 配列の2番目
#define DAMAGE				(3)																	// ダメージ
#define DEVIDE_VALUE		(2)																	// 割る数
#define RANDUM_ANGLE		(360 - 180)															// 弧度ランダム
//******************************************************************************
// 静的メンバ変数
//******************************************************************************
//******************************************************************************
// コンストラクタ
//******************************************************************************
CPlayer_Beam::CPlayer_Beam(int nPriority) : CScene(nPriority)
{
	memset(m_apBeam, NULL, sizeof(m_apBeam));
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CPlayer_Beam::~CPlayer_Beam()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CPlayer_Beam * CPlayer_Beam::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CBeamクラスのポインタ
	CPlayer_Beam *pPlayer_Beam;

	// メモリ確保
	pPlayer_Beam = new CPlayer_Beam;

	// 初期化
	pPlayer_Beam->Init();

	// ビーム生成
	pPlayer_Beam->BeamCreate(pos,size);

	// ポインタを返す
	return pPlayer_Beam;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CPlayer_Beam::Init(void)
{
	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CPlayer_Beam::Uninit(void)
{
	// 破棄
	Release();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CPlayer_Beam::Update(void)
{
	// 当たり判定
	Collision();
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CPlayer_Beam::Draw(void)
{
}
//******************************************************************************
// ビーム生成
//******************************************************************************
void CPlayer_Beam::BeamCreate(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ビーム生成
	m_apBeam[BEAM_NUM_0] = CBeam::Create(pos,
		size,
		BEAM_COLOR2,
		CBeam::TEX_TYPE_01);

	m_apBeam[BEAM_NUM_1] = CBeam::Create(pos,
		size,
		BEAM_COLOR,
		CBeam::TEX_TYPE_02);
}
//******************************************************************************
// ビーム破棄
//******************************************************************************
void CPlayer_Beam::ReleaseAllBeam(void)
{
	// 最大数分回す
	for (int nCnt = INIT_INT; nCnt < BEAM_MAX_NUM; nCnt++)
	{
		// 破棄
		m_apBeam[nCnt]->Release();
	}

	// 終了
	Uninit();
	return;
}
//******************************************************************************
// 当たり判定
//******************************************************************************
void CPlayer_Beam::Collision(void)
{
	// 位置取得
	D3DXVECTOR3 pos = m_apBeam[BEAM_NUM_0]->GetPosition();

	// サイズ取得
	D3DXVECTOR3 size = m_apBeam[BEAM_NUM_0]->GetSize();

	// サイズ取得
	float fSize = m_apBeam[BEAM_NUM_0]->GetSizeY();

	// CScene型のポインタ
	CScene *pScene = NULL;

	//**************************************************************************
	// 敵の当たり判定
	//**************************************************************************
	do
	{
		// オブジェタイプが敵の場合
		pScene = GetScene(OBJTYPE_ENEMY);

		// NULLでない場合
		if (pScene != NULL)
		{
			// オブジェクトタイプ取得
			OBJTYPE objType = pScene->GetObjType();

			// OBJTYPE_ENEMYの場合
			if (objType == OBJTYPE_ENEMY)
			{
				// 敵の位置
				D3DXVECTOR3 EnemyPos = ((CEnemy*)pScene)->GetPosition();

				// 敵のサイズ
				D3DXVECTOR3 EnemySize = ((CEnemy*)pScene)->GetSize();

				D3DXVECTOR3 box1Max = D3DXVECTOR3(size.x / DEVIDE_VALUE, size.y / DEVIDE_VALUE, size.z / DEVIDE_VALUE) + pos;
				D3DXVECTOR3 box1Min = D3DXVECTOR3(-size.x / DEVIDE_VALUE, -fSize / DEVIDE_VALUE, -size.z / DEVIDE_VALUE) + pos;
				D3DXVECTOR3 box2Max = D3DXVECTOR3(EnemySize.x / DEVIDE_VALUE, EnemySize.y / DEVIDE_VALUE, EnemySize.z / DEVIDE_VALUE) + EnemyPos;
				D3DXVECTOR3 box2Min = D3DXVECTOR3(-EnemySize.x / DEVIDE_VALUE, -EnemySize.y / DEVIDE_VALUE, -EnemySize.z / DEVIDE_VALUE) + EnemyPos;

				if (box1Max.y > box2Min.y&&
					box1Min.y < box2Max.y&&
					box1Max.x > box2Min.x&&
					box1Min.x < box2Max.x)
				{
					// サイズ代入
					fSize = (pos.y + fSize / DEVIDE_VALUE) - (EnemyPos.y + EnemySize.y / DEVIDE_VALUE);

					// ビームの数繰り返す
					for (int nCnt = INIT_INT; nCnt < BEAM_MAX_NUM; nCnt++)
					{
						// サイズ設定
						m_apBeam[nCnt]->SetSizeY(fSize);
					}

					// 向き
					float fAngle = float(rand() % RANDUM_ANGLE);

					// エフェクト生成
					CParticle_Beam::Create(EFFECT_POS, EFFECT_SIZE, EFFECT_ROT, EFFECT_COLOR, CParticle::TEX_TYPE_FLASH);

					// 敵にダメージを与える
					((CEnemy*)pScene)->HitEnemy(DAMAGE);
				}
			} 
		}
	} while (pScene != NULL);

	//**************************************************************************
	// ボスの当たり判定
	//**************************************************************************
	do
	{
		// オブジェタイプが敵の場合
		pScene = GetScene(OBJTYPE_BOSS);

		// NULLでない場合
		if (pScene != NULL)
		{
			// オブジェクトタイプ取得
			OBJTYPE objType = pScene->GetObjType();

			// OBJTYPE_ENEMYの場合
			if (objType == OBJTYPE_BOSS)
			{
				// 敵の位置
				D3DXVECTOR3 BossPos = ((CBoss*)pScene)->GetPosition();

				// 敵のサイズ
				D3DXVECTOR3 BossSize = ((CBoss*)pScene)->GetCollisionSize();

				D3DXVECTOR3 box1Max = D3DXVECTOR3(size.x / DEVIDE_VALUE, size.y / DEVIDE_VALUE, size.z / DEVIDE_VALUE) + pos;
				D3DXVECTOR3 box1Min = D3DXVECTOR3(-size.x / DEVIDE_VALUE, -fSize / DEVIDE_VALUE, -size.z / DEVIDE_VALUE) + pos;
				D3DXVECTOR3 box2Max = D3DXVECTOR3(BossSize.x / DEVIDE_VALUE, BossSize.y / DEVIDE_VALUE, BossSize.z / DEVIDE_VALUE) + BossPos;
				D3DXVECTOR3 box2Min = D3DXVECTOR3(-BossSize.x / DEVIDE_VALUE, -BossSize.y / DEVIDE_VALUE, -BossSize.z / DEVIDE_VALUE) + BossPos;

				if (box1Max.y > box2Min.y&&
					box1Min.y < box2Max.y&&
					box1Max.x > box2Min.x&&
					box1Min.x < box2Max.x)
				{
					// サイズ代入
					fSize = (pos.y + fSize / DEVIDE_VALUE) - (BossPos.y + BossSize.y / DEVIDE_VALUE);

					// ビームの数繰り返す
					for (int nCnt = INIT_INT; nCnt < BEAM_MAX_NUM; nCnt++)
					{
						// サイズ設定
						m_apBeam[nCnt]->SetSizeY(fSize);
					}

					// 向き
					float fAngle = float(rand() % RANDUM_ANGLE);

					// エフェクト生成
					CParticle_Beam::Create(EFFECT_POS2, EFFECT_SIZE, EFFECT_ROT, EFFECT_COLOR, CParticle::TEX_TYPE_FLASH);

					// 敵にダメージを与える
					((CBoss*)pScene)->HitBoss(DAMAGE);
				}
			}
		}
	} while (pScene != NULL);

	//**************************************************************************
	// ボス右の当たり判定
	//**************************************************************************
	do
	{
		// オブジェタイプが敵の場合
		pScene = GetScene(OBJTYPE_BOSS_RIGHT);

		// NULLでない場合
		if (pScene != NULL)
		{
			// オブジェクトタイプ取得
			OBJTYPE objType = pScene->GetObjType();

			// OBJTYPE_ENEMYの場合
			if (objType == OBJTYPE_BOSS_RIGHT)
			{
				// 敵の位置
				D3DXVECTOR3 Boss_RightPos = ((CBoss_Right*)pScene)->GetPosition();

				// 敵のサイズ
				D3DXVECTOR3 Boss_RightSize = ((CBoss_Right*)pScene)->GetSize();

				D3DXVECTOR3 box1Max = D3DXVECTOR3(size.x / DEVIDE_VALUE, size.y / DEVIDE_VALUE, size.z / DEVIDE_VALUE) + pos;
				D3DXVECTOR3 box1Min = D3DXVECTOR3(-size.x / DEVIDE_VALUE, -fSize / DEVIDE_VALUE, -size.z / DEVIDE_VALUE) + pos;
				D3DXVECTOR3 box2Max = D3DXVECTOR3(Boss_RightSize.x / DEVIDE_VALUE, Boss_RightSize.y / DEVIDE_VALUE, Boss_RightSize.z / DEVIDE_VALUE) + Boss_RightPos;
				D3DXVECTOR3 box2Min = D3DXVECTOR3(-Boss_RightSize.x / DEVIDE_VALUE, -Boss_RightSize.y / DEVIDE_VALUE, -Boss_RightSize.z / DEVIDE_VALUE) + Boss_RightPos;

				if (box1Max.y > box2Min.y&&
					box1Min.y < box2Max.y&&
					box1Max.x > box2Min.x&&
					box1Min.x < box2Max.x)
				{
					// サイズ代入
					fSize = (pos.y + fSize / DEVIDE_VALUE) - (Boss_RightPos.y + Boss_RightSize.y / DEVIDE_VALUE);

					// ビームの数繰り返す
					for (int nCnt = INIT_INT; nCnt < BEAM_MAX_NUM; nCnt++)
					{
						// サイズ設定
						m_apBeam[nCnt]->SetSizeY(fSize);
					}

					// 向き
					float fAngle = float(rand() % RANDUM_ANGLE);

					// エフェクト生成
					CParticle_Beam::Create(EFFECT_POS3, EFFECT_SIZE, EFFECT_ROT, EFFECT_COLOR, CParticle::TEX_TYPE_FLASH);

					// 敵にダメージを与える
					((CBoss_Right*)pScene)->Hit(DAMAGE);
				}
			}
		}
	} while (pScene != NULL);

	//**************************************************************************
	// ボス左の当たり判定
	//**************************************************************************
	do
	{
		// オブジェタイプが敵の場合
		pScene = GetScene(OBJTYPE_BOSS_LEFT);

		// NULLでない場合
		if (pScene != NULL)
		{
			// オブジェクトタイプ取得
			OBJTYPE objType = pScene->GetObjType();

			// OBJTYPE_ENEMYの場合
			if (objType == OBJTYPE_BOSS_LEFT)
			{
				// 敵の位置
				D3DXVECTOR3 Boss_LeftPos = ((CBoss_Left*)pScene)->GetPosition();

				// 敵のサイズ
				D3DXVECTOR3 Boss_LeftSize = ((CBoss_Left*)pScene)->GetSize();

				D3DXVECTOR3 box1Max = D3DXVECTOR3(size.x / DEVIDE_VALUE, size.y / DEVIDE_VALUE, size.z / DEVIDE_VALUE) + pos;
				D3DXVECTOR3 box1Min = D3DXVECTOR3(-size.x / DEVIDE_VALUE, -fSize / DEVIDE_VALUE, -size.z / DEVIDE_VALUE) + pos;
				D3DXVECTOR3 box2Max = D3DXVECTOR3(Boss_LeftSize.x / DEVIDE_VALUE, Boss_LeftSize.y / DEVIDE_VALUE, Boss_LeftSize.z / DEVIDE_VALUE) + Boss_LeftPos;
				D3DXVECTOR3 box2Min = D3DXVECTOR3(-Boss_LeftSize.x / DEVIDE_VALUE, -Boss_LeftSize.y / DEVIDE_VALUE, -Boss_LeftSize.z / DEVIDE_VALUE) + Boss_LeftPos;

				if (box1Max.y > box2Min.y&&
					box1Min.y < box2Max.y&&
					box1Max.x > box2Min.x&&
					box1Min.x < box2Max.x)
				{
					// サイズ代入
					fSize = (pos.y + fSize / DEVIDE_VALUE) - (Boss_LeftPos.y + Boss_LeftSize.y / DEVIDE_VALUE);

					// ビームの数繰り返す
					for (int nCnt = INIT_INT; nCnt < BEAM_MAX_NUM; nCnt++)
					{
						// サイズ設定
						m_apBeam[nCnt]->SetSizeY(fSize);
					}

					// 向き
					float fAngle = float(rand() % RANDUM_ANGLE);

					// エフェクト生成
					CParticle_Beam::Create(EFFECT_POS4, EFFECT_SIZE, EFFECT_ROT, EFFECT_COLOR, CParticle::TEX_TYPE_FLASH);

					// 敵にダメージを与える
					((CBoss_Left*)pScene)->Hit(DAMAGE);
				}
			}
		}
	} while (pScene != NULL);
}