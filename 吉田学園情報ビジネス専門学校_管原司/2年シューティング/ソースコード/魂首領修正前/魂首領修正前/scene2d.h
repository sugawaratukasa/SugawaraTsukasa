//---------------------------------------------------
// Create
// scene2d.h
// Authur:	�ǌ��i
//---------------------------------------------------
#ifndef _SCENE2D_H_
#define _SCENE2D_H_
#include "d3dx9.h"
//---------------------------------------------------
//�}�N����`
//---------------------------------------------------
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE| D3DFVF_TEX1)
#define NUM_VERTEX	4

#define NUM_POLYGON 2
//---------------------------------------------------
//�\���̐錾
//---------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;//���_���W
	float rhw;//���W�ϊ��p���W��
	D3DCOLOR col;//���_�J���[
	D3DXVECTOR2 tex;//�e�N�X�`��
}VERTEX_2D;
//---------------------------------------------------
//�N���X
//---------------------------------------------------
class CScene2d : public CScene
{
public:
	CScene2d(int nPriority = 3);
	~CScene2d();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 pos);
	void SetTexture(float fTexX, float fTexY, float fTexAnimX , float fTexAnimY);
	void SetRGBA(D3DXCOLOR col);
	void SetRot(D3DXVECTOR3 rot);
	void SetScale(float fScale);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	static CScene2d * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
private:
	LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//�o�b�t�@
	D3DXVECTOR3 m_pos;	//�ʒu���W
	D3DXVECTOR3 m_rot; //����
	D3DXCOLOR m_col;	//�J���[
	int m_nsizeX;	//�T�C�YX
	int m_nsizeY;	//�T�C�YY
	float m_fAngle;	//�p�x
	float m_fLength;	//�Ίp��
	float m_fTexX;	//�e�N�X�`��X
	float m_fTexY;	//�e�N�X�`��Y
	float m_fTexAnimX;	//�e�N�X�`���A�j���[�V����
	float m_fTexAnimY;	//�e�N�X�`���A�j���[�V����
	float m_fScale;		//�g��
	int m_nCount;	//
};
#endif