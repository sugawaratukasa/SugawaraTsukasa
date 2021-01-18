//******************************************************************************
// �e [normal_bullet.cpp]
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
#include "enemy.h"
#include "player.h"
#include "normal_bullet.h"
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CNormal_Bullet::CNormal_Bullet(int nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CNormal_Bullet::~CNormal_Bullet()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CNormal_Bullet * CNormal_Bullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DCOLOR col, CBullet::TEX_TYPE textype)
{
	// CNormal_Bullet�|�C���^
	CNormal_Bullet * pNormalBullet;

	// �������m��
	pNormalBullet = new CNormal_Bullet;

	// �e�̏��ݒ�
	pNormalBullet->SetBullet(pos, rot, size, col, textype, CScene::OBJTYPE_PLAYER_BULLET);

	// �ړ��ʑ��
	pNormalBullet->m_move = move;

	// ������
	pNormalBullet->Init();

	// �|�C���^��Ԃ�
	return pNormalBullet;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CNormal_Bullet::Init(void)
{
	// ������
	CBullet::Init();

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CNormal_Bullet::Uninit(void)
{
	// �I��
	CBullet::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CNormal_Bullet::Update(void)
{
	// �X�V
	CBullet::Update();

	//�Q�[���擾
	CGame * pGame = CSceneManager::GetGame();

	//�v���C���[�̎擾
	CPlayer * pPlayer = CGame::GetPlayer();

	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	//�v���C���[�̏�Ԏ擾
	int nPlayerState = 0;
	nPlayerState = pPlayer->GetPlayerState();

	// CScene�^�̃|�C���^
	CScene *pScene = NULL;
	do
	{
		// �I�u�W�F�^�C�v���G�̏ꍇ
		pScene = GetScene(OBJTYPE_ENEMY);
		if (pScene != NULL)
		{
			OBJTYPE objType = pScene->GetObjType();
			// �I�u�W�F�N�g�^�C�v���G
			if (objType == OBJTYPE_ENEMY)
			{
				// ���W�ƃT�C�Y�擾
				D3DXVECTOR3 EnemyPos = ((CEnemy*)pScene)->GetPosition();
				D3DXVECTOR3 EnemySize = ((CEnemy*)pScene)->GetSize();

				// �����蔻��
				if (Collision(pos, EnemyPos, size, EnemySize) == true)
				{
					// �G�Ƀ_���[�W��^����
					((CEnemy*)pScene)->HitEnemy(20);
					// �e������
					Uninit();
					return;
				}
			}
		}
	} while (pScene != NULL);

	//�ʒu�X�V
	pos.x += m_move.x;
	pos.y += m_move.y;

	// �ʒu���W�ݒ�
	SetPosition(pos);
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CNormal_Bullet::Draw(void)
{
	// �`��
	CBullet::Draw();
}
//******************************************************************************
// �����蔻��
//******************************************************************************
bool CNormal_Bullet::Collision(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 size1, D3DXVECTOR3 size2)
{
	bool bHit = false;  //�����������ǂ���

	D3DXVECTOR3 box1Max = D3DXVECTOR3(size1.x / 2, size1.y, size1.z / 2) + pos1;          //�Ԃ��鑤�̍ő�l
	D3DXVECTOR3 box1Min = D3DXVECTOR3(-size1.x / 2, -size1.y, -size1.z / 2) + pos1;       //�Ԃ��鑤�̍ŏ��l
	D3DXVECTOR3 box2Max = D3DXVECTOR3(size2.x / 2, size2.y / 2, size2.z / 2) + pos2;      //�Ԃ����鑤�̍ő�l
	D3DXVECTOR3 box2Min = D3DXVECTOR3(-size2.x / 2, -size2.y / 2, -size2.z / 2) + pos2;   //�Ԃ����鑤�̍ŏ��l

	if (box1Max.y > box2Min.y&&
		box1Min.y < box2Max.y&&
		box1Max.x > box2Min.x&&
		box1Min.x < box2Max.x)
	{
		bHit = true;
	}

	return bHit;    //�����������ǂ�����Ԃ�
}