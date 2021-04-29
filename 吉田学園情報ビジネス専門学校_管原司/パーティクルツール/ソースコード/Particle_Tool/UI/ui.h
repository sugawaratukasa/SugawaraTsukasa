//***********************************************************************************
//	UI	[ui.h]
//	Author : 管原 司
//***********************************************************************************
#ifndef _UI_H_
#define _UI_H_
//***********************************************************************************
// インクルードファイル
//***********************************************************************************
#include "scene.h"
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
//***********************************************************************************
// マクロ定義
//***********************************************************************************
#define MAX_SAVE_CHAR	(16)		// セーブ用テキスト名の最大数
#define MAX_LOAD_CHAR	(16)		// ロード用テキスト名の最大数
//***********************************************************************************
// クラス
//***********************************************************************************
class CUI : public CScene
{
public:
	CUI(int nPriority = 0);
	~CUI();
	static CUI *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	//*********************************************************
	// 1番目のノードの設定
	//*********************************************************
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
	D3DXVECTOR3 GetMove(void) { return m_move; }
	D3DXVECTOR3 GetRandom_Pos(void) { return m_pos; }
	D3DXCOLOR GetColor(void) { return m_color; }
	D3DXCOLOR GetSubColor(void) { return m_SubColor; }
	float GetScale(void) { return m_fAddScale; }
	float GetAngle(void) { return m_fAngle; }
	D3DXVECTOR3 GetAddAngle(void) { return m_AddAngle; }
	float GetRandom_Min_Size(void) { return m_fRandom_Min_Size; }
	float GetRandom_Max_Size(void) { return m_fRandom_Max_Size; }
	bool GetUseAlpha_Blend(void) { return m_bAlpha_Blend; }
	bool GetbEmitter(void) { return m_bEmitter; }
	bool GetbEffect(void) { return m_bEffect; }
	bool GetbLife(void) { return m_bLife; }
	bool GetbRandomPos(void) { return m_bRandomPos; }
	bool GetRandomSize(void) { return m_bRandomSize; }
	bool GetbAddScale(void) { return m_bAddScale; }
	bool GetbSubColor(void) { return m_bSubColor; }
	bool GetbRotRandom(void) { return m_bRotRandom; }
	bool GetbTexRandom(void) { return m_bTex_Random; }
	bool GetColorRandom(void) { return m_bColorRandom; }
	int GetCreateCount(void) { return m_nCreateCount; }
	int GetCreateTotalCount(void) { return m_nCreateTotalCount; }
	int GetTexNum(void) { return m_nTexNum; }
	int GetAlpha(void) { return m_nAlpha; }
	int GetLife(void) { return m_nLife; }
	int GetMinTexRandomNum(void) { return m_nMinTexRamdomNum; }
	int GetMaxTexRandomNum(void) { return m_nMaxTexRamdomNum; }
	int GetColorRandom_R(void) { return m_nColor_R; }
	int GetColorRandom_G(void) { return m_nColor_G; }
	int GetColorRandom_B(void) { return m_nColor_B; }
	//*********************************************************
	// 2番目のノードのゲッター
	//*********************************************************
	D3DXVECTOR3 GetPos_2(void) { return m_pos_2; }
	D3DXVECTOR3 GetRot_2(void) { return m_rot_2; }
	D3DXVECTOR3 GetSize_2(void) { return m_size_2; }
	D3DXVECTOR3 GetMove_2(void) { return m_move_2; }
	D3DXVECTOR3 GetRandom_Pos_2(void) { return m_pos_2; }
	D3DXCOLOR GetColor_2(void) { return m_color_2; }
	D3DXCOLOR GetSubColor_2(void) { return m_SubColor_2; }
	float GetScale_2(void) { return m_fAddScale_2; }
	float GetAngle_2(void) { return m_fAngle_2; }
	D3DXVECTOR3 GetAddAngle_2(void) { return m_AddAngle_2; }
	float GetRandom_Min_Size_2(void) { return m_fRandom_Min_Size_2; }
	float GetRandom_Max_Size_2(void) { return m_fRandom_Max_Size_2; }
	bool GetUseAlpha_Blend_2(void) { return m_bAlpha_Blend_2; }
	bool GetbEmitter_2(void) { return m_bEmitter_2; }
	bool GetbEffect_2(void) { return m_bEffect_2; }
	bool GetbLife_2(void) { return m_bLife_2; }
	bool GetbRandomPos_2(void) { return m_bRandomPos_2; }
	bool GetRandomSize_2(void) { return m_bRandomSize_2; }
	bool GetbAddScale_2(void) { return m_bAddScale_2; }
	bool GetbSubColor_2(void) { return m_bSubColor_2; }
	bool GetbRotRandom_2(void) { return m_bRotRandom_2; }
	bool GetbTexRandom_2(void) { return m_bTex_Random_2; }
	bool GetColorRandom_2(void) { return m_bColorRandom_2; }
	int GetCreateCount_2(void) { return m_nCreateCount_2; }
	int GetCreateTotalCount_2(void) { return m_nCreateTotalCount_2; }
	int GetTexNum_2(void) { return m_nTexNum_2; }
	int GetAlpha_2(void) { return m_nAlpha_2; }
	int GetLife_2(void) { return m_nLife_2; }
	int GetMinTexRandomNum_2(void) { return m_nMinTexRamdomNum_2; }
	int GetMaxTexRandomNum_2(void) { return m_nMaxTexRamdomNum_2; }
	int GetColorRandom_R_2(void) { return m_nColor_R; }
	int GetColorRandom_G_2(void) { return m_nColor_G; }
	int GetColorRandom_B_2(void) { return m_nColor_B; }
private:
	void Save(const char *cText);
	void Save2(const char *cText);
	void Load(const char *cText);
	void Load2(const char *cText);
	void SettingNoad_1(void);
	void SettingNoad_2(void);
	bool m_bSetting_window;				// 各種設定window
	bool m_bSettingNoad_1;				// 一つ目のノード
	bool m_bSettingNoad_2;				// 二つ目のノード
//************************************************************
// 1番目のノード
//************************************************************
	bool m_bEmitter;					// エミッターのbool
	bool m_bEffect;						// エフェクトのbool
	bool m_bAlpha_Blend;				// アルファブレンドの使用判定
	bool m_bLife;						// ライフ
	bool m_bRandomPos;					// 位置ランダム
	bool m_bRandomSize;					// ランダムサイズ
	bool m_bAddScale;					// スケール
	bool m_bSubColor;					// カラー減算用のbool
	bool m_bSave;						// セーブ
	bool m_bLoad;						// ロード
	bool m_bSameSize;					// サイズXYを同じにするか
	bool m_bRotRandom;					// 向きランダム
	bool m_bTex_Random;					// テクスチャランダム
	bool m_bColorRandom;				// カラーランダム
	D3DXCOLOR m_color;					// 色
	D3DXVECTOR3 m_pos;					// 位置
	D3DXVECTOR3 m_rot;					// 向き
	D3DXVECTOR3 m_size;					// サイズ
	D3DXVECTOR3 m_move;					// 移動
	D3DXVECTOR3 m_AddAngle;				// 角度加算
	D3DXCOLOR m_SubColor;				// 色減算
	float m_fSize;						// サイズ
	float m_fRandom_Max_Size;			// ランダムサイズ
	float m_fRandom_Min_Size;			// ランダムサイズ
	float m_fAddScale;					// 拡大率加算量
	float m_fAngle;						// 角度
	int m_nCreateCount;					// 生成カウント
	int m_nCreateTotalCount;			// 生成の総数
	int m_nTexNum;						// テクスチャ番号
	int m_nAlpha;						// 透過値
	int m_nLife;						// ライフ
	int m_nMinTexRamdomNum;				// ランダムの最小値
	int m_nMaxTexRamdomNum;				// ランダムの最大値
	int m_nColor_R;						// 赤の量
	int m_nColor_G;						// 赤の量
	int m_nColor_B;						// 赤の量
	char m_cSave[MAX_SAVE_CHAR];		// セーブ用
	char m_cLoad[MAX_LOAD_CHAR];		// ロード用
//********************************************
// 2番目のノード
//********************************************
	bool m_bEmitter_2;					// エミッターのbool
	bool m_bEffect_2;					// エフェクトのbool
	bool m_bAlpha_Blend_2;				// アルファブレンドの使用判定
	bool m_bLife_2;						// ライフ
	bool m_bRandomPos_2;				// 位置ランダム
	bool m_bRandomSize_2;				// ランダムサイズ
	bool m_bAddScale_2;					// スケール
	bool m_bSubColor_2;					// カラー減算用のbool
	bool m_bSave_2;						// セーブ
	bool m_bLoad_2;						// ロード
	bool m_bSameSize_2;					// サイズXYを同じにするか
	bool m_bRotRandom_2;				// 向きランダム
	bool m_bTex_Random_2;				// テクスチャランダム
	bool m_bColorRandom_2;				// 色ランダム
	D3DXCOLOR m_color_2;				// 色
	D3DXVECTOR3 m_pos_2;				// 位置
	D3DXVECTOR3 m_rot_2;				// 向き
	D3DXVECTOR3 m_size_2;				// サイズ
	D3DXVECTOR3 m_move_2;				// 移動
	D3DXVECTOR3 m_AddAngle_2;			// 角度加算
	D3DXCOLOR m_SubColor_2;				// 色減算
	float m_fSize_2;					// サイズ
	float m_fRandom_Max_Size_2;			// ランダムサイズ
	float m_fRandom_Min_Size_2;			// ランダムサイズ
	float m_fAddScale_2;				// 拡大率加算量
	float m_fAngle_2;					// 角度
	int m_nCreateCount_2;				// 生成カウント
	int m_nCreateTotalCount_2;			// 生成の総数
	int m_nTexNum_2;					// テクスチャ番号
	int m_nAlpha_2;						// 透過値
	int m_nLife_2;						// ライフ
	int m_nMinTexRamdomNum_2;			// ランダムの最小値
	int m_nMaxTexRamdomNum_2;			// ランダムの最大値
	int m_nColor_R_2;					// 赤の量
	int m_nColor_G_2;					// 緑の量
	int m_nColor_B_2;					// 青の量
	char m_cSave_2[MAX_SAVE_CHAR];		// セーブ用
	char m_cLoad_2[MAX_LOAD_CHAR];		// ロード用
};
#endif