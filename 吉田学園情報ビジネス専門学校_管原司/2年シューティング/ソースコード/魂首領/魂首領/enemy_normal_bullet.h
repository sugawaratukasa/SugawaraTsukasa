//******************************************************************************
// �G�̒e [enemy_normal_bullet.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _ENEMY_NORMAL_BULLET_H_
#define _ENEMY_NORMAL_BULLET_H_
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "bullet.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define ENEMY_NORMAL_BULLET_SIZE (D3DXVECTOR3(20.0f,20.0f,0.0f))	// �e�̃T�C�Y
//******************************************************************************
// �N���X
//******************************************************************************
class CEnemy_Normal_Bullet : public CBullet
{
public:

	CEnemy_Normal_Bullet(int nPriority = OBJTYPE_ENEMY_BULLET);
	~CEnemy_Normal_Bullet();
	static CEnemy_Normal_Bullet * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DCOLOR col, CBullet::TEX_TYPE textype);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void HitPlayer(void);
	D3DXVECTOR3 m_move;
};
#endif