//---------------------------------------------------
// Bullet
// Bullet.h
// Authur:	�ǌ��i
//---------------------------------------------------
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_
//---------------------------------------------------
//�}�N����`
//---------------------------------------------------
#define EXPLOSION_SIZE_X 50
#define EXPLOSION_SIZE_Y 50
//---------------------------------------------------
//�N���X
//---------------------------------------------------
class CExplosion : public CScene2d
{
public:
	CExplosion(int nPriority = PRIORITY_TYPE_EXPLOSION);
	~CExplosion();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CExplosion * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
	static HRESULT Load(void);
	static void Unload(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//texture
	int m_nCountAnim; //�J�E���^�[
	int m_nPatternAnim;	//�p�^�[��
	bool m_bUse;	//�g�p���
};
#endif