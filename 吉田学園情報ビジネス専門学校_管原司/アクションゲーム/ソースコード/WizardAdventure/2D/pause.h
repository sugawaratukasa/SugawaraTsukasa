//******************************************************************************
// ポーズ [pause.h]
// Author : 管原司
//******************************************************************************
#ifndef _PAUSE_H_
#define _PAUSE_H_
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "scene.h"
//******************************************************************************
// 前方宣言
//******************************************************************************
class C2D_Polygon;
//******************************************************************************
// クラス
//******************************************************************************
class CPause:public CScene
{
public:
	enum TYPE
	{
		TYPE_BLACK = 0,
		TYPE_RESUME,
		TYPE_CONTROLS,
		TYPE_EXIT,
		TYPE_MAX
	};
	CPause(int nPriority = OBJTYPE_NOSTOP_UI);
	~CPause();
	static CPause *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void Select(void);
	void Release(void);
	C2D_Polygon *m_apPolygon[TYPE_MAX];	// C2D_Polygonのポインタ
	int m_nCount;						// カウント
	bool m_bStick;						// スティックの判定
	bool m_bControls;					// 説明の判定
};

#endif
