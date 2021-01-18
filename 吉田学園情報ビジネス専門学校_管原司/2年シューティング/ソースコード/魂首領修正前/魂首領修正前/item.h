//---------------------------------------------------
// Item
// item.h
// Authur:	�ǌ��i
//---------------------------------------------------
#ifndef _ITEM_H_
#define _ITEM_H_
//---------------------------------------------------
//�}�N��
//----------------------------------------------------
#define MAX_ITEM_TEX 3
#define STAR_SIZE_X 40
#define STAR_SIZE_Y 40
#define BOM_SIZE_X 40
#define BOM_SIZE_Y 40
#define POWER_SIZE_X 40
#define POWER_SIZE_Y 40
#define ITEM_SIZE_X 40
#define ITEM_SIZE_Y 40
//-----------------------------------------------------
//�N���X
//-----------------------------------------------------
class CItem : public CScene2d
{
public:
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_STAR,
		TYPE_BOM,
		TYPE_POWER,
		TYPE_MAX
	}TYPE;
	CItem(int nPriority = PRIORITY_TYPE_ITEM);
	~CItem();
	static CItem * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, int sizeX, int sizeY , TYPE type);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, int sizeX, int sizeY , TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_ITEM_TEX];	//texture�̏��
	TYPE m_type;											//�^�C�v
	D3DXVECTOR3 m_move;										//�ړ�
	bool m_bMove;											//move
};
#endif