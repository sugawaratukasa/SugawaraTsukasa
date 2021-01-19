//******************************************************************************
// �ʏ�̓G [normal_enemy.cpp]
// Author : �ǌ��@�i
//******************************************************************************
//******************************************************************************
// �}�N����`
//******************************************************************************
#define BULLET_MOVE_VALUE (D3DXVECTOR3(5.0f,5.0f,0.0f))
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "player.h"
#include "bullet.h"
#include "enemy_traking_bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "game.h"
#include "normal_enemy.h"
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CNormal_Enemy::CNormal_Enemy(int nPriority) : CEnemy(nPriority)
{
	m_nAttackCount = 0;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CNormal_Enemy::~CNormal_Enemy()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CNormal_Enemy * CNormal_Enemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nLife, TEX_TYPE tex_type)
{
	// CNormal_Enemy�N���X�̃|�C���^
	CNormal_Enemy * pNormal_Enemy;

	// �������m��
	pNormal_Enemy = new CNormal_Enemy;

	// �G�̏��ݒ�
	pNormal_Enemy->SetEnemy(pos, rot, size, nLife, tex_type, CScene::OBJTYPE_ENEMY);

	// ������
	pNormal_Enemy->Init();

	// �|�C���^��Ԃ�
	return pNormal_Enemy;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CNormal_Enemy::Init(void)
{
	// ������
	CEnemy::Init();

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CNormal_Enemy::Uninit(void)
{
	// �I��
	CEnemy::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CNormal_Enemy::Update(void)
{
	// �X�V
	CEnemy::Update();

	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �ړ���
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 2.0f, 0.0f);

	// �C���N�������g
	m_nAttackCount++;

	// 60���܂�0�̎�
	if (m_nAttackCount % 60 == 0)
	{
		// �񔭐���
		for (int nCount = 0; nCount < 2; nCount++)
		{
			CEnemy_Traking_Bullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z),
				D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)),
				ENEMY_TRAKING_BULLET_SIZE,
				D3DXVECTOR3(BULLET_MOVE_VALUE.x + nCount, BULLET_MOVE_VALUE.y + nCount, BULLET_MOVE_VALUE.z),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				CBullet::TEX_TYPE_ENEMY_NORMAL);
		}
		// �J�E���g��0�ɂ���
		m_nAttackCount = 0;
	}

	// �ړ�
	pos.y += move.y;

	// �ʒu���W�ݒ�
	SetPosition(pos);
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CNormal_Enemy::Draw(void)
{
	// �`��
	CEnemy::Draw();
}