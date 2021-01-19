//******************************************************************************
// �^�C�g�� [title.h]
// Author : �ǌ� �i
//******************************************************************************
#ifndef _TITLE_H_
#define _TITLE_H_
//******************************************************************************
// �}�N����`
//******************************************************************************
#define TITLE_WAIT_COUNT	(10)	// �^�C�g���J�E���g
#define MAX_TITLE_TEX		(2)		// �^�C�g���e�N�X�`��
#define MAX_TITLE			(2)		// �^�C�g���ő吔
//******************************************************************************
// �N���X
//******************************************************************************
class CTitle : public CScene
{
public:
	
	CTitle(int nPriority = 10);
	~CTitle();
	static HRESULT Load(void);
	static void Unload(void);
	static CTitle * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_TITLE_TEX];	// �e�N�X�`��
	CScene2d * m_apScene2D[MAX_TITLE];						// �^�C�g���̏��
	D3DXVECTOR3 m_pos;										// �ʒu���W
	D3DXVECTOR3 m_size;										// �T�C�Y
	D3DXCOLOR m_color;										// �J���[
	bool m_bColor;											// �J���[�p��bool�ϐ�
	bool m_bfade;											// �t�F�[�h�p��bool�ϐ�
};
#endif