//******************************************************************************
// パーティクルエミッター [particle_emitter.cpp]
// Author : 管原　司
//******************************************************************************

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "../3D/3DPolygon/Particle/particle.h"
#include "particle_effect.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define FIRE_EXPLOSION			("data/Effect/Fire_Explosion_Data.txt")			// 火の爆発パス
#define ICE_EXPLOSION			("data/Effect/Ice_Explosion_Data.txt")			// 氷の爆発パス
#define FIRE_EXPLOSION_2		("data/Effect/Fire_Explosion2_Data.txt")		// 火の爆発パス
#define ICE_EXPLOSION_2			("data/Effect/Ice_Explosion2_Data.txt")			// 氷の爆発パス
#define ENEMY_FIRE_EXPLOSION	("data/Effect/Enemy_Fire_Explosion_Data.txt")	// 敵火の爆発パス
#define ENEMY_FIRE_EXPLOSION_2	("data/Effect/Enemy_Fire_Explosion2_Data.txt")	// 敵火の爆発パス
#define WOOD_EFFECT				("data/Effect/wood_effect_Data.txt")			// 木のエフェクト
#define WOOD_EFFECT_2			("data/Effect/wood_effect_2_Data.txt")			// 木のエフェクト
#define BLOCK_EFFECT			("data/Effect/Block_effect_Data.txt")			// ブロックエフェクト
#define STAR_EFFECT				("data/Effect/StarEffect_Data.txt")				// 星エフェクト
#define STAR_EFFECT2			("data/Effect/StarEffect2_Data.txt")			// 星エフェクト
#define REMAINDER				(0)												// 余り0
//******************************************************************************
// コンストラクタ
//******************************************************************************
CParticle_Effect::CParticle_Effect()
{
	m_pos				 = INIT_D3DXVECTOR3;
	m_nCreate_TotalCount = INIT_INT;
	memset(m_cText, NULL, sizeof(m_cText));
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CParticle_Effect::~CParticle_Effect()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CParticle_Effect * CParticle_Effect::Create(D3DXVECTOR3 pos, TYPE type)
{
	// CParticle_Effectのポインタ
	CParticle_Effect *pParticle_Effect = NULL;

	// NULLの場合
	if (pParticle_Effect == NULL)
	{
		// メモリ確保
		pParticle_Effect = new CParticle_Effect;

		// NULLでない場合
		if (pParticle_Effect != NULL)
		{
			// 位置代入
			pParticle_Effect->m_pos = pos;

			// タイプ代入
			pParticle_Effect->m_Type = type;

			// 初期化
			pParticle_Effect->Init();
		}
	}
	// ポインタを返す
	return pParticle_Effect;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CParticle_Effect::Init(void)
{
	// 種類
	switch (m_Type)
	{
	case TYPE_FIRE_EXPLOSION:
		// テキスト読み込み
		sprintf(m_cText, FIRE_EXPLOSION);
		break;
	case TYPE_ICE_EXPLOSION:
		// テキスト読み込み
		sprintf(m_cText, ICE_EXPLOSION);
		break;
	case TYPE_FIRE_EXPLOSION_2:
		// テキスト読み込み
		sprintf(m_cText, FIRE_EXPLOSION_2);
		break;
	case TYPE_ICE_EXPLOSION_2:
		// テキスト読み込み
		sprintf(m_cText, ICE_EXPLOSION_2);
		break;
	case TYPE_ENEMY_FIRE_EXPLOSION:
		// テキスト読み込み
		sprintf(m_cText,ENEMY_FIRE_EXPLOSION);
		break;
	case TYPE_ENEMY_FIRE_EXPLOSION_2:
		// テキスト読み込み
		sprintf(m_cText, ENEMY_FIRE_EXPLOSION_2);
		break;
	case TYPE_WOOD_EFFECT:
		// テキスト読み込み
		sprintf(m_cText, WOOD_EFFECT);
		break;
	case TYPE_WOOD_EFFECT_2:
		// テキスト読み込み
		sprintf(m_cText, WOOD_EFFECT_2);
		break;
	case TYPE_BLOCK_EFFECT:
		// テキスト読み込み
		sprintf(m_cText, BLOCK_EFFECT);
		break;
	case TYPE_STAR_EFFECT:
		// テキスト読み込み
		sprintf(m_cText, STAR_EFFECT);
		break;
	case TYPE_STAR_EFFECT2:
		// テキスト読み込み
		sprintf(m_cText, STAR_EFFECT2);
		break;
		// 例外
	default:
		break;
	}
	// 読み込み
	Load(m_cText);

	// 生成
	CParticle::CreateEffect(m_pos, m_nCreate_TotalCount, m_cText);

	// 破棄
	Uninit();

	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CParticle_Effect::Uninit(void)
{
	// 破棄
	Release();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CParticle_Effect::Update(void)
{
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CParticle_Effect::Draw(void)
{
}
//******************************************************************************
// 読み込み関数
//******************************************************************************
void CParticle_Effect::Load(const char * cText)
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
							if (strcmp(cHeadText, "CREATE_TOTAL_COUNT") == INIT_INT)
							{
								// 情報をm_bAlpha_Blendに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nCreate_TotalCount);
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