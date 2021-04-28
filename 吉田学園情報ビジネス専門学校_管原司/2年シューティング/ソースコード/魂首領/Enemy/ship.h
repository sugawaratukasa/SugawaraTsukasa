//******************************************************************************
// 船 [ship.h]
// Author : 管原　司
//******************************************************************************
#ifndef _SHIP_H_
#define _SHIP_H_
//******************************************************************************
// クラス
//******************************************************************************
class CShip : public CScene2d
{
public:
	CShip(int nPriority = OBJTYPE_SHIP);
	~CShip();
	static HRESULT Load(void);
	static void Unload(void);
	static CShip * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void BatteryCreate(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//　テクスチャ情報
};
#endif