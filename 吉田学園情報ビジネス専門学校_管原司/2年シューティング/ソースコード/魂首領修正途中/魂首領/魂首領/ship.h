//******************************************************************************
// 船 [ship.h]
// Author : 管原　司
//******************************************************************************
#ifndef _SHIP_H_
#define _SHIP_H_
//******************************************************************************
// マクロ定義
//******************************************************************************
#define SHIP_SIZE			(D3DXVECTOR3(1000.0f,1800.0f,0.0f))	// 船のサイズ
#define SHIP_BATTERY_POS1	(D3DXVECTOR3(150.0f,400.0f,0.0f))	// 砲台の位置1
#define SHIP_BATTERY_POS2	(D3DXVECTOR3(-150.0f,400.0f,0.0f))	// 砲台の位置2
#define SHIP_BATTERY_POS3	(D3DXVECTOR3(280.0f,-20.0f,0.0f))	// 砲台の位置3
#define SHIP_BATTERY_POS4	(D3DXVECTOR3(-280.0f,-20.0f,0.0f))	// 砲台の位置4
#define SHIP_BATTERY_POS5	(D3DXVECTOR3(-280.0f,-550.0f,0.0f))	// 砲台の位置5
#define SHIP_BATTERY_POS6	(D3DXVECTOR3(280.0f,-550.0f,0.0f))	// 砲台の位置6
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
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//　テクスチャ情報
};
#endif