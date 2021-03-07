//******************************************************************************
// チュートリアルポリゴン [tutrial_polygon.h]
// Author : 管原　司
//******************************************************************************
#ifndef _TUTRIAL_POLYGON_H_
#define _TUTRIAL_POLYGON_H_
//******************************************************************************
// クラス
//******************************************************************************
class CTutrial_Polygon : public CPolygon
{
public:
	CTutrial_Polygon(int nPriority = OBJTYPE::OBJTYPE_UI);
	~CTutrial_Polygon();
	static CTutrial_Polygon *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, TEX_TYPE textype);
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:

};
#endif