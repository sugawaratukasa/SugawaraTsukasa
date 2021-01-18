//******************************************************************************
// �g�U�e [enemy_diffudion_bullet.cpp]
// Author : �ǌ��@�i
//******************************************************************************
//******************************************************************************
// �t�@�C���C���N���[�h
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "game.h"
#include "bullet.h"
#include "enemy_normal_bullet.h"
#include "enemy_diffusion_bullet.h"
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CEnemy_Diffusion_Bullet::CEnemy_Diffusion_Bullet(int nPriority)
{
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CEnemy_Diffusion_Bullet::~CEnemy_Diffusion_Bullet()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CEnemy_Diffusion_Bullet * CEnemy_Diffusion_Bullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DCOLOR col, CBullet::TEX_TYPE textype)
{
	// CNormal_Bullet�|�C���^
	CEnemy_Diffusion_Bullet * pEnemy_Diffusion_Bullet;

	// �������m��
	pEnemy_Diffusion_Bullet = new CEnemy_Diffusion_Bullet;

	// �e�̏��ݒ�
	pEnemy_Diffusion_Bullet->SetBullet(pos, rot, size, col, textype, CScene::OBJTYPE_ENEMY_BULLET);

	// �ړ��ʑ��
	pEnemy_Diffusion_Bullet->m_move = move;

	// ������
	pEnemy_Diffusion_Bullet->Init();

	// �|�C���^��Ԃ�
	return pEnemy_Diffusion_Bullet;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CEnemy_Diffusion_Bullet::Init(void)
{
	// ������
	CBullet::Init();

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CEnemy_Diffusion_Bullet::Uninit(void)
{
	// �I��
	CBullet::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CEnemy_Diffusion_Bullet::Update(void)
{
	// �X�V
	CBullet::Update();

	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �C���N�������g
	m_nDifCount++;

	// �J�E���g80�ȏ�̏ꍇ
	if (m_nDifCount >= 80)
	{
		// 20��J��Ԃ�
		for (int nCount = 0; nCount < 20; nCount++)
		{
			// �~�`�e����
			CEnemy_Normal_Bullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z),
				D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)),
				D3DXVECTOR3(cosf(D3DXToRadian(nCount * (360 / 20)))*5.0f, sinf(D3DXToRadian(nCount * (360 / 20)))*5.0f, 0.0f),
				ENEMY_NORMAL_BULLET_SIZE,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				CBullet::TEX_TYPE_ENEMY_NORMAL);
		}

		//�I��
		Uninit();
		return;
	}

	// �ړ�
	pos.x += m_move.x;
	pos.y += m_move.y;

	// �ʒu���W�X�V
	SetPosition(pos);
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CEnemy_Diffusion_Bullet::Draw(void)
{
	// �`��
	CBullet::Draw();
}