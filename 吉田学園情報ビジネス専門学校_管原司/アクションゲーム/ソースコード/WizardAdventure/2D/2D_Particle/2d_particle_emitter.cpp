//******************************************************************************
// 2dパーティクルエミッター [2d_particle_emitter.cpp]
// Author : 管原　司
//******************************************************************************

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "scene.h"
#include "2d_particle.h"
#include "2d_particle_emitter.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define FIRE_EMITTER_TEXT	("data/Effect/2dFireEmitter_Data.txt")	 // テキストのパス
#define ICE_EMITTER_TEXT	("data/Effect/2dIceEmitter_Data.txt")	 // テキストのパス
#define GREEN_EMITTER		("data/Effect/2D_GreenEffect_Data.txt")	 // テキストのパス
#define REMAINDER			(0)										 // 余り0
//******************************************************************************
// コンストラクタ
//******************************************************************************
C2D_Particle_Emitter::C2D_Particle_Emitter()
{
	m_pos			= INIT_D3DXVECTOR3;
	m_nCount		= INIT_INT;
	m_nCreateCount	= INIT_INT;
	memset(m_cText, NULL, sizeof(m_cText));
}
//******************************************************************************
// デストラクタ
//******************************************************************************
C2D_Particle_Emitter::~C2D_Particle_Emitter()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
C2D_Particle_Emitter * C2D_Particle_Emitter::Create(D3DXVECTOR3 pos, TYPE type)
{
	// C2D_Particle_Emitterのポインタ
	C2D_Particle_Emitter *p2D_Particle_Emitter = NULL;

	// NULLの場合
	if (p2D_Particle_Emitter == NULL)
	{
		// メモリ確保
		p2D_Particle_Emitter = new C2D_Particle_Emitter;

		// NULLでない場合
		if (p2D_Particle_Emitter != NULL)
		{
			// 位置代入
			p2D_Particle_Emitter->m_pos = pos;

			// 位置代入
			p2D_Particle_Emitter->m_Type = type;

			// 初期化
			p2D_Particle_Emitter->Init();
		}
	}
	// ポインタを返す
	return p2D_Particle_Emitter;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT C2D_Particle_Emitter::Init(void)
{
	// タイプ
	switch (m_Type)
	{
		// 緑
	case TYPE_GREEN:
		// 読み込むファイル指定
		sprintf(m_cText, GREEN_EMITTER);
		break;
		// 火
	case TYPE_FIRE:
		// 読み込むファイル指定
		sprintf(m_cText, FIRE_EMITTER_TEXT);
		break;
		// 氷
	case TYPE_ICE:
		// 読み込むファイル指定
		sprintf(m_cText, ICE_EMITTER_TEXT);
		break;
		// 例外
	default:
		break;
	}

	// 読み込み
	Load(m_cText);
	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void C2D_Particle_Emitter::Uninit(void)
{
	// 破棄
	CScene::Release();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void C2D_Particle_Emitter::Update(void)
{
	// 生成処理
	CreateParticle();
}
//******************************************************************************
// 描画関数
//******************************************************************************
void C2D_Particle_Emitter::Draw(void)
{
}
//******************************************************************************
// 破棄関数
//******************************************************************************
void C2D_Particle_Emitter::Release(void)
{
	// 終了
	Uninit();
	return;
}
//******************************************************************************
// 位置設定関数
//******************************************************************************
void C2D_Particle_Emitter::SetPos(D3DXVECTOR3 pos)
{
	// 位置代入
	m_pos = pos;
}
//******************************************************************************
// パーティクル生成処理関数
//******************************************************************************
void C2D_Particle_Emitter::CreateParticle(void)
{
	// インクリメント
	m_nCount++;

	// 余りが0の場合
	if (m_nCount % m_nCreateCount == REMAINDER)
	{
		C2D_Particle::Create(m_pos, m_cText);
	}
}
//******************************************************************************
// 読み込み関数
//******************************************************************************
void C2D_Particle_Emitter::Load(const char * cText)
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