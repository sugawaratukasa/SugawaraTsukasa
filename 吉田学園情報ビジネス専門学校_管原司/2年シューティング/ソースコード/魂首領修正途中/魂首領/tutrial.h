//******************************************************************************
// �`���[�g���A�� [tutrial.h]
// Author : �ǌ� �i
//******************************************************************************
#ifndef _TUTRIAL_H_
#define _TUTRIAL_H_
//******************************************************************************
// �N���X
//******************************************************************************
class CTutrial : public CScene2d
{
public:
	static CTutrial * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	static HRESULT Load(void);
	static void Unload(void);
	CTutrial(int nPriority = 10);
	~CTutrial();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	// �e�N�X�`��
	bool m_bfade;							// �t�F�[�h
};
#endif