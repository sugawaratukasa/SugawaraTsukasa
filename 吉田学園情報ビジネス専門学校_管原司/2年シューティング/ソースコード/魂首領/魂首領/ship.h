//******************************************************************************
// �D [ship.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _SHIP_H_
#define _SHIP_H_
//******************************************************************************
// �}�N����`
//******************************************************************************
#define SHIP_SIZE			(D3DXVECTOR3(1000.0f,1800.0f,0.0f))	// �D�̃T�C�Y
#define SHIP_BATTERY_POS1	(D3DXVECTOR3(150.0f,400.0f,0.0f))	// �C��̈ʒu1
#define SHIP_BATTERY_POS2	(D3DXVECTOR3(-150.0f,400.0f,0.0f))	// �C��̈ʒu2
#define SHIP_BATTERY_POS3	(D3DXVECTOR3(280.0f,-20.0f,0.0f))	// �C��̈ʒu3
#define SHIP_BATTERY_POS4	(D3DXVECTOR3(-280.0f,-20.0f,0.0f))	// �C��̈ʒu4
#define SHIP_BATTERY_POS5	(D3DXVECTOR3(-280.0f,-550.0f,0.0f))	// �C��̈ʒu5
#define SHIP_BATTERY_POS6	(D3DXVECTOR3(280.0f,-550.0f,0.0f))	// �C��̈ʒu6
//******************************************************************************
// �N���X
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
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�@�e�N�X�`�����
};
#endif