//******************************************************************************
// パーティクルエミッター [particle_emitter.cpp]
// Author : 管原　司
//******************************************************************************

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "scene.h"
#include "../3D/Model/player.h"
#include "../3D/3DPolygon/Particle/particle.h"
#include "../3D/Model/Enemy/ghost.h"
#include "particle_emitter.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define STAR_EMITTER_TEXT	("data/Effect/StarEmitter01_Data.txt")								// テキストのパス
#define FIRE_EMITTER_TEXT	("data/Effect/FireEmitter_Data.txt")								// テキストのパス
#define ICE_EMITTER_TEXT	("data/Effect/IceEmitter_Data.txt")									// テキストのパス
#define FIREGHOST_TEXT		("data/Effect/FireGhostEmitter_Data.txt")							// テキストのパス
#define ICEGHOST_TEXT		("data/Effect/IceGhostEmitter_Data.txt")							// テキストのパス
#define FIRE_ENEMY_CREATE	("data/Effect/Fire_Create_Data.txt")								// テキストのパス
#define ICE_ENEMY_CREATE	("data/Effect/Ice_Create_Data.txt")									// テキストのパス
#define MAP_EMITTER			("data/Effect/MapEffect_Data.txt")									// テキストのパス
#define STAR_EMITTER2_TEXT	("data/Effect/StarEmitter02_Data.txt")								// テキストのパス
#define MAP_POS				(D3DXVECTOR3(PlayerPos.x - 300.0f, 0.0f, -150.0f))					// 位置
#define MAP_POS2			(D3DXVECTOR3(PlayerPos.x + 300.0f, 0.0f, -150.0f))					// 位置
#define REMAINDER			(0)																	// 余り0
#define RELEASE_COUNT		(60)																// 破棄カウント
//******************************************************************************
// コンストラクタ
//******************************************************************************
CParticle_Emitter::CParticle_Emitter()
{
	m_pos				= INIT_D3DXVECTOR3;
	m_nCount			= INIT_INT;
	m_nCreateCount		= INIT_INT;
	memset(m_cText, NULL, sizeof(m_cText));
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CParticle_Emitter::~CParticle_Emitter()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CParticle_Emitter * CParticle_Emitter::Create(D3DXVECTOR3 pos, TYPE type)
{
	// CParticle_Emitterのポインタ
	CParticle_Emitter *pParticle_Emitter = NULL;

	// NULLの場合
	if (pParticle_Emitter == NULL)
	{
		// メモリ確保
		pParticle_Emitter = new CParticle_Emitter;

		// NULLでない場合
		if (pParticle_Emitter != NULL)
		{
			// 位置代入
			pParticle_Emitter->m_pos = pos;

			// 位置代入
			pParticle_Emitter->m_Type = type;

			// 初期化
			pParticle_Emitter->Init();
		}
	}
	// ポインタを返す
	return pParticle_Emitter;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CParticle_Emitter::Init(void)
{
	// タイプ
	switch (m_Type)
	{
	case TYPE_STAR_RIGHT:
		// テキストファイル読み込み
		sprintf(m_cText, STAR_EMITTER_TEXT);
		break;
	case TYPE_STAR_LEFT:
		// テキストファイル読み込み
		sprintf(m_cText, STAR_EMITTER_TEXT);
		break;
	case TYPE_FIRE_RIGHT:
		// テキストファイル読み込み
		sprintf(m_cText, FIRE_EMITTER_TEXT);
		break;
	case TYPE_FIRE_LEFT:
		// テキストファイル読み込み
		sprintf(m_cText, FIRE_EMITTER_TEXT);
		break;
	case TYPE_ICE_RIGHT:
		// テキストファイル読み込み
		sprintf(m_cText, ICE_EMITTER_TEXT);
		break;
	case TYPE_ICE_LEFT:
		// テキストファイル読み込み
		sprintf(m_cText, ICE_EMITTER_TEXT);
		break;
	case TYPE_FIRE_GHOST:
		// テキストファイル読み込み
		sprintf(m_cText, FIREGHOST_TEXT);
		break;
	case TYPE_ICE_GHOST:
		// テキストファイル読み込み
		sprintf(m_cText, ICEGHOST_TEXT);
		break;
	case TYPE_FIRE_CREATE:
		// ファイル読み込み
		sprintf(m_cText, FIRE_ENEMY_CREATE);
		break;
	case TYPE_ICE_CREATE:
		// ファイル読み込み
		sprintf(m_cText, ICE_ENEMY_CREATE);
		break;
	case TYPE_MAP:
		// ファイル読み込み
		sprintf(m_cText, MAP_EMITTER);
		break;
	case TYPE_STAR:
		// ファイル読み込み
		sprintf(m_cText, STAR_EMITTER2_TEXT);
		break;
	}

	// 読み込み
	Load(m_cText);
	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CParticle_Emitter::Uninit(void)
{
	// 破棄
	CScene::Release();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CParticle_Emitter::Update(void)
{
	// 生成処理
	CreateParticle();

	// タイプが右の場合
	if (m_Type == TYPE_STAR_RIGHT || m_Type == TYPE_FIRE_RIGHT || m_Type == TYPE_ICE_RIGHT)
	{
		// 星の処理
		Right_Arm();
	}
	// タイプが左の場合
	if (m_Type == TYPE_STAR_LEFT || m_Type == TYPE_FIRE_LEFT || m_Type == TYPE_ICE_LEFT)
	{
		// 星の処理
		Left_Arm();
	}
	// タイプがMAPの場合
	if (m_Type == TYPE_MAP)
	{
		// CSceneのポインタ
		CScene *pScene = NULL;

		do
		{
			// CScene取得
			pScene = GetScene(OBJTYPE_PLAYER);

			// NULLでない場合
			if (pScene != NULL)
			{
				// オブジェクトタイプ取得
				OBJTYPE objtype = pScene->GetObjType();

				// OBJTYPE_PLAYERの場合
				if (objtype == OBJTYPE_PLAYER)
				{
					// 向き取得
					int nRot = ((CPlayer*)pScene)->GetRotState();

					// プレイヤーの位置取得
					D3DXVECTOR3 PlayerPos = ((CPlayer*)pScene)->GetPos();

					// RIGHTの場合
					if (nRot == CPlayer::ROT_STATE_RIGHT)
					{
						// 位置設定
						m_pos = MAP_POS;
					}
					// LEFTの場合
					if (nRot == CPlayer::ROT_STATE_LEFT)
					{
						// 位置設定
						m_pos = MAP_POS2;
					}
				}
			}
			// NULLになるまで繰り返す
		} while (pScene != NULL);
	}
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CParticle_Emitter::Draw(void)
{
}
//******************************************************************************
// 破棄関数
//******************************************************************************
void CParticle_Emitter::Release(void)
{
	// 終了
	Uninit();
	return;
}
//******************************************************************************
// 位置設定関数
//******************************************************************************
void CParticle_Emitter::SetPos(D3DXVECTOR3 pos)
{
	// 位置代入
	m_pos = pos;
}
//******************************************************************************
// パーティクル生成処理関数
//******************************************************************************
void CParticle_Emitter::CreateParticle(void)
{
	// インクリメント
	m_nCount++;

	// 余りが0の場合
	if (m_nCount % m_nCreateCount == REMAINDER)
	{
		CParticle::Create(m_pos, m_cText);
	}

	// TYPE_FIRE_CREATEまたはTYPE_ICE_CREATEの場合
	if (m_Type == TYPE_FIRE_CREATE || m_Type == TYPE_ICE_CREATE)
	{
		// 100になったら
		if (m_nCount == RELEASE_COUNT)
		{
			// 終了
			Uninit();
			return;
		}
	}
}
//******************************************************************************
// 読み込み関数
//******************************************************************************
void CParticle_Emitter::Load(const char * cText)
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
//******************************************************************************
// 右手の処理関数
//******************************************************************************
void CParticle_Emitter::Right_Arm(void)
{
	// 位置
	D3DXVECTOR3 pos;

	// CSceneのポインタ
	CScene *pScene = NULL;

	// プレイヤー取得
	do
	{
		// シーン取得
		pScene = GetScene(OBJTYPE_PLAYER);

		// NULLでない場合
		if (pScene != NULL)
		{
			// オブジェクトタイプ取得
			OBJTYPE objtype = pScene->GetObjType();

			// オブジェクトタイププレイヤー
			if (objtype == OBJTYPE_PLAYER)
			{
				// 位置取得
				pos.x = ((CPlayer*)pScene)->GetMtxWorld(CPlayer::PARTS_DOWN_ARM_R)._41;
				pos.y = ((CPlayer*)pScene)->GetMtxWorld(CPlayer::PARTS_DOWN_ARM_R)._42;
				pos.z = ((CPlayer*)pScene)->GetMtxWorld(CPlayer::PARTS_DOWN_ARM_R)._43;

				// 位置代入
				m_pos = pos;
			}
		}
		// NULLになるまで繰り返す
	} while (pScene != NULL);
}
//******************************************************************************
// 左手の処理関数
//******************************************************************************
void CParticle_Emitter::Left_Arm(void)
{
	// 位置
	D3DXVECTOR3 pos;

	// CSceneのポインタ
	CScene *pScene = NULL;

	// プレイヤー取得
	do
	{
		// シーン取得
		pScene = GetScene(OBJTYPE_PLAYER);

		// NULLでない場合
		if (pScene != NULL)
		{
			// オブジェクトタイプ取得
			OBJTYPE objtype = pScene->GetObjType();

			// オブジェクトタイププレイヤー
			if (objtype == OBJTYPE_PLAYER)
			{
				// 位置取得
				pos.x = ((CPlayer*)pScene)->GetMtxWorld(CPlayer::PARTS_DOWN_ARM_L)._41;
				pos.y = ((CPlayer*)pScene)->GetMtxWorld(CPlayer::PARTS_DOWN_ARM_L)._42;
				pos.z = ((CPlayer*)pScene)->GetMtxWorld(CPlayer::PARTS_DOWN_ARM_L)._43;

				// 位置代入
				m_pos = pos;
			}
		}
		// NULLになるまで繰り返す
	} while (pScene != NULL);
}