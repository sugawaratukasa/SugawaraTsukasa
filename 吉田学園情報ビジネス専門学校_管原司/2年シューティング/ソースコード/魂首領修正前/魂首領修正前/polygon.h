//---------------------------------------------------
// Polygon
// Polygon.h
// Authur:	�ǌ��i
//---------------------------------------------------
#ifndef _POLYGON_H_
#define _POLYGON_H_
//---------------------------------------------------
//�}�N��
//---------------------------------------------------
#define POLYGON_SIZE_X 320
#define RIGHT_POS_X 1120
#define LEFT_POS_X 160
//---------------------------------------------------
//�N���X
//---------------------------------------------------
class CPolygon : public CScene2d
{
public:
	CPolygon(int nPriority = PRIORITY_TYPE_POLYGON);
	~CPolygon();
	static CPolygon * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);
};
#endif