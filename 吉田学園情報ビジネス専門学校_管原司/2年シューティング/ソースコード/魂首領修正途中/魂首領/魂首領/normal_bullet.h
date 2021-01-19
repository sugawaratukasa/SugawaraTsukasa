//******************************************************************************
// �e [bullet.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _NORMAL_BULLET_H_
#define _NORMAL_BULLET_H_
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "bullet.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define BULLET_LEVEL1_SIZE	(D3DXVECTOR3(40.0f,40.0f,0.0f))	// ���x��1�̒e�̃T�C�Y
#define BULLET_LEVEL2_SIZE	(D3DXVECTOR3(50.0f,50.0f,0.0f))	// ���x��2�̒e�̃T�C�Y
#define BULLET_LEVEL3_SIZE	(D3DXVECTOR3(50.0f,50.0f,0.0f))	// ���x��3�̒e�̃T�C�Y
//******************************************************************************
// �N���X
//******************************************************************************
class CNormal_Bullet : public CBullet
{
public:

	CNormal_Bullet(int nPriority = OBJTYPE_PLAYER_BULLET);
	~CNormal_Bullet();
	static CNormal_Bullet * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DCOLOR col, CBullet::TEX_TYPE textype);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void HitEnemy(void);
	D3DXVECTOR3 m_move;
};
#endif