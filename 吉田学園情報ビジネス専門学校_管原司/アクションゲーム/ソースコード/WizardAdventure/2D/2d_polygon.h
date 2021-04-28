//******************************************************************************
// 2D_ポリゴン [2d_polygon.h]
// Author : 管原司
//******************************************************************************
#ifndef _2D_POLYGON_H_
#define _2D_POLYGON_H_
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "scene2d.h"
//******************************************************************************
// クラス
//******************************************************************************
class C2D_Polygon :public CScene2D
{
public:
	enum TYPE
	{
		TYPE_NONE = -1,
		TYPE_RESUME,
		TYPE_CONTROLS,
		TYPE_EXIT,
		TYPE_GAMESTART,
		TYPE_TITLE,
		TYPE_TITLE_BG,
		TYPE_PRESS_START,
		TYPE_RESULT,
		TYPE_MAGIC_UI,
		TYPE_CONTROLS_BG,
		TYPE_MAX
	};
	C2D_Polygon(int nPriority = OBJTYPE_NOSTOP_UI);
	~C2D_Polygon();
	static C2D_Polygon *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	TYPE m_Type;	// 種類
	bool m_bStick;	// スティックの判定
	bool m_bColor;	// 判定
};

#endif
