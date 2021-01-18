//---------------------------------------------------
// BG
// bg.h
// Authur:	�ǌ��i
//---------------------------------------------------
#ifndef _BG_H_
#define _BG_H_
//---------------------------------------------------
//�}�N����`
//---------------------------------------------------
#define MAX_BG 3
//---------------------------------------------------
//�N���X
//---------------------------------------------------
class CBg : public CScene
{
public:
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_FARST_BG,
		TYPE_SECOUND_BG,
		TYPE_THIRD_BG,
		TYPE_MAX
	}TYPE;
	CBg(int nPriority = PRIORITY_TYPE_BG);
	~CBg();
	static HRESULT Load(void);
	static void Unload(void);
	static CBg * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BG];	//�e�N�X�`�����
	CScene2d * m_apScene2D[MAX_BG];	//BG�̏��
	TYPE m_type;				//�^�C�v
	D3DXVECTOR3 m_Farstpos;		//�ʒu
	D3DXVECTOR3 m_Secoundpos;	//�ʒu
	D3DXVECTOR3 m_Thirdpos;		//�ʒu
	D3DXVECTOR3 m_move;			//�ړ�
	float m_texsizeX;			//�e�N�X�`��X
	float m_texsizeY;			//�e�N�X�`��Y
	float m_fFastMove;			//����
	float m_fSlowMove;			//�x��
	float m_fmove;				//�ړ�
};
#endif
