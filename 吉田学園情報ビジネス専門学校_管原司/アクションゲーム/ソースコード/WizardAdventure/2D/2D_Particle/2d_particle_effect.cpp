//******************************************************************************
// 2Dパーティクルエミッター [2d_particle_emitter.cpp]
// Author : 管原　司
//******************************************************************************

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "2d_particle.h"
#include "2d_particle_effect.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define COLOR_BOM	("data/Effect/ColorBom_Data.txt")		// パス
#define REMAINDER	(0)									// 余り0
//******************************************************************************
// コンストラクタ
//******************************************************************************
C2D_Particle_Effect::C2D_Particle_Effect()
{
	m_pos					= INIT_D3DXVECTOR3;
	m_nCreate_TotalCount	= INIT_INT;
	memset(m_cText, NULL, sizeof(m_cText));
}
//******************************************************************************
// デストラクタ
//******************************************************************************
C2D_Particle_Effect::~C2D_Particle_Effect()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
C2D_Particle_Effect *C2D_Particle_Effect::Create(D3DXVECTOR3 pos, TYPE type)
{
	// C2D_Particle_Effectのポインタ
	C2D_Particle_Effect *p2D_Particle_Effect = NULL;

	// NULLの場合
	if (p2D_Particle_Effect == NULL)
	{
		// メモリ確保
		p2D_Particle_Effect = new C2D_Particle_Effect;

		// NULLでない場合
		if (p2D_Particle_Effect != NULL)
		{
			// 位置代入
			p2D_Particle_Effect->m_pos = pos;

			// タイプ代入
			p2D_Particle_Effect->m_Type = type;

			// 初期化
			p2D_Particle_Effect->Init();
		}
	}
	// ポインタを返す
	return p2D_Particle_Effect;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT C2D_Particle_Effect::Init(void)
{
	// 種類
	switch (m_Type)
	{
		// カラーボム
	case TYPE_COLOR_BOM:
		// 生成
		// テキスト読み込み
		sprintf(m_cText, COLOR_BOM);
		break;
		// 例外
	default:
		break;
	}
	// 読み込み
	Load(m_cText);

	// 生成
	C2D_Particle::CreateEffect(m_pos, m_nCreate_TotalCount, m_cText);

	// 破棄
	Uninit();

	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void C2D_Particle_Effect::Uninit(void)
{
	// 破棄
	Release();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void C2D_Particle_Effect::Update(void)
{
}
//******************************************************************************
// 描画関数
//******************************************************************************
void C2D_Particle_Effect::Draw(void)
{
}
//******************************************************************************
// 読み込み関数
//******************************************************************************
void C2D_Particle_Effect::Load(const char * cText)
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