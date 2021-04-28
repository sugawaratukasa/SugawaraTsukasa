//******************************************************************************
// 3Dポリゴン[3d_polygon.h]
// Author : 管原司
//******************************************************************************
#ifndef _3D_POLYGON_H_
#define _3D_POLYGON_H_
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "scene3d.h"
//******************************************************************************
// 前方宣言
//******************************************************************************

//******************************************************************************
// クラス
//******************************************************************************
class C3D_Polygon : public CScene3d
{
public:
	// テクスチャタイプの列挙型
	enum TEX_TYPE
	{
		TEX_TYPE_NONE = -1,
		TEX_TYPE_SKY,
		TEX_TYPE_CLOUD,
		TEX_TYPE_MAX
	};

	C3D_Polygon(int nPriority = OBJTYPE_BG);
	~C3D_Polygon();
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPolygon(D3DXVECTOR3 pos, D3DXVECTOR3 size, TEX_TYPE textype);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[TEX_TYPE_MAX];		// テクスチャへのポインタ
	TEX_TYPE m_Textype;										// テクスチャの種類
	bool m_bDraw;
};
#endif
