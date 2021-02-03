//******************************************************************************
// 黒ポリゴン [black_polygon.h]
// Author : 管原　司
//******************************************************************************
#ifndef _BLACK_POLYGON_H_
#define _BLACK_POLYGON_H_
//******************************************************************************
// マクロ定義
//******************************************************************************
#define POLYGON_SIZE			(D3DXVECTOR3(320.0f,SCREEN_HEIGHT,0.0f))		// サイズ
#define POLYGON_RIGHT_POS		(D3DXVECTOR3(1120.0f,SCREEN_HEIGHT / 2 ,0.0f))	// 右の位置
#define POLYGON_LEFT_POS		(D3DXVECTOR3(160.0f,SCREEN_HEIGHT / 2 ,0.0f))	// 左の位置
#define BLACK_POLYGON_COLOR		(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f))				// カラー
//******************************************************************************
// クラス
//******************************************************************************
class CBlack_Polygon : public CPolygon
{
public:
	CBlack_Polygon(int nPriority = OBJTYPE::OBJTYPE_UI);
	~CBlack_Polygon();
	static CBlack_Polygon *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, TEX_TYPE textype);
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:

};
#endif