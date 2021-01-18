//******************************************************************************
// �G�̒e [enemy_diffusionl_bullet.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _ENEMY_DIFFUSIONL_BULLET_H_
#define _ENEMY_DIFFUSIONL_BULLET_H_
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "bullet.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define FIFFUSION_BULLET_SIZE	(D3DXVECTOR3(100.0f,100.0f,0.0f))	// �e�̃T�C�Y
//******************************************************************************
// �N���X
//******************************************************************************
class CEnemy_Diffusion_Bullet : public CBullet
{
public:

	CEnemy_Diffusion_Bullet(int nPriority = 10);
	~CEnemy_Diffusion_Bullet();
	static CEnemy_Diffusion_Bullet * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DCOLOR col, CBullet::TEX_TYPE textype);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	D3DXVECTOR3 m_move;	// �ړ�
	int m_nDifCount;	// �J�E���g
	
};
#endif