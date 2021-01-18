//******************************************************************************
// �~�`�̒e���o���G [circle_bullet_enemy.cpp]
// Author : �ǌ��@�i
//******************************************************************************

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
#include "enemy_normal_bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "game.h"
#include "item.h"
#include "circle_bullet_enemy.h"
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CCirecle_Bullet_Enemy::CCirecle_Bullet_Enemy(int nPriority)
{
	m_nAttackCount = 0;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CCirecle_Bullet_Enemy::~CCirecle_Bullet_Enemy()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CCirecle_Bullet_Enemy * CCirecle_Bullet_Enemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nLife, TEX_TYPE tex_type, DROP_ITEM drop_item)
{
	// CNormal_Enemy�N���X�̃|�C���^
	CCirecle_Bullet_Enemy * pCirecle_Bullet_Enemy;

	// �������m��
	pCirecle_Bullet_Enemy = new CCirecle_Bullet_Enemy;

	// �G�̏��ݒ�
	pCirecle_Bullet_Enemy->SetEnemy(pos, rot, size, nLife, tex_type, CScene::OBJTYPE_ENEMY);

	// ���Ƃ��A�C�e���ݒ�
	pCirecle_Bullet_Enemy->m_DropItem = drop_item;

	// ������
	pCirecle_Bullet_Enemy->Init();

	// �|�C���^��Ԃ�
	return pCirecle_Bullet_Enemy;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CCirecle_Bullet_Enemy::Init(void)
{
	// ������
	CEnemy::Init();
	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CCirecle_Bullet_Enemy::Uninit(void)
{
	// �I��
	CEnemy::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CCirecle_Bullet_Enemy::Update(void)
{
	// �X�V
	CEnemy::Update();

	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �ړ���
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 2.0f, 0.0f);

	// ��Ԏ擾
	int nState = CEnemy::GetState();

	// �C���N�������g
	m_nAttackCount++;

	// �J�E���g����100�̏ꍇ
	if (m_nAttackCount == 100)
	{
		// 20��J��Ԃ�
		for (int nCount = 0; nCount < 20; nCount++)
		{
			CEnemy_Normal_Bullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)), ENEMY_NORMAL_BULLET_SIZE, D3DXVECTOR3(cosf(D3DXToRadian(nCount * (360 / 20)))*5.0f, sinf(D3DXToRadian(nCount * (360 / 20)))*5.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CBullet::TEX_TYPE_ENEMY_NORMAL);
		}
		// �J�E���g����0�ɂ���
		m_nAttackCount = 0;
	}

	// ���S��ԂȂ�
	if (nState == STATE_DEATH)
	{
		if (m_DropItem == DROP_ITEM_POWERUP)
		{

		}
		if (m_DropItem == DROP_ITEM_BOM)
		{

		}
	}
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CCirecle_Bullet_Enemy::Draw(void)
{
	// �`��
	CEnemy::Draw();
}