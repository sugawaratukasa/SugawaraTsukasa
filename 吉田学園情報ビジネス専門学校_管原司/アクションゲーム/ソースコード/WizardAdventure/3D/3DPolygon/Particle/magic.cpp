//******************************************************************************
// 魔法 [magic.cpp]
// Author : 管原　司
//******************************************************************************

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "particle.h"
#include "manager.h"
#include "../3D/Model/Enemy/enemy.h"
#include "../3D/Model/Enemy/ghost.h"
#include "../3D/Model/player.h"
#include "../3D/Model/Object/3d_obj.h"
#include "../3D/Model/Block/block.h"
#include "collision.h"
#include "Particle_Effect/particle_effect.h"
#include "../3D/Model/Object/wood.h"
#include "sound.h"
#include "magic.h"

//******************************************************************************
// マクロ定義
//******************************************************************************
#define MAX_TEXT			 (1024)										// テキストの最大数
#define FIRE_BALL_TEXT		 ("data/Effect/FireBall_Data.txt")			// テキスト
#define ICE_BALL_TEXT		 ("data/Effect/IceBall_Data.txt")			// テキスト
#define ENEMY_FIRE_BALL_TEXT ("data/Effect/Enemy_FireBall_Data.txt")	// テキスト
#define ENEMY_ICE_BALL_TEXT	 ("data/Effect/Enemy_IceBall_Data.txt")		// テキスト
#define REMAINDER			 (0)										// 余り0
#define MAX_LIFE			 (150)										// ライフの最大数
#define MIN_LIFE			 (0)										// ライフの最小数
#define MOVE_VALUE			 (2.5f)										// 移動量
#define SIZE				 (20.0f)									// サイズ
#define DAMAGE				 (20)										// ダメージ
#define WEAK_DAMAGE			 (100)										// 弱点ダメージ
#define DEVIDE				 (10)										// 割る数
#define SIZE_XYZ			 (D3DXVECTOR3(20.0f,20.0f,20.0f))			// サイズ
//******************************************************************************
// コンストラクタ
//******************************************************************************
CMagic::CMagic()
{
	m_pos			= INIT_D3DXVECTOR3;
	m_nCount		= INIT_INT;
	m_nCreateCount	= INIT_INT;
	m_nLife			= INIT_INT;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CMagic::~CMagic()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CMagic * CMagic::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, TYPE type)
{
	// CMagicのポインタ
	CMagic *pMagic;

	// メモリ確保
	pMagic = new CMagic;

	// 位置代入
	pMagic->m_pos = pos;

	// 移動量代入
	pMagic->m_move = move;

	// 位置代入
	pMagic->m_Type = type;

	// 初期化
	pMagic->Init();

	// ポインタを返す
	return pMagic;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CMagic::Init(void)
{
	// ライフ設定
	m_nLife = MAX_LIFE;

	// タイプ
	switch (m_Type)
	{
		// 火玉
	case TYPE_FIRE_BALL:
		// テキストファイル読み込み
		sprintf(m_cText, FIRE_BALL_TEXT);
		//オブジェクトタイプ設定
		SetObjType(OBJTYPE_MAGIC);
		break;
		// 氷玉
	case TYPE_ICE_BALL:
		// テキストファイル読み込み
		sprintf(m_cText, ICE_BALL_TEXT);
		//オブジェクトタイプ設定
		SetObjType(OBJTYPE_MAGIC);
		break;
		// 敵の火玉
	case TYPE_ENEMY_FIRE_BALL:
		// テキストファイル読み込み
		sprintf(m_cText, ENEMY_FIRE_BALL_TEXT);
		//オブジェクトタイプ設定
		SetObjType(OBJTYPE_ENEMY_MAGIC);
		break;
	case TYPE_ENEMY_ICE_BALL:
		// テキストファイル読み込み
		sprintf(m_cText, ENEMY_ICE_BALL_TEXT);
		//オブジェクトタイプ設定
		SetObjType(OBJTYPE_ENEMY_MAGIC);
		break;
	}

	// 読み込み
	Load(m_cText);
	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CMagic::Uninit(void)
{
	// 破棄
	Release();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CMagic::Update(void)
{
	// インクリメント
	m_nCount++;

	// デクリメント
	m_nLife--;

	// 余りが0の場合
	if (m_nCount % m_nCreateCount == REMAINDER)
	{
		CParticle::Create(m_pos, m_cText);
	}
	// ライフが0以下になったら
	if (m_nLife <= MIN_LIFE)
	{
		// 終了
		Uninit();
		return;
	}

	// 移動
	m_pos += m_move;

	// 当たり判定
	Collision();
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CMagic::Draw(void)
{
}
//******************************************************************************
// 当たり判定関数
//******************************************************************************
void CMagic::Collision(void)
{
	// サウンド取得
	CSound *pSound = CManager::GetSound();

	// CSceneのポインタ
	CScene *pScene = NULL;

	// 火球と氷球の場合
	if (m_Type == TYPE_FIRE_BALL || m_Type == TYPE_ICE_BALL)
	{
		do
		{
			// シーン取得
			pScene = GetScene(OBJTYPE_ENEMY);
			// NULLでない場合
			if (pScene != NULL)
			{
				// オブジェクトタイプ取得
				OBJTYPE objtype = pScene->GetObjType();

				// OBJTYPE_ENEMYの場合
				if (objtype == OBJTYPE_ENEMY)
				{
					// 位置取得
					D3DXVECTOR3 EnemyPos = ((CEnemy*)pScene)->GetPos();
					D3DXVECTOR3 EnemySize = ((CEnemy*)pScene)->GetSize();
					int nType = ((CGhost*)pScene)->GetType();
					// 円形の当たり判定
					if (CCollision::SphereCollision(m_pos, SIZE, EnemyPos, EnemySize.x) == true)
					{
						// 火球で敵が火の場合
						if (m_Type == TYPE_FIRE_BALL && nType == CGhost::TYPE_FIRE)
						{
							// 爆発音再生
							pSound->PlaySoundA(CSound::SOUND_LABEL_SE_FIRE_EXPLOSION);

							// エフェクト生成
							CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_FIRE_EXPLOSION);
							CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_FIRE_EXPLOSION_2);

							// ダメージ
							((CEnemy*)pScene)->Hit(DAMAGE);
							Uninit();
							return;
						}
						// 火球で敵が氷の場合
						if (m_Type == TYPE_FIRE_BALL && nType == CGhost::TYPE_ICE)
						{
							// 爆発音再生
							pSound->PlaySoundA(CSound::SOUND_LABEL_SE_FIRE_EXPLOSION);
							// エフェクト生成
							CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_FIRE_EXPLOSION);
							CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_FIRE_EXPLOSION_2);

							// ダメージ
							((CEnemy*)pScene)->Hit(WEAK_DAMAGE);
							Uninit();
							return;
						}
						// 氷球で敵が氷の場合
						if (m_Type == TYPE_ICE_BALL && nType == CGhost::TYPE_ICE)
						{
							// 爆発音再生
							pSound->PlaySoundA(CSound::SOUND_LABEL_SE_ICE_EXPLOSION);
							// エフェクト生成
							CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_ICE_EXPLOSION);
							CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_ICE_EXPLOSION_2);

							// ダメージ
							((CEnemy*)pScene)->Hit(DAMAGE);
							Uninit();
							return;
						}
						// 氷球で敵が火の場合
						if (m_Type == TYPE_ICE_BALL && nType == CGhost::TYPE_FIRE)
						{
							// 爆発音再生
							pSound->PlaySoundA(CSound::SOUND_LABEL_SE_ICE_EXPLOSION);
							// エフェクト生成
							CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_ICE_EXPLOSION);
							CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_ICE_EXPLOSION_2);

							// ダメージ
							((CEnemy*)pScene)->Hit(WEAK_DAMAGE);
							Uninit();
							return;
						}
					}
				}
			}
		} while (pScene != NULL);
	}
	// 敵の火球と氷球の場合
	if (m_Type == TYPE_ENEMY_FIRE_BALL || m_Type == TYPE_ENEMY_ICE_BALL)
	{
		do
		{
			// シーン取得
			pScene = GetScene(OBJTYPE_PLAYER);
			// NULLでない場合
			if (pScene != NULL)
			{
				// オブジェクトタイプ取得
				OBJTYPE objtype = pScene->GetObjType();

				// OBJTYPE_ENEMYの場合
				if (objtype == OBJTYPE_PLAYER)
				{
					// 位置
					D3DXVECTOR3 PlayerPos;

					// 位置取得
					PlayerPos.x = ((CPlayer*)pScene)->GetMtxWorld(CPlayer::PARTS_UNDER_BODY)._41;
					PlayerPos.y = ((CPlayer*)pScene)->GetMtxWorld(CPlayer::PARTS_UNDER_BODY)._42;
					PlayerPos.z = ((CPlayer*)pScene)->GetMtxWorld(CPlayer::PARTS_UNDER_BODY)._43;

					// サイズ取得
					D3DXVECTOR3 PlayerSize = ((CPlayer*)pScene)->GetSize();

					// 円形の当たり判定
					if (CCollision::SphereCollision(m_pos, SIZE, PlayerPos, PlayerSize.x / DEVIDE) == true)
					{
						// ヒット
						((CPlayer*)pScene)->Hit(DAMAGE);

						// 火の場合
						if (m_Type == TYPE_ENEMY_FIRE_BALL)
						{
							// エフェクト生成
							CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_ENEMY_FIRE_EXPLOSION);
							CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_ENEMY_FIRE_EXPLOSION_2);
						}
						// 氷の場合
						if (m_Type == TYPE_ENEMY_ICE_BALL)
						{
							// エフェクト生成
							CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_ICE_EXPLOSION);
							CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_ICE_EXPLOSION_2);
						}

						// 終了
						Uninit();
						return;
					}
				}
			}
			// NULLになるまで繰り返す
		} while (pScene != NULL);
	}
	do
	{
		// シーン取得
		pScene = GetScene(OBJTYPE_MAP_OBJ);
		// NULLでない場合
		if (pScene != NULL)
		{
			// オブジェクトタイプ取得
			OBJTYPE objtype = pScene->GetObjType();

			// OBJTYPE_ENEMYの場合
			if (objtype == OBJTYPE_MAP_OBJ)
			{
				// 位置取得
				D3DXVECTOR3 ObjPos = ((C3D_Obj*)pScene)->GetPos();

				// サイズ取得
				D3DXVECTOR3 ObjSize = ((C3D_Obj*)pScene)->GetSize();

				// 円形の当たり判定
				if (CCollision::RectangleCollision(m_pos, SIZE_XYZ, ObjPos, ObjSize) == true)
				{
					// 火の場合
					if (m_Type == TYPE_FIRE_BALL)
					{
						// 爆発音再生
						pSound->PlaySoundA(CSound::SOUND_LABEL_SE_FIRE_EXPLOSION);

						// エフェクト生成
						CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_FIRE_EXPLOSION);
						CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_FIRE_EXPLOSION_2);

						// タイプ取得
						int n3D_ObjType = ((C3D_Obj*)pScene)->GetType();

						// タイプが床ブロックの場合
						if (n3D_ObjType == C3D_Obj::TYPE_WOOD)
						{
							// エフェクト生成
							CParticle_Effect::Create(ObjPos, CParticle_Effect::TYPE_WOOD_EFFECT);
							CParticle_Effect::Create(ObjPos, CParticle_Effect::TYPE_WOOD_EFFECT_2);
							// 終了
							((C3D_Obj*)pScene)->Uninit();
						}
					}
					// 氷の場合
					if (m_Type == TYPE_ICE_BALL)
					{
						// 爆発音再生
						pSound->PlaySoundA(CSound::SOUND_LABEL_SE_ICE_EXPLOSION);

						// エフェクト生成
						CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_ICE_EXPLOSION);
						CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_ICE_EXPLOSION_2);
					}
					// 火の場合
					if (m_Type == TYPE_ENEMY_FIRE_BALL)
					{
						// エフェクト生成
						CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_ENEMY_FIRE_EXPLOSION);
						CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_ENEMY_FIRE_EXPLOSION_2);
					}
					// 氷の場合
					if (m_Type == TYPE_ENEMY_ICE_BALL)
					{
						// エフェクト生成
						CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_ICE_EXPLOSION);
						CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_ICE_EXPLOSION_2);
					}
					// 終了
					Uninit();
					return;
				}
			}
		}
		// NULLになるまで繰り返す
	} while (pScene != NULL);
	do
	{
		// シーン取得
		pScene = GetScene(OBJTYPE_BLOCK);
		// NULLでない場合
		if (pScene != NULL)
		{
			// オブジェクトタイプ取得
			OBJTYPE objtype = pScene->GetObjType();

			// OBJTYPE_ENEMYの場合
			if (objtype == OBJTYPE_BLOCK)
			{
				// 位置取得
				D3DXVECTOR3 BlockPos = ((CBlock*)pScene)->GetPos();

				// サイズ取得
				D3DXVECTOR3 BlockSize = ((CBlock*)pScene)->GetSize();

				// 円形の当たり判定
				if (CCollision::RectangleCollision(m_pos, SIZE_XYZ, BlockPos, BlockSize) == true)
				{
					// 火の場合
					if (m_Type == TYPE_FIRE_BALL)
					{
						// 爆発音再生
						pSound->PlaySoundA(CSound::SOUND_LABEL_SE_FIRE_EXPLOSION);

						// エフェクト生成
						CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_FIRE_EXPLOSION);
						CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_FIRE_EXPLOSION_2);
					}
					// 氷の場合
					if (m_Type == TYPE_ICE_BALL)
					{
						// 爆発音再生
						pSound->PlaySoundA(CSound::SOUND_LABEL_SE_ICE_EXPLOSION);

						// エフェクト生成
						CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_ICE_EXPLOSION);
						CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_ICE_EXPLOSION_2);
					}
					// 火の場合
					if (m_Type == TYPE_ENEMY_FIRE_BALL)
					{
						// エフェクト生成
						CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_ENEMY_FIRE_EXPLOSION);
						CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_ENEMY_FIRE_EXPLOSION_2);
					}
					// 氷の場合
					if (m_Type == TYPE_ENEMY_ICE_BALL)
					{
						// エフェクト生成
						CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_ICE_EXPLOSION);
						CParticle_Effect::Create(m_pos, CParticle_Effect::TYPE_ICE_EXPLOSION_2);
					}
					// 終了
					Uninit();
					return;
				}
			}
		}
		// NULLになるまで繰り返す
	} while (pScene != NULL);
}
//******************************************************************************
// 読み込み関数
//******************************************************************************
void CMagic::Load(const char * cText)
{
	// 読み込み用
	char cReedText[MAX_TEXT];

	// 文字の判別用
	char cHeadText[MAX_TEXT];

	// 使わない文字
	char cDie[MAX_TEXT];

	// ファイルポインタ
	FILE *pFile = NULL;

	// NULLの場合
	if (pFile == NULL)
	{
		//ファイルを開く
		pFile = fopen(cText, "r");

		// NULLでない場合
		if (pFile != NULL)
		{
			// SCRIPTの文字が見つかるまで
			while (strcmp(cHeadText, "SCRIPT") != INIT_INT)
			{
				// テキストからcReedText分文字を読み込む
				fgets(cReedText, sizeof(cReedText), pFile);

				// 読み込んだ文字ををcHeadTextに格納
				sscanf(cReedText, "%s", &cHeadText);
			}
			// cHeadTextがSCRIPTだったら
			if (strcmp(cHeadText, "SCRIPT") == INIT_INT)
			{
				// END_SCRIPTの文字が見つかるまで
				while (strcmp(cHeadText, "END_SCRIPT") != INIT_INT)
				{
					// テキストからcReedText分文字を読み込む
					fgets(cReedText, sizeof(cReedText), pFile);

					// 読み込んだ文字ををcHeadTextに格納
					sscanf(cReedText, "%s", &cHeadText);

					// cHeadTextがMOTIONSETだったら
					if (strcmp(cHeadText, "SETTINGS") == INIT_INT)
					{
						// END_MOTIONSETの文字が見つかるまで
						while (strcmp(cHeadText, "END_SETTINGS") != INIT_INT)
						{
							// テキストからcReedText分文字を読み込む
							fgets(cReedText, sizeof(cReedText), pFile);

							// 読み込んだ文字ををcHeadTextに格納
							sscanf(cReedText, "%s", &cHeadText);

							// cHeadTextがALPHA_BLENDの場合
							if (strcmp(cHeadText, "CREATE_COUNT") == INIT_INT)
							{
								// 情報をm_bAlpha_Blendに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nCreateCount);
							}
						}
					}
				}
				// ファイルを閉じる
				fclose(pFile);
			}
			// 開けなかったら
			else
			{
				printf("ファイルを開く事が出来ませんでした。\n");
			}
		}
	}
}