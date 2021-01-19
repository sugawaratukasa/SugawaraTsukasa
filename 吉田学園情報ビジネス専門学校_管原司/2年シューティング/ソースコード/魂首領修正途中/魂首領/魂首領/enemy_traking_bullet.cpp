//******************************************************************************
// �_�������e [enemy_traking_bullet.h]
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
#include "game.h"
#include "bullet.h"
#include "enemy.h"
#include "player.h"
#include "enemy_traking_bullet.h"
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CEnemy_Traking_Bullet::CEnemy_Traking_Bullet(int nPriority) : CBullet(nPriority)
{
	m_move = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_fAngle = 0.0f;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CEnemy_Traking_Bullet::~CEnemy_Traking_Bullet()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CEnemy_Traking_Bullet * CEnemy_Traking_Bullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DCOLOR col, CBullet::TEX_TYPE textype)
{
	// CNormal_Bullet�|�C���^
	CEnemy_Traking_Bullet * pEnemy_Traking_Bullet;

	// �������m��
	pEnemy_Traking_Bullet = new CEnemy_Traking_Bullet;

	// �e�̏��ݒ�
	pEnemy_Traking_Bullet->SetBullet(pos, rot, size, col, textype, CScene::OBJTYPE_ENEMY_BULLET);

	// �ړ��ʑ��
	pEnemy_Traking_Bullet->m_move = move;

	// ������
	pEnemy_Traking_Bullet->Init();

	// �|�C���^��Ԃ�
	return pEnemy_Traking_Bullet;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CEnemy_Traking_Bullet::Init(void)
{
	// ������
	CBullet::Init();

	//�Q�[���擾
	CGame * pGame = CSceneManager::GetGame();

	//�v���C���[�̎擾
	CPlayer * pPlayer = CGame::GetPlayer();
	
	// �v���C���[�̈ʒu���W�擾
	D3DXVECTOR3 PlayerPos = pPlayer->GetPosition();

	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	m_fAngle = atan2f(PlayerPos.y - pos.y, PlayerPos.x - pos.x);

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CEnemy_Traking_Bullet::Uninit(void)
{
	// �I��
	CBullet::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CEnemy_Traking_Bullet::Update(void)
{
	// �X�V
	CBullet::Update();

	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	// �q�b�g��������
	HitPlayer();

	// �p�x���
	float fRad = m_fAngle;

	// �ʒu�X�V
	pos.x += m_move.x * cosf(fRad);
	pos.y += m_move.y * sinf(fRad);

	// �ʒu���W�ݒ�
	SetPosition(pos);
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CEnemy_Traking_Bullet::Draw(void)
{
	// �`��
	CBullet::Draw();
}
//******************************************************************************
// �q�b�g�����֐�
//******************************************************************************
void CEnemy_Traking_Bullet::HitPlayer(void)
{
	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	//�Q�[���擾
	CGame * pGame = CSceneManager::GetGame();

	//�v���C���[�̎擾
	CPlayer * pPlayer = CGame::GetPlayer();

	// �v���C���[�̈ʒu���W�擾
	D3DXVECTOR3 PlayerPos = pPlayer->GetPosition();

	// �v���C���[�̃T�C�Y�擾
	D3DXVECTOR3 PlayerSize = pPlayer->GetCollisionSize();

	// �����蔻��
	if (Collision(pos, PlayerPos, size, PlayerSize) == true)
	{
		// �v���C���[�Ƀ_���[�W��^����
		pPlayer->HitPlayer();

		// �e������
		Uninit();
		return;
	}
}