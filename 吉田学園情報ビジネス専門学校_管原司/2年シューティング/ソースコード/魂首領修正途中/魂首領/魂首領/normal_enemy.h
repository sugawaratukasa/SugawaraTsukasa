//******************************************************************************
// �ʏ�̓G [normal_enemy.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _NORMAL_ENEMY_H_
#define _NORMAL_ENEMY_H_
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "enemy.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define NORMAL_ENEMY_SIZE	(D3DXVECTOR3(50.0f,50.0f,0.0f))	// �ʏ�̓G�T�C�Y
#define NORMAL_ENEMY_LIFE	(20)							// �ʏ�̓G�̃��C�t
//******************************************************************************
// �N���X
//******************************************************************************
class CNormal_Enemy : public CEnemy
{
public:

	CNormal_Enemy(int nPriority = OBJTYPE_ENEMY);
	~CNormal_Enemy();
	static CNormal_Enemy * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nLife, TEX_TYPE tex_type);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void Attack(void);
	int m_nAttackCount;	// �U���J�E���g
};
#endif