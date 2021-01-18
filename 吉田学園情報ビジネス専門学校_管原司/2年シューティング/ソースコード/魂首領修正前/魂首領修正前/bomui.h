//---------------------------------------------------
//	bomui
// bom.h
// Authur:	�ǌ��i
//---------------------------------------------------

//---------------------------------------------------
//�}�N����`
//---------------------------------------------------
#ifndef _BOM_H_
#define _BOM_H_
#define MAX_BOM 5
#define BOM_SIZE_X 40
#define BOM_SIZE_Y 40
//---------------------------------------------------
//�O���錾
//---------------------------------------------------
class CScene2d;
//---------------------------------------------------
//�N���X
//---------------------------------------------------
class CBom : public CScene
{
public:
	CBom(int nPriority = CScene::PRIORITY_TYPE_UI);
	~CBom();
	static CBom * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetBomUI(int mBomPossesion);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`�����
	CScene2d * m_apScene2D[MAX_BOM];		//���C�t�̏��
	D3DXVECTOR3 m_pos;		//�ʒu���W
	int m_nBom_Posession;	//�{���̏�����
};
#endif