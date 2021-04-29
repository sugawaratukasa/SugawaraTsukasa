//******************************************************************************
// リスト構造 [scene.h]
// Author : 管原　司
//******************************************************************************
#ifndef _SCENE_H_
#define _SCENE_H_
//******************************************************************************
// マクロ定義
//******************************************************************************
#define INIT_INT			(0)									// int型初期化
#define INIT_FLOAT			(0.0f)								// float型初期化
#define INIT_D3DXVECTOR3	(D3DXVECTOR3(0.0f,0.0f,0.0f))		// D3DXVECTOR3初期化
#define INIT_COLOR			(D3DXCOLOR(0.0f,0.0f,0.0f,0.0f))	// D3DXCOLOR初期化
#define RHW_VALUE			(1.0f)								// rhw値
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "main.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE| D3DFVF_TEX1)
#define NUM_VERTEX		(4)
#define NUM_POLYGON		(2)
//******************************************************************************
// 構造体宣言
//******************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	// 頂点座標
	float rhw;			// 座標変換用紙係数
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ
}VERTEX_2D;
//******************************************************************************
// クラス
//******************************************************************************
class CScene
{
public:
	// オブジェクトタイプの列挙型
	typedef enum
	{
		OBJTYPE_NONE = -1,
		OBJTYPE_BG,
		OBJTYPE_SHIP,
		OBJTYPE_ENEMY,
		OBJTYPE_DEFAULT,
		OBJTYPE_PLAYER,
		OBJTYPE_PLAYER_BULLET,
		OBJTYPE_PLAYER_WEPON,
		OBJTYPE_ENEMY_BULLET,
		OBJTYPE_BOSS,
		OBJTYPE_BOSS_RIGHT,
		OBJTYPE_BOSS_LEFT,
		OBJTYPE_PARTICLE,
		OBJTYPE_EXPLOSION,
		OBJTYPE_ITEM,
		OBJTYPE_UI,
		OBJTYPE_FADE,
		OBJTYPE_MAX
	}OBJTYPE;

	CScene(int nPriority = OBJTYPE_DEFAULT);
	virtual ~CScene();

	void SetObjType(OBJTYPE objType);
	OBJTYPE GetObjType(void) { return m_objType; }
	static CScene *GetScene(int nPriority);

	// 純粋仮想関数
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static void UpdateAll(void);
	static void DrawAll(void);
	static void ReleaseAll(void);
	static void DesignationReleaseAll(OBJTYPE type);
	static void SetUpdateStop(bool bUpdateStop);

	static bool GetUpdateStop(void) { return m_bUpdateStop; }

protected:
	void Release(void);

private:
	OBJTYPE m_objType;					// オブジェクトの種類
	static CScene *m_pTop[OBJTYPE_MAX];	// 先頭のオブジェクトへのポインタ
	static CScene *m_pCur[OBJTYPE_MAX];	// 現在のオブジェクトへのポインタ
	CScene *m_pPrev;					// 前のオブジェクトへのポインタ
	CScene *m_pNext;					// 次のオブジェクトへのポインタ
	int m_nPriority;					// 描画順
	static int m_nNext;					// 次のカウント	
	static bool m_bRelease;				// 破棄するかを判断する変数
	bool m_bDeath;						// 死亡フラグ
	static bool m_bUpdateStop;			// 更新停止するか判断する変数
};
#endif // !_RENDERER_H_