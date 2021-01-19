//******************************************************************************
// �|���S�� [polygon.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _POLYGON_H_
#define _POLYGON_H_
//******************************************************************************
// �}�N����`
//******************************************************************************
#define POLYGON_SIZE			(D3DXVECTOR3(320.0f,SCREEN_HEIGHT,0.0f))		// �T�C�Y
#define POLYGON_RIGHT_POS		(D3DXVECTOR3(1120.0f,SCREEN_HEIGHT / 2 ,0.0f))	// �E�̈ʒu
#define POLYGON_LEFT_POS		(D3DXVECTOR3(160.0f,SCREEN_HEIGHT / 2 ,0.0f))	// ���̈ʒu
//******************************************************************************
// �N���X
//******************************************************************************
class CPolygon : public CScene2d
{
public:
	CPolygon(int nPriority = 10);
	~CPolygon();
	static CPolygon * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
};
#endif