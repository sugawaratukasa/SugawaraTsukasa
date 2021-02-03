//******************************************************************************
// ���U���g [result.h]
// Author : �ǌ� �i
//******************************************************************************
#ifndef _RESULT_H_
#define _RESULT_H_
//******************************************************************************
// �O���錾
//******************************************************************************
class CScene2d;
class CPlayerdata;
//******************************************************************************
// �N���X
//******************************************************************************
class CResult : public CScene
{
public:
	CResult(int nPriority = 10);
	~CResult();
	static CResult * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CPlayerdata * GetPlayerData(void) { return m_pPlayerData; }
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	// �e�N�X�`���̏��
	static CPlayerdata * m_pPlayerData;		// �v���C���[�f�[�^
	CScene2d * m_pScene2D;					// Result�̏��
	D3DXVECTOR3 m_pos;						// �ʒu���W
	D3DXVECTOR3 m_size;						// �T�C�Y
	bool m_bfade;							// �t�F�[�h�p��bool�ϐ�
};
#endif