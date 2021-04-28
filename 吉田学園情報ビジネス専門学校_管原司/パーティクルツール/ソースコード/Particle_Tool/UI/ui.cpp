//***********************************************************************************
//	UI	[ui.cpp]
//	Author : 管原 司
//***********************************************************************************
//***********************************************************************************
// インクルードファイル
//***********************************************************************************
#include "main.h"
#include "manager.h"
#include "texture.h"
#include "ui.h"
#include <tchar.h>
//***********************************************************************************
// マクロ定義
//***********************************************************************************
#define MAX_SIZE				(100.0f)									// サイズの最大値
#define MIN_SIZE				(0.0f)										// サイズの最小値
#define MAX_MOVE				(10.0f)										// 移動量の最大値
#define MIN_MOVE				(-10.0f)									// 移動量の最小値
#define MAX_SCALE				(5.0f)										// 拡大率の最大値
#define MIN_SCALE				(-5.0f)										// 拡大率の最小値
#define MAX_ANGLE				(360.0f)									// 角度の最大値
#define MIN_ANGLE				(1.0f)										// 角度の最小値
#define MAX_COUNT				(500)										// カウントの最大値
#define MIN_COUNT				(1)											// カウントの最小値
#define SLIDER_VALUE			(1.0f)										// スライダーの加算量
#define SLIDER_VALUE2			(0.01f)										// スライダーの加算量
#define SLIDER_VALUE3			(1)											// スライダーの加算量
#define DEFAULT_SIZE			(30.0f)										// サイズの基準値
#define DEFAULT_COUNT			(10)										// カウントの基準値
#define DEFAULT_ANGLE			(360.0f)									// 角度の基準値
#define SIZE					(D3DXVECTOR3(m_fSize, m_fSize, 0.0f))		// サイズ
#define SIZE_2					(D3DXVECTOR3(m_fSize_2, m_fSize_2, 0.0f))	// サイズ
#define COLOR					(D3DXCOLOR(1.0f,1.0f, 1.0f, 1.0f))			// 色
#define NAME_NUM				(16)										// 名前
#define MIN_TEX					(0)											// テクスチャの最小数
#define SUB_TEXTURENUM			(1)											// テクスチャの番号を-1
#define MIN_ALPHA				(0)											// アルファの最小値
#define MAX_ALPHA				(255)										// アルファの最大値
#define SUBCOLOR_SLIDE			(0.01f)										// 色減算スライダー
#define MIN_SUBCOLOR			(0.0f)										// 色減算最小値
#define MAX_SUBCOLOR			(1.0f)										// 色減算
#define MAX_LIFE				(50)										// カウントの最大値
#define MIN_LIFE				(1)											// カウントの最小値
#define RANDOM_MIN_SIZE			(1.0f)										// ランダムサイズの最小値
#define RANDOM_SIZE_INIT		(30.0f)										// ランダムサイズの初期値
#define RANDOM_MIN_POS			(1.0f)										// ランダム位置の最小
#define RANDOM_MAX_POS			(100.0f)									// ランダム位置の最小
#define INIT_LIFE				(30)										// ライフ初期値
#define RANDOM_POS_INIT			(50.0f)										// ランダム位置の初期値
#define CREATE_TOTALCOUNT_INIT	(30)										// 生成の総数の初期値
#define MAX_TEXT				(1024)										// テキストの最大数
#define MIN_ADDANGLE			(-30.0f)									// 角度加算最小値
#define MAX_ADDANGLE			(30.0f)										// 角度加算最大値
#define MIN_ROT					(0.0f)										// 角度加算最小値
#define MAX_ROT					(360.0f)									// 角度加算最大値
#define INIT_COLORRANDOM		(255)										// 色のランダム値
#define MIN_RANDOMCOL			(1)											// ランダムカラー最小値
#define MAX_RANDOMCOL			(255)										// ランダムカラー最大値
//***********************************************************************************
//静的メンバ変数
//***********************************************************************************
//***********************************************************************************
// コンストラクタ
//***********************************************************************************
CUI::CUI(int nPriority)
{
	m_bSetting_window	= true;
	m_bSettingNoad_1	= false;
	m_bSettingNoad_2	= false;
	m_bEmitter			= false;
	m_bEffect			= false;
	m_bAlpha_Blend		= false;
	m_bLife				= true;
	m_bRandomPos		= false;
	m_bRandomSize		= false;
	m_bAddScale			= false;
	m_bSubColor			= false;
	m_bSave				= false;
	m_bLoad				= false;
	m_bSameSize			= false;
	m_bRotRandom		= false;
	m_bTex_Random		= false;
	m_bColorRandom		= false;
	m_fSize				= INIT_FLOAT;
	m_pos				= INIT_D3DXVECTOR3;
	m_rot				= INIT_D3DXVECTOR3;
	m_size				= INIT_D3DXVECTOR3;
	m_move				= INIT_D3DXVECTOR3;
	m_AddAngle			= INIT_D3DXVECTOR3;
	m_color				= INIT_COLOR;
	m_SubColor			= INIT_COLOR;
	m_fAddScale			= INIT_FLOAT;
	m_fAngle			= INIT_FLOAT;
	m_fRandom_Max_Size	= INIT_FLOAT;
	m_fRandom_Min_Size	= INIT_FLOAT;
	m_nCreateCount		= INIT_INT;
	m_nCreateTotalCount = INIT_INT;
	m_nTexNum			= INIT_INT;
	m_nAlpha			= INIT_INT;
	m_nLife				= INIT_INT;
	m_nMinTexRamdomNum	= INIT_INT;
	m_nMaxTexRamdomNum	= INIT_INT;
	m_nColor_R			= INIT_INT;
	m_nColor_G			= INIT_INT;
	m_nColor_B			= INIT_INT;
	memset(m_cSave, NULL, sizeof(m_cSave));
	memset(m_cLoad, NULL, sizeof(m_cLoad));
	//**********************************************
	// 二つ目
	//**********************************************
	m_bEmitter_2			= false;
	m_bEffect_2				= false;
	m_bAlpha_Blend_2		= false;
	m_bLife_2				= true;
	m_bRandomPos_2			= false;
	m_bRandomSize_2			= false;
	m_bAddScale_2			= false;
	m_bSubColor_2			= false;
	m_bSave_2				= false;
	m_bLoad_2				= false;
	m_bSameSize_2			= false;
	m_bRotRandom_2			= false;
	m_bTex_Random_2			= false;
	m_bColorRandom_2		= false;
	m_fSize_2				= INIT_FLOAT;
	m_pos_2					= INIT_D3DXVECTOR3;
	m_rot_2					= INIT_D3DXVECTOR3;
	m_size_2				= INIT_D3DXVECTOR3;
	m_move_2				= INIT_D3DXVECTOR3;
	m_AddAngle_2			= INIT_D3DXVECTOR3;
	m_color_2				= INIT_COLOR;
	m_SubColor_2			= INIT_COLOR;
	m_fAddScale_2			= INIT_FLOAT;
	m_fAngle_2				= INIT_FLOAT;
	m_fRandom_Max_Size_2	= INIT_FLOAT;
	m_fRandom_Min_Size_2	= INIT_FLOAT;
	m_nCreateCount_2		= INIT_INT;
	m_nCreateTotalCount_2	= INIT_INT;
	m_nTexNum_2				= INIT_INT;
	m_nAlpha_2				= INIT_INT;
	m_nLife_2				= INIT_INT;
	m_nMinTexRamdomNum_2	= INIT_INT;
	m_nMaxTexRamdomNum_2	= INIT_INT;
	m_nColor_R_2			= INIT_INT;
	m_nColor_G_2			= INIT_INT;
	m_nColor_B_2			= INIT_INT;
	memset(m_cSave_2, NULL, sizeof(m_cSave_2));
	memset(m_cLoad_2, NULL, sizeof(m_cSave_2));
}
//***********************************************************************************
// デストラクタ
//***********************************************************************************
CUI::~CUI()
{
}
//***********************************************************************************
// 生成関数
//***********************************************************************************
CUI * CUI::Create(void)
{
	// CUIのポインタ
	CUI *pUi = NULL;

	// NULLの場合
	if (pUi == NULL)
	{
		// メモリ確保
		pUi = new CUI;

		// NULLでない場合
		if (pUi != NULL)
		{
			// 初期化
			pUi->Init();
		}
	}
	// ポインタを返す
	return pUi;
}
//***********************************************************************************
// 初期化関数
//***********************************************************************************
HRESULT CUI::Init(void)
{
	// 色
	m_color = COLOR;

	// サイズx
	m_size.x = DEFAULT_SIZE;

	// サイズx
	m_size.y = DEFAULT_SIZE;

	// サイズ
	m_fSize = DEFAULT_SIZE;

	// ランダムサイズ
	m_fRandom_Min_Size = RANDOM_SIZE_INIT;

	// ランダムサイズ
	m_fRandom_Max_Size = RANDOM_SIZE_INIT;

	// 角度
	m_fAngle = DEFAULT_ANGLE;

	// カウント
	m_nCreateCount = DEFAULT_COUNT;

	// 生成の総数
	m_nCreateTotalCount = CREATE_TOTALCOUNT_INIT;

	// ライフ
	m_nLife = INIT_LIFE;

	// ランダム位置
	m_pos.x = RANDOM_POS_INIT;

	// ランダム位置
	m_pos.y = RANDOM_POS_INIT;

	// テクスチャ数取得
	int nTexNum = CManager::GetTexture()->GetTexNum();

	// ランダムテクスチャの最大
	m_nMaxTexRamdomNum = nTexNum - SUB_TEXTURENUM;

	// ランダム色の初期値
	m_nColor_R = INIT_COLORRANDOM;
	m_nColor_G = INIT_COLORRANDOM;
	m_nColor_B = INIT_COLORRANDOM;

	//**********************************************************
	// 2番目のノード
	//**********************************************************

	// 色
	m_color_2 = COLOR;

	// サイズx
	m_size_2.x = DEFAULT_SIZE;

	// サイズx
	m_size_2.y = DEFAULT_SIZE;

	// サイズ
	m_fSize_2 = DEFAULT_SIZE;

	// ランダムサイズ
	m_fRandom_Min_Size_2 = RANDOM_SIZE_INIT;

	// ランダムサイズ
	m_fRandom_Max_Size_2 = RANDOM_SIZE_INIT;

	// 角度
	m_fAngle_2 = DEFAULT_ANGLE;

	// カウント
	m_nCreateCount_2 = DEFAULT_COUNT;

	// 生成の総数
	m_nCreateTotalCount_2 = CREATE_TOTALCOUNT_INIT;

	// ライフ
	m_nLife_2 = INIT_LIFE;

	// ランダム位置
	m_pos_2.x = RANDOM_POS_INIT;

	// ランダム位置
	m_pos_2.y = RANDOM_POS_INIT;

	// ランダムテクスチャの最大
	m_nMaxTexRamdomNum_2 = nTexNum - SUB_TEXTURENUM;

	// ランダム色の初期値
	m_nColor_R_2 = INIT_COLORRANDOM;
	m_nColor_G_2 = INIT_COLORRANDOM;
	m_nColor_B_2 = INIT_COLORRANDOM;
	return S_OK;
}
//***********************************************************************************
// 終了関数
//***********************************************************************************
void CUI::Uninit(void)
{
	// 破棄
	Release();
}
//***********************************************************************************
// 更新関数
//***********************************************************************************
void CUI::Update(void)
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// ウィンドウ
	if (m_bSetting_window)
	{
		// ウィンドウ生成
		ImGui::Begin("SettingWindows");

		// 一番目のノードの設定
		SettingNoad_1();

		// 2番目のノードの設定
		SettingNoad_2();

		ImGui::End();
	}
	// 更新処理の終わりに
	ImGui::EndFrame();
}
//***********************************************************************************
// 描画関数
//***********************************************************************************
void CUI::Draw(void)
{
}
//***********************************************************************************
// 情報保存関数
//***********************************************************************************
void CUI::Save(const char *cText)
{
	FILE * pFile = NULL;

	// テキスト
	char cSaveText[MAX_TEXT] = {};

	// 読み込み
	sprintf(cSaveText, "%s.txt", cText);

	// NULLの場合
	if (pFile == NULL)
	{
		// ファイルの書き出し
		pFile = fopen(cSaveText, "w");

		// ファイルが空じゃないか
		if (pFile != NULL)
		{
			// 書き込み
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# パーティクルデータ保存テキスト\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "SCRIPT\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# 各種設定\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "SETTINGS\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# 生成カウント\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "CREATE_COUNT = %d\n", m_nCreateCount);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# 生成の総数\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "CREATE_TOTAL_COUNT = %d\n", m_nCreateTotalCount);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# EffectかEmitterか使用判定[false[0]/true[1]]\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "EMITTER = %d\n", (int)m_bEmitter);
			fprintf(pFile, "EFFECT = %d\n", (int)m_bEffect);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# 加算合成使用判定[false[0]/true[1]]\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "ALPHA_BLEND = %d\n", (int)m_bAlpha_Blend);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# ライフの使用判定[false[0]/true[1]]\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "LIFE = %d\n", (int)m_bLife);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# 位置をランダム使用判定[false[0]/true[1]]\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "RANDOM_POS = %d\n", (int)m_bRandomPos);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# ランダムサイズ使用判定[false[0]/true[1]]\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "RANDOM_SIZE = %d\n", (int)m_bRandomSize);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# 拡大使用判定[false[0]/true[1]]\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "ADD_SCALE = %d\n", (int)m_bAddScale);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# 色減算の使用判定[false[0]/true[1]]\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "COLOR_SUBTRACT = %d\n", (int)m_bSubColor);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# 向きランダムの使用判定[false[0]/true[1]]\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "ROT_RANDOM = %d\n", (int)m_bRotRandom);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# テクスチャランダムの使用判定[false[0]/true[1]]\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "TEX_RANDOM = %d\n", (int)m_bTex_Random);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# 色ランダムの使用判定[false[0]/true[1]]\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "COLOR_RANDOM = %d\n", (int)m_bColorRandom);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# テクスチャナンバー\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "TEXTURE_NUM = %d\n", m_nTexNum);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# ランダムテクスチャナンバー\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "MIN_TEXTURE_RANDOM_NUM = %d\n", m_nMinTexRamdomNum);
			fprintf(pFile, "MAX_TEXTURE_RANDOM_NUM = %d\n", m_nMaxTexRamdomNum);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# 透過値\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "ALPHA_NUM = %d\n", m_nAlpha);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# サイズ\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "SIZE = %.1f %.1f %.1f\n", m_size.x, m_size.y, m_size.z);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# 移動量\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "MOVE = %.1f %.1f %.1f\n", m_move.x, m_move.y, m_move.z);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# 角度\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "ANGLE = %.1f\n", m_fAngle);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# 角度加算\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "ADD_ANGLE = %.1f %.1f %.1f\n", m_AddAngle.x, m_AddAngle.y, m_AddAngle.z);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# 色\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "COLOR = %.1f %.1f %.1f %.1f \n", m_color.r, m_color.g, m_color.b, m_color.a);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# ライフの値\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "LIFE_VALUE = %d\n", m_nLife);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# 拡大率加算の値\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "ADD_SCALE_VALUE = %.3f\n", m_fAddScale);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# 色ランダムの値\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "COLOR_R_VALUE = %d\n", m_nColor_R);
			fprintf(pFile, "COLOR_G_VALUE = %d\n", m_nColor_G);
			fprintf(pFile, "COLOR_B_VALUE = %d\n", m_nColor_B);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# 色減算値の値\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "COLOR_SUB_VALUE = %.3f %.3f %.3f %.3f \n", m_SubColor.r, m_SubColor.g, m_SubColor.b, m_SubColor.a);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# ランダムサイズの値[最小/最大]\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "MIN_SIZE_VALUE = %.1f\n", m_fRandom_Min_Size);
			fprintf(pFile, "MAX_SIZE_VALUE = %.1f\n", m_fRandom_Max_Size);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# 位置ランダムの値\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "RANDOM_POS_VALUE = %.1f %.1f %.1f\n", m_pos.x, m_pos.y, m_pos.z);
			fprintf(pFile, "END_SETTINGS\n");
			fprintf(pFile, "\n");
			fprintf(pFile, "END_SCRIPT");

			// ファイルを閉じる
			fclose(pFile);
		}
	}
}
//***********************************************************************************
// 情報保存関数
//***********************************************************************************
void CUI::Save2(const char * cText)
{
	FILE * pFile = NULL;

	// テキスト
	char cSaveText[MAX_TEXT] = {};

	// 読み込み
	sprintf(cSaveText, "%s.txt", cText);

	// NULLの場合
	if (pFile == NULL)
	{
		// ファイルの書き出し
		pFile = fopen(cSaveText, "w");

		// ファイルが空じゃないか
		if (pFile != NULL)
		{
			// 書き込み
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# パーティクルデータ保存テキスト\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "SCRIPT\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# 各種設定\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "SETTINGS\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# EffectかEmitterか使用判定[false[0]/true[1]]\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "EMITTER = %d\n", (int)m_bEmitter_2);
			fprintf(pFile, "EFFECT = %d\n", (int)m_bEffect_2);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# 加算合成使用判定[false[0]/true[1]]\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "ALPHA_BLEND = %d\n", (int)m_bAlpha_Blend_2);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# ライフの使用判定[false[0]/true[1]]\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "LIFE = %d\n", (int)m_bLife_2);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# 位置をランダム使用判定[false[0]/true[1]]\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "RANDOM_POS = %d\n", (int)m_bRandomPos_2);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# ランダムサイズ使用判定[false[0]/true[1]]\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "RANDOM_SIZE = %d\n", (int)m_bRandomSize_2);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "ADD_SCALE = %d\n", (int)m_bAddScale_2);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# 色減算の使用判定[false[0]/true[1]]\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "COLOR_SUBTRACT = %d\n", (int)m_bSubColor_2);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# 向きランダムの使用判定[false[0]/true[1]]\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "ROT_RANDOM = %d\n", (int)m_bRotRandom_2);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# テクスチャランダムの使用判定[false[0]/true[1]]\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "TEX_RANDOM = %d\n", (int)m_bTex_Random_2);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# 色ランダムの使用判定[false[0]/true[1]]\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "COLOR_RANDOM = %d\n", (int)m_bColorRandom);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# テクスチャナンバー\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "TEXTURE_NUM = %d\n", m_nTexNum_2);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# ランダムテクスチャナンバー\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "MIN_TEXTURE_RANDOM_NUM = %d\n", m_nMinTexRamdomNum_2);
			fprintf(pFile, "MAX_TEXTURE_RANDOM_NUM = %d\n", m_nMaxTexRamdomNum_2);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# 透過値\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "ALPHA_NUM = %d\n", m_nAlpha_2);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# サイズ\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "SIZE = %.1f %.1f %.1f\n", m_size_2.x, m_size_2.y, m_size_2.z);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# 移動量\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "MOVE = %.1f %.1f %.1f\n", m_move_2.x, m_move_2.y, m_move_2.z);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# 拡大使用判定[false[0]/true[1]]\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# 角度\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "ANGLE = %.1f\n", m_fAngle_2);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# 角度加算\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "ADD_ANGLE = %.1f %.1f %.1f\n", m_AddAngle.x, m_AddAngle.y, m_AddAngle.z);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# 色\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "COLOR = %.1f %.1f %.1f %.1f \n", m_color_2.r, m_color_2.g, m_color_2.b, m_color_2.a);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# 生成カウント\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "CREATE_COUNT = %d\n", m_nCreateCount_2);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# 生成総数\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "CREATE_COUNT = %d\n", m_nCreateTotalCount_2);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# ライフの値\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "LIFE_VALUE = %d\n", m_nLife_2);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# 拡大率加算の値\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "ADD_SCALE_VALUE = %.3f\n", m_fAddScale_2);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# 色ランダムの値\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "COLOR_R_VALUE = %d\n", m_nColor_R);
			fprintf(pFile, "COLOR_G_VALUE = %d\n", m_nColor_G);
			fprintf(pFile, "COLOR_B_VALUE = %d\n", m_nColor_B);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# 色減算値の値\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "COLOR_SUB_VALUE = %.3f %.3f %.3f %.3f \n", m_SubColor_2.r, m_SubColor_2.g, m_SubColor_2.b, m_SubColor_2.a);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# ランダムサイズの値[最小/最大]\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "MIN_SIZE_VALUE = %.1f\n", m_fRandom_Min_Size_2);
			fprintf(pFile, "MAX_SIZE_VALUE = %.1f\n", m_fRandom_Max_Size_2);
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "# 位置ランダムの値\n");
			fprintf(pFile, "#*************************************\n");
			fprintf(pFile, "RANDOM_POS_VALUE = %.1f %.1f %.1f\n", m_pos_2.x, m_pos_2.y, m_pos_2.z);
			fprintf(pFile, "END_SETTINGS\n");
			fprintf(pFile, "\n");
			fprintf(pFile, "END_SCRIPT");

			// ファイルを閉じる
			fclose(pFile);
		}
	}
}
//***********************************************************************************
// 情報読み込み関数
//***********************************************************************************
void CUI::Load(const char * cText)
{
	// 読み込み用
	char cReedText[MAX_TEXT];

	// 文字の判別用
	char cHeadText[MAX_TEXT];

	// 使わない文字
	char cDie[MAX_TEXT];

	// テキスト
	char cSaveText[MAX_TEXT];

	// 読み込み
	sprintf(cSaveText, "%s.txt", cText);

	// ファイルポインタ
	FILE *pFile = NULL;

	// NULLの場合
	if (pFile == NULL)
	{
		//ファイルを開く
		pFile = fopen(cSaveText, "r");

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

							// cHeadTextがEMITTERの場合
							if (strcmp(cHeadText, "EMITTER") == INIT_INT)
							{
								// 情報をm_bEmitterに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bEmitter);
							}
							// cHeadTextがEFFECTの場合
							if (strcmp(cHeadText, "EFFECT") == INIT_INT)
							{
								// 情報をm_bEffectに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bEffect);
							}
							// cHeadTextがALPHA_BLENDの場合
							if (strcmp(cHeadText, "ALPHA_BLEND") == INIT_INT)
							{
								// 情報をm_bAlpha_Blendに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bAlpha_Blend);
							}
							// cHeadTextがLIFEの場合
							if (strcmp(cHeadText, "LIFE") == INIT_INT)
							{
								// 情報をm_bLifeに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bLife);
							}
							// cHeadTextがRANDOM_POSの場合
							if (strcmp(cHeadText, "RANDOM_POS") == INIT_INT)
							{
								// 情報をm_bRandomPosに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bRandomPos);
							}
							// cHeadTextがRANDOM_SIZEの場合
							if (strcmp(cHeadText, "RANDOM_SIZE") == INIT_INT)
							{
								// 情報をm_bRandomSizeに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bRandomSize);
							}
							// cHeadTextがADD_SCALEの場合
							if (strcmp(cHeadText, "ADD_SCALE") == INIT_INT)
							{
								// 情報をm_bAddScaleに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bAddScale);
							}
							// cHeadTextがCOLOR_SUBTRACTの場合
							if (strcmp(cHeadText, "COLOR_SUBTRACT") == INIT_INT)
							{
								// 情報をm_bSubColorに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bSubColor);
							}
							// cHeadTextがCOLOR_SUBTRACTの場合
							if (strcmp(cHeadText, "ROT_RANDOM") == INIT_INT)
							{
								// 情報をm_bSubColorに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bRotRandom);
							}
							// cHeadTextがTEXTURE_NUMの場合 
							if (strcmp(cHeadText, "TEXTURE_NUM") == INIT_INT)
							{
								// 情報をm_nTexNumに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nTexNum);
							}
							// cHeadTextがALPHA_NUMの場合
							if (strcmp(cHeadText, "ALPHA_NUM") == INIT_INT)
							{
								// 情報をm_nAlphaに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nAlpha);
							}
							// cHeadTextがSIZEの場合
							if (strcmp(cHeadText, "SIZE") == INIT_INT)
							{
								// 情報をm_bRandomPosに格納
								sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie, &m_size.x, &m_size.y, &m_size.z);
							}
							// cHeadTextがMOVEの場合
							if (strcmp(cHeadText, "MOVE") == INIT_INT)
							{
								// 情報をm_moveに格納
								sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie, &m_move.x, &m_move.y, &m_move.z);
							}
							// cHeadTextがANGLEの場合
							if (strcmp(cHeadText, "ANGLE") == INIT_INT)
							{
								// 情報をm_fAngleに格納
								sscanf(cReedText, "%s %s %f", &cDie, &cDie, &m_fAngle);
							}
							// cHeadTextがANGLEの場合
							if (strcmp(cHeadText, "ADD_ANGLE") == INIT_INT)
							{
								// 情報をm_fAngleに格納
								sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie, &m_AddAngle.x, &m_AddAngle.y, &m_AddAngle.z);
							}
							// cHeadTextがCOLORの場合
							if (strcmp(cHeadText, "COLOR") == INIT_INT)
							{
								// 情報をm_colorに格納
								sscanf(cReedText, "%s %s %f %f %f %f", &cDie, &cDie, &m_color.r, &m_color.g, &m_color.b, &m_color.a);
							}
							// cHeadTextがCREATE_COUNTの場合
							if (strcmp(cHeadText, "CREATE_COUNT") == INIT_INT)
							{
								// 情報をm_nCreateCountに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nCreateCount);
							}
							// cHeadTextがCREATE_TOTAL_COUNTの場合
							if (strcmp(cHeadText, "CREATE_TOTAL_COUNT") == INIT_INT)
							{
								// 情報をm_nCreateTotalCountに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nCreateTotalCount);
							}
							// cHeadTextがLIFE_VALUEの場合
							if (strcmp(cHeadText, "LIFE_VALUE") == INIT_INT)
							{
								// 情報をm_nLifeに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nLife);
							}
							// cHeadTextがADD_SCALE_VALUEの場合
							if (strcmp(cHeadText, "ADD_SCALE_VALUE") == INIT_INT)
							{
								/// 情報をm_fAddScaleに格納
								sscanf(cReedText, "%s %s %f", &cDie, &cDie, &m_fAddScale);
							}
							// cHeadTextがCOLOR_SUB_VALUEの場合
							if (strcmp(cHeadText, "COLOR_SUB_VALUE") == INIT_INT)
							{
								// 情報をm_SubColorに格納
								sscanf(cReedText, "%s %s %f %f %f %f", &cDie, &cDie, &m_SubColor.r, &m_SubColor.g, &m_SubColor.b, &m_SubColor.a);
							}
							// cHeadTextがMIN_SIZE_VALUEの場合
							if (strcmp(cHeadText, "MIN_SIZE_VALUE") == INIT_INT)
							{
								// 情報をm_fRandom_Min_Sizeに格納
								sscanf(cReedText, "%s %s %f", &cDie, &cDie, &m_fRandom_Min_Size);
							}
							// cHeadTextがMAX_SIZE_VALUEの場合
							if (strcmp(cHeadText, "MAX_SIZE_VALUE") == INIT_INT)
							{
								// 情報をm_fRandom_Max_Sizeに格納
								sscanf(cReedText, "%s %s %f", &cDie, &cDie, &m_fRandom_Max_Size);
							}
							// cHeadTextがRANDOM_POS_VALUEの場合
							if (strcmp(cHeadText, "RANDOM_POS_VALUE") == INIT_INT)
							{
								// 情報をm_fRandomPosに格納
								sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie, &m_pos.x, &m_pos.y, &m_pos.z);
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
//***********************************************************************************
// ノード2に情報読み込み関数
//***********************************************************************************
void CUI::Load2(const char * cText)
{
	// 読み込み用
	char cReedText[MAX_TEXT];

	// 文字の判別用
	char cHeadText[MAX_TEXT];

	// 使わない文字
	char cDie[MAX_TEXT];

	// テキスト
	char cSaveText[MAX_TEXT];

	// 読み込み
	sprintf(cSaveText, "%s.txt", cText);

	// ファイルポインタ
	FILE *pFile = NULL;

	// NULLの場合
	if (pFile == NULL)
	{
		//ファイルを開く
		pFile = fopen(cSaveText, "r");

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

							// cHeadTextがEMITTERの場合
							if (strcmp(cHeadText, "EMITTER") == INIT_INT)
							{
								// 情報をm_bEmitterに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bEmitter_2);
							}
							// cHeadTextがEFFECTの場合
							if (strcmp(cHeadText, "EFFECT") == INIT_INT)
							{
								// 情報をm_bEffectに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bEffect_2);
							}
							// cHeadTextがALPHA_BLENDの場合
							if (strcmp(cHeadText, "ALPHA_BLEND") == INIT_INT)
							{
								// 情報をm_bAlpha_Blendに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bAlpha_Blend_2);
							}
							// cHeadTextがLIFEの場合
							if (strcmp(cHeadText, "LIFE") == INIT_INT)
							{
								// 情報をm_bLifeに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bLife_2);
							}
							// cHeadTextがRANDOM_POSの場合
							if (strcmp(cHeadText, "RANDOM_POS") == INIT_INT)
							{
								// 情報をm_bRandomPosに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bRandomPos);
							}
							// cHeadTextがRANDOM_SIZEの場合
							if (strcmp(cHeadText, "RANDOM_SIZE") == INIT_INT)
							{
								// 情報をm_bRandomSizeに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bRandomSize_2);
							}
							// cHeadTextがADD_SCALEの場合
							if (strcmp(cHeadText, "ADD_SCALE") == INIT_INT)
							{
								// 情報をm_bAddScaleに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bAddScale_2);
							}
							// cHeadTextがCOLOR_SUBTRACTの場合
							if (strcmp(cHeadText, "COLOR_SUBTRACT") == INIT_INT)
							{
								// 情報をm_bSubColorに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bSubColor_2);
							}
							// cHeadTextがCOLOR_SUBTRACTの場合
							if (strcmp(cHeadText, "ROT_RANDOM") == INIT_INT)
							{
								// 情報をm_bSubColorに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_bRotRandom_2);
							}
							// cHeadTextがTEXTURE_NUMの場合 
							if (strcmp(cHeadText, "TEXTURE_NUM") == INIT_INT)
							{
								// 情報をm_nTexNumに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nTexNum_2);
							}
							// cHeadTextがALPHA_NUMの場合
							if (strcmp(cHeadText, "ALPHA_NUM") == INIT_INT)
							{
								// 情報をm_nAlphaに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nAlpha_2);
							}
							// cHeadTextがSIZEの場合
							if (strcmp(cHeadText, "SIZE") == INIT_INT)
							{
								// 情報をm_bRandomPosに格納
								sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie, &m_size_2.x, &m_size_2.y, &m_size_2.z);
							}
							// cHeadTextがMOVEの場合
							if (strcmp(cHeadText, "MOVE") == INIT_INT)
							{
								// 情報をm_moveに格納
								sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie, &m_move_2.x, &m_move_2.y, &m_move_2.z);
							}
							// cHeadTextがANGLEの場合
							if (strcmp(cHeadText, "ANGLE") == INIT_INT)
							{
								// 情報をm_fAngleに格納
								sscanf(cReedText, "%s %s %f", &cDie, &cDie, &m_fAngle_2);
							}
							// cHeadTextがANGLEの場合
							if (strcmp(cHeadText, "ADD_ANGLE") == INIT_INT)
							{
								// 情報をm_fAngleに格納
								sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie, &m_AddAngle_2.x, &m_AddAngle_2.y, &m_AddAngle_2.z);
							}
							// cHeadTextがCOLORの場合
							if (strcmp(cHeadText, "COLOR") == INIT_INT)
							{
								// 情報をm_colorに格納
								sscanf(cReedText, "%s %s %f %f %f %f", &cDie, &cDie, &m_color_2.r, &m_color_2.g, &m_color_2.b, &m_color_2.a);
							}
							// cHeadTextがCREATE_COUNTの場合
							if (strcmp(cHeadText, "CREATE_COUNT") == INIT_INT)
							{
								// 情報をm_nCreateCountに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nCreateCount_2);
							}
							// cHeadTextがCREATE_TOTAL_COUNTの場合
							if (strcmp(cHeadText, "CREATE_TOTAL_COUNT") == INIT_INT)
							{
								// 情報をm_nCreateTotalCountに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nCreateTotalCount_2);
							}
							// cHeadTextがLIFE_VALUEの場合
							if (strcmp(cHeadText, "LIFE_VALUE") == INIT_INT)
							{
								// 情報をm_nLifeに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nLife_2);
							}
							// cHeadTextがADD_SCALE_VALUEの場合
							if (strcmp(cHeadText, "ADD_SCALE_VALUE") == INIT_INT)
							{
								/// 情報をm_fAddScaleに格納
								sscanf(cReedText, "%s %s %f", &cDie, &cDie, &m_fAddScale_2);
							}
							// cHeadTextがCOLOR_SUB_VALUEの場合
							if (strcmp(cHeadText, "COLOR_SUB_VALUE") == INIT_INT)
							{
								// 情報をm_SubColorに格納
								sscanf(cReedText, "%s %s %f %f %f %f", &cDie, &cDie, &m_SubColor_2.r, &m_SubColor_2.g, &m_SubColor_2.b, &m_SubColor_2.a);
							}
							// cHeadTextがMIN_SIZE_VALUEの場合
							if (strcmp(cHeadText, "MIN_SIZE_VALUE") == INIT_INT)
							{
								// 情報をm_fRandom_Min_Sizeに格納
								sscanf(cReedText, "%s %s %f", &cDie, &cDie, &m_fRandom_Min_Size_2);
							}
							// cHeadTextがMAX_SIZE_VALUEの場合
							if (strcmp(cHeadText, "MAX_SIZE_VALUE") == INIT_INT)
							{
								// 情報をm_fRandom_Max_Sizeに格納
								sscanf(cReedText, "%s %s %f", &cDie, &cDie, &m_fRandom_Max_Size_2);
							}
							// cHeadTextがRANDOM_POS_VALUEの場合
							if (strcmp(cHeadText, "RANDOM_POS_VALUE") == INIT_INT)
							{
								// 情報をm_fRandomPosに格納
								sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie, &m_pos_2.x, &m_pos_2.y, &m_pos_2.z);
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
//***********************************************************************************
// ノード1の情報設定
//***********************************************************************************
void CUI::SettingNoad_1(void)
{
	// ツリーノード生成
	ImGui::SetNextTreeNodeOpen(m_bSettingNoad_1, ImGuiCond_Once);

	if (ImGui::TreeNode("SettingNoad_1"))
	{
		// Emitterチェックボックス
		ImGui::Checkbox("Emitter", &m_bEmitter);

		// エミッターがtrueの場合
		if (m_bEmitter)
		{
			// trueの場合
			if (m_bEffect == true)
			{
				m_bEffect = false;
			}

			// カウント設定用							
			ImGui::DragInt("Create Count", (int*)&m_nCreateCount, SLIDER_VALUE3, MIN_COUNT, MAX_COUNT);
		}

		// Effectチェックボックス
		ImGui::Checkbox("Effect", &m_bEffect);

		// エミッターがtrueの場合
		if (m_bEffect)
		{
			// trueの場合
			if (m_bEmitter == true)
			{
				m_bEmitter = false;
			}
			// カウント設定用							
			ImGui::DragInt("Create Count", (int*)&m_nCreateCount, SLIDER_VALUE3, MIN_COUNT, MAX_COUNT);

			// カウント設定用							
			ImGui::DragInt("Create TotalCount", (int*)&m_nCreateTotalCount, SLIDER_VALUE3, MIN_COUNT, MAX_COUNT);
		}

		// 現在のテクスチャナンバー
		ImGui::Text("TextureNumber = %d", m_nTexNum);

		// テクスチャ数取得
		int nTexNum = CManager::GetTexture()->GetTexNum();

		// チェックボックス
		ImGui::Checkbox("Texture_Radom", &m_bTex_Random);

		// falseの場合
		if (m_bTex_Random == true)
		{
			// テクスチャの最小スライダー
			ImGui::SliderInt("MinTextureNumber", (int*)&m_nMinTexRamdomNum, MIN_TEX, nTexNum - SUB_TEXTURENUM);

			// テクスチャの最大スライダー
			ImGui::SliderInt("MaxTextureNumber", (int*)&m_nMaxTexRamdomNum, MIN_TEX, nTexNum - SUB_TEXTURENUM);
		}

		// falseの場合
		if (m_bTex_Random == false)
		{
			// テクスチャのスライダー
			ImGui::SliderInt("TextureNumber", (int*)&m_nTexNum, MIN_TEX, nTexNum - SUB_TEXTURENUM);
		}

		// 透過値のスライダー
		ImGui::SliderInt("AlphaNum", (int*)&m_nAlpha, MIN_ALPHA, MAX_ALPHA);

		// チェックボックス
		ImGui::Checkbox("AlphaBlend", &m_bAlpha_Blend);

		// ライフのチェックボックス
		ImGui::Checkbox("Life", &m_bLife);

		// ライフ
		if (m_bLife)
		{
			// カウント設定用							
			ImGui::DragInt("Life", (int*)&m_nLife, SLIDER_VALUE3, MIN_LIFE, MAX_LIFE);
		}

		// ランダム位置のチェックボックス
		ImGui::Checkbox("RandomPos", &m_bRandomPos);

		// 位置ランダム
		if (m_bRandomPos)
		{
			// 位置ランダムサイズ設定							
			ImGui::DragFloat3("RandomPosValue", (float*)&m_pos, SLIDER_VALUE, RANDOM_MIN_POS, RANDOM_MAX_POS);
		}

		// チェックボックス
		ImGui::Checkbox("Rot_Random", &m_bRotRandom);

		// falseの場合
		if (m_bRotRandom == false)
		{
			// 移動量設定用
			ImGui::DragFloat3("rot", (float*)&m_rot, SLIDER_VALUE, MIN_ROT, MAX_ROT);
		}

		// チェックボックス
		ImGui::Checkbox("Same_Size", &m_bSameSize);

		// falseの場合
		if (m_bSameSize == false)
		{
			// サイズ設定用
			ImGui::DragFloat2("size", (float*)&m_size, SLIDER_VALUE, MIN_SIZE, MAX_SIZE);
		}
		// trueの場合
		if (m_bSameSize == true)
		{
			// サイズ設定用
			ImGui::DragFloat("size", (float*)&m_fSize, SLIDER_VALUE, MIN_SIZE, MAX_SIZE);

			// サイズ設定
			m_size = SIZE;
		}

		// チェックボックス
		ImGui::Checkbox("SizeRandom", &m_bRandomSize);

		// ランダムサイズ
		if (m_bRandomSize == true)
		{
			// サイズランダムサイズ設定							
			ImGui::DragFloat("MinSizeValue", (float*)&m_fRandom_Min_Size, SLIDER_VALUE, RANDOM_MIN_SIZE, MAX_SIZE);

			// サイズランダムサイズ設定							
			ImGui::DragFloat("MaxSizeValue", (float*)&m_fRandom_Max_Size, SLIDER_VALUE, RANDOM_MIN_SIZE, MAX_SIZE);
		}

		// 移動量設定用
		ImGui::DragFloat3("move", (float*)&m_move, SLIDER_VALUE, MIN_MOVE, MAX_MOVE);

		// チェックボックス
		ImGui::Checkbox("AddScale", &m_bAddScale);

		// 拡大率加算
		if (m_bAddScale)
		{
			// カウント設定用							
			ImGui::DragFloat("AddScale_Value", (float*)&m_fAddScale, SLIDER_VALUE2, MIN_SCALE, MAX_SCALE);
		}

		// 角度設定用
		ImGui::DragFloat("Angle", &m_fAngle, SLIDER_VALUE, MIN_ANGLE, MAX_ANGLE);

		// 角度加算設定用
		ImGui::DragFloat3("AddAngle", (float*)&m_AddAngle, SLIDER_VALUE, MIN_ADDANGLE, MAX_ADDANGLE);

		// チェックボックス
		ImGui::Checkbox("ColorRandom", &m_bColorRandom);

		// falseの場合
		if (m_bColorRandom == false)
		{
			// カラーエディット
			ImGui::ColorEdit4("color", (float*)&m_color);
		}
		// trueの場合
		if (m_bColorRandom == true)
		{
			// カラーエディット
			ImGui::DragInt("R", &m_nColor_R, SLIDER_VALUE3, MIN_RANDOMCOL, MAX_RANDOMCOL);

			// カラーエディット
			ImGui::DragInt("G", &m_nColor_G, SLIDER_VALUE3, MIN_RANDOMCOL, MAX_RANDOMCOL);

			// カラーエディット
			ImGui::DragInt("B", &m_nColor_B, SLIDER_VALUE3, MIN_RANDOMCOL, MAX_RANDOMCOL);
		}

		// チェックボックス
		ImGui::Checkbox("ColorSubtract", &m_bSubColor);

		// カラー減算
		if (m_bSubColor)
		{
			// 色減算値設定							
			ImGui::DragFloat4("SubColor Value", (float*)m_SubColor, SUBCOLOR_SLIDE, MIN_SUBCOLOR, MAX_SUBCOLOR);

			// チェックボックス
			ImGui::Checkbox("SubColor Close", &m_bSubColor);
		}

		// ツリーノード生成
		ImGui::SetNextTreeNodeOpen(m_bSave, ImGuiCond_Once);

		if (ImGui::TreeNode("Save"))
		{
			// テキスト名入力
			ImGui::InputTextWithHint("Save Text", "Save Text Name", m_cSave, sizeof(m_cSave));

			// セーブ
			if (ImGui::Button("Save"))
			{
				// NULLでない場合
				if (m_cSave != NULL)
				{
					// 保存
					Save(m_cSave);
				}
			}
			ImGui::TreePop();
		}

		// ツリーノード生成
		ImGui::SetNextTreeNodeOpen(m_bLoad, ImGuiCond_Once);

		if (ImGui::TreeNode("Load"))
		{
			// テキスト名入力
			ImGui::InputTextWithHint("Load Text", "Load Text Name", m_cLoad, sizeof(m_cLoad));

			// セーブ
			if (ImGui::Button("Load"))
			{
				// NULLでない場合
				if (m_cSave != NULL)
				{
					// 保存
					Load(m_cLoad);
				}
			}
			ImGui::TreePop();
		}
		ImGui::TreePop();
	}
}
//***********************************************************************************
// ノード2の情報設定
//***********************************************************************************
void CUI::SettingNoad_2(void)
{
	ImGui::SetNextTreeNodeOpen(m_bSettingNoad_2, ImGuiCond_Once);

	if (ImGui::TreeNode("SettingNoad_2"))
	{
		// Emitterチェックボックス
		ImGui::Checkbox("Emitter", &m_bEmitter_2);

		// エミッターがtrueの場合
		if (m_bEmitter_2)
		{
			// trueの場合
			if (m_bEffect_2 == true)
			{
				m_bEffect_2 = false;
			}
			// カウント設定用							
			ImGui::DragInt("Create Count", (int*)&m_nCreateCount_2, SLIDER_VALUE3, MIN_COUNT, MAX_COUNT);
		}

		// Effectチェックボックス
		ImGui::Checkbox("Effect", &m_bEffect_2);

		// エミッターがtrueの場合
		if (m_bEffect_2)
		{
			// trueの場合
			if (m_bEmitter_2 == true)
			{
				m_bEmitter_2 = false;
			}
			// カウント設定用							
			ImGui::DragInt("Create Count2", (int*)&m_nCreateCount_2, SLIDER_VALUE3, MIN_COUNT, MAX_COUNT);

			// カウント設定用							
			ImGui::DragInt("Create TotalCount2", (int*)&m_nCreateTotalCount_2, SLIDER_VALUE3, MIN_COUNT, MAX_COUNT);
		}

		// テクスチャ数取得
		int nTexNum = CManager::GetTexture()->GetTexNum();

		// チェックボックス
		ImGui::Checkbox("Texture_Radnom", &m_bTex_Random_2);

		// trueの場合
		if (m_bTex_Random_2 == true)
		{
			// テクスチャの最小スライダー
			ImGui::SliderInt("MinTextureNumber", (int*)&m_nMinTexRamdomNum_2, MIN_TEX, nTexNum - SUB_TEXTURENUM);

			// テクスチャの最大スライダー
			ImGui::SliderInt("MaxTextureNumber", (int*)&m_nMaxTexRamdomNum_2, MIN_TEX, nTexNum - SUB_TEXTURENUM);
		}

		// falseの場合
		if (m_bTex_Random_2 == false)
		{
			// テクスチャのスライダー
			ImGui::SliderInt("TextureNumber", (int*)&m_nTexNum_2, MIN_TEX, nTexNum - SUB_TEXTURENUM);
		}

		// 透過値のスライダー
		ImGui::SliderInt("AlphaNum", (int*)&m_nAlpha_2, MIN_ALPHA, MAX_ALPHA);

		// チェックボックス
		ImGui::Checkbox("AlphaBlend", &m_bAlpha_Blend_2);

		// ライフのチェックボックス
		ImGui::Checkbox("Life", &m_bLife_2);

		// ライフ
		if (m_bLife_2)
		{
			// カウント設定用							
			ImGui::DragInt("Life", (int*)&m_nLife_2, SLIDER_VALUE3, MIN_LIFE, MAX_LIFE);
		}

		// ランダム位置のチェックボックス
		ImGui::Checkbox("RandomPos", &m_bRandomPos_2);

		// 位置ランダム
		if (m_bRandomPos_2)
		{
			// 位置ランダムサイズ設定							
			ImGui::DragFloat3("RandomPosValue2", (float*)&m_pos_2, SLIDER_VALUE, RANDOM_MIN_POS, RANDOM_MAX_POS);
		}

		// チェックボックス
		ImGui::Checkbox("Rot_Random", &m_bRotRandom_2);

		// falseの場合
		if (m_bRotRandom_2 == false)
		{
			// 移動量設定用
			ImGui::DragFloat3("rot", (float*)&m_rot_2, SLIDER_VALUE, MIN_ROT, MAX_ROT);
		}
		// ランダム位置のチェックボックス
		ImGui::Checkbox("Same_Size", &m_bSameSize_2);

		// falseの場合
		if (m_bSameSize_2 == false)
		{
			// サイズ設定用
			ImGui::DragFloat2("size", (float*)&m_size_2, SLIDER_VALUE, MIN_SIZE, MAX_SIZE);
		}
		// trueの場合
		if (m_bSameSize_2 == true)
		{
			// サイズ設定用
			ImGui::DragFloat("size", (float*)&m_fSize_2, SLIDER_VALUE, MIN_SIZE, MAX_SIZE);

			// サイズ設定
			m_size_2 = SIZE_2;
		}

		// チェックボックス
		ImGui::Checkbox("SizeRandom", &m_bRandomSize_2);

		// ランダムサイズ
		if (m_bRandomSize_2 == true)
		{
			// サイズランダムサイズ設定							
			ImGui::DragFloat("MinSizeValue2", (float*)&m_fRandom_Min_Size_2, SLIDER_VALUE, RANDOM_MIN_SIZE, MAX_SIZE);

			// サイズランダムサイズ設定							
			ImGui::DragFloat("MaxSizeValue2", (float*)&m_fRandom_Max_Size_2, SLIDER_VALUE, RANDOM_MIN_SIZE, MAX_SIZE);
		}

		// 移動量設定用
		ImGui::DragFloat3("move", (float*)&m_move_2, SLIDER_VALUE, MIN_MOVE, MAX_MOVE);

		// チェックボックス
		ImGui::Checkbox("AddScale", &m_bAddScale_2);

		// 拡大率加算
		if (m_bAddScale_2)
		{
			// カウント設定用							
			ImGui::DragFloat("AddScale_Value2", (float*)&m_fAddScale_2, SLIDER_VALUE2, MIN_SCALE, MAX_SCALE);
		}

		// 角度設定用
		ImGui::DragFloat("Angle", &m_fAngle_2, SLIDER_VALUE, MIN_ANGLE, MAX_ANGLE);

		// 角度加算設定用
		ImGui::DragFloat3("AddAngle", (float*)&m_AddAngle_2, SLIDER_VALUE, MIN_ADDANGLE, MAX_ADDANGLE);

		// チェックボックス
		ImGui::Checkbox("ColorRandom", &m_bColorRandom_2);

		// falseの場合
		if (m_bColorRandom_2 == false)
		{
			// カラーエディット
			ImGui::ColorEdit4("color", (float*)&m_color_2);
		}
		// trueの場合
		if (m_bColorRandom == true)
		{
			// カラーエディット
			ImGui::DragInt("R", &m_nColor_R_2, SLIDER_VALUE3, MIN_RANDOMCOL, MAX_RANDOMCOL);

			// カラーエディット
			ImGui::DragInt("G", &m_nColor_G_2, SLIDER_VALUE3, MIN_RANDOMCOL, MAX_RANDOMCOL);

			// カラーエディット
			ImGui::DragInt("B", &m_nColor_B_2, SLIDER_VALUE3, MIN_RANDOMCOL, MAX_RANDOMCOL);
		}

		// チェックボックス
		ImGui::Checkbox("ColorSubtract", &m_bSubColor_2);

		// カラー減算
		if (m_bSubColor_2)
		{
			// 色減算値設定							
			ImGui::DragFloat4("SubColor Value2", (float*)m_SubColor_2, SUBCOLOR_SLIDE, MIN_SUBCOLOR, MAX_SUBCOLOR);
		}

		ImGui::SetNextTreeNodeOpen(m_bSave_2, ImGuiCond_Once);

		if (ImGui::TreeNode("Save"))
		{
			// テキスト名入力
			ImGui::InputTextWithHint("Save Text", "Save Text Name", m_cSave_2, sizeof(m_cSave_2));

			// セーブ
			if (ImGui::Button("Save"))
			{
				// NULLでない場合
				if (m_cSave != NULL)
				{
					// 保存
					Save2(m_cSave_2);
				}
			}
			ImGui::TreePop();
		}

		ImGui::SetNextTreeNodeOpen(m_bLoad_2, ImGuiCond_Once);

		if (ImGui::TreeNode("Load"))
		{
			// テキスト名入力
			ImGui::InputTextWithHint("Load Text", "Load Text Name", m_cLoad_2, sizeof(m_cLoad_2));

			// セーブ
			if (ImGui::Button("Load"))
			{
				// NULLでない場合
				if (m_cSave != NULL)
				{
					// 保存
					Load2(m_cLoad_2);
				}
			}
			ImGui::TreePop();
		}
		ImGui::TreePop();
	}
}
