//******************************************************************************
// ���� [explosion.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_
//******************************************************************************
// �}�N����`
//******************************************************************************
#define EXPLOSION_SIZE (D3DXVECTOR3(50.0f,50.0f,0.0f))	// �����T�C�Y
//******************************************************************************
// �N���X
//******************************************************************************
class CExplosion : public CScene2d
{
public:
	CExplosion(int nPriority = 10);
	~CExplosion();
	static HRESULT Load(void);
	static void Unload(void);
	static CExplosion * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	// �e�N�X�`��
	int m_nCountAnim;						// �J�E���^�[
	int m_nPatternAnim;						// �p�^�[��
};
#endif