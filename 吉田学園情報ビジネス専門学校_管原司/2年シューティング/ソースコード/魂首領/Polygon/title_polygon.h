//******************************************************************************
// タイトルポリゴン [title_polygon.h]
// Author : 管原　司
//******************************************************************************
#ifndef _TITLE_POLYGON_H_
#define _TITLE_POLYGON_H_
//******************************************************************************
// クラス
//******************************************************************************
class CTitle_Polygon : public CPolygon
{
public:
	CTitle_Polygon(int nPriority = OBJTYPE::OBJTYPE_UI);
	~CTitle_Polygon();
	static CTitle_Polygon *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, TEX_TYPE textype);
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:

};
#endif