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
#include "normal_enemy.h"
#include "player.h"
#include "normal_bullet.h"
#include "player_beam.h"
#include "boss.h"
#include "score.h"
//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
bool CPlayer_Beam::m_bUseBeam = true;
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CPlayer_Beam::CPlayer_Beam(int nPriority) : CBullet(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bUseBeam = true;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CPlayer_Beam::~CPlayer_Beam()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CPlayer_Beam * CPlayer_Beam::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DCOLOR col, CBullet::TEX_TYPE textype)
{
	// CNormal_Bullet�|�C���^
	CPlayer_Beam * pPlayer_Beam;

	// �������m��
	pPlayer_Beam = new CPlayer_Beam;

	// �e�̏��ݒ�
	pPlayer_Beam->SetBullet(pos, rot, size, col, textype, CScene::OBJTYPE_PLAYER_BULLET);

	// �ړ��ʑ��
	pPlayer_Beam->m_move = move;

	// ������
	pPlayer_Beam->Init();

	// �|�C���^��Ԃ�
	return pPlayer_Beam;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CPlayer_Beam::Init(void)
{
	// ������
	CBullet::Init();

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CPlayer_Beam::Uninit(void)
{
	// �I��
	CBullet::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CPlayer_Beam::Update(void)
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

	// x���W���v���C���[�ɍ��킹��
	pos.x = pPlayer->GetPosition().x;

	// �q�b�g����
	HitEnemy();

	// false�̏ꍇ
	if (m_bUseBeam == false)
	{
		// �I��
		Uninit();
		return;
	}

	//�ʒu�X�V
	pos.x += m_move.x;
	pos.y += m_move.y;

	// �ʒu���W�ݒ�
	SetPosition(pos);
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CPlayer_Beam::Draw(void)
{
	// �`��
	CBullet::Draw();
}
//******************************************************************************
// �r�[���g�p��Ԑݒ�
//******************************************************************************
void CPlayer_Beam::SetUseBeam(bool bUseBeam)
{
	m_bUseBeam = bUseBeam;
}
//******************************************************************************
// �q�b�g���菈��
//******************************************************************************
void CPlayer_Beam::HitEnemy(void)
{
	//�Q�[���擾
	CGame * pGame = CSceneManager::GetGame();

	//�v���C���[�̎擾
	CPlayer * pPlayer = CGame::GetPlayer();

	// �{�X�擾
	CBoss * pBoss = CGame::GetBoss();

	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	// �X�R�A�̎擾
	CScore * pScore = CGame::GetScore();

	// CScene�^�̃|�C���^
	CScene *pScene = NULL;

	// �G�̓����蔻��
	do
	{
		// �I�u�W�F�^�C�v���G�̏ꍇ
		pScene = GetScene(OBJTYPE_ENEMY);
		if (pScene != NULL)
		{
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_ENEMY)
			{
				// ���W�ƃT�C�Y�擾
				D3DXVECTOR3 EnemyPos = ((CEnemy*)pScene)->GetPosition();
				D3DXVECTOR3 EnemySize = ((CEnemy*)pScene)->GetSize();

				// �����蔻��
				if (Collision(pos, EnemyPos, size, EnemySize) == true)
				{
					// �G�Ƀ_���[�W��^����
					((CEnemy*)pScene)->HitEnemy(10);
					// �X�R�A���Z
					pScore->AddScore(100);
					// �e������
					Uninit();
					return;
				}
			}
		}
	} while (pScene != NULL);

	// �{�X�̈ʒu���W�ƃT�C�Y�擾
	D3DXVECTOR3 BossPos = pBoss->GetPosition();
	D3DXVECTOR3 BossSize = pBoss->GetSize();

	// �����蔻��
	if (Collision(pos, BossPos, size, BossPos) == true)
	{
		// �{�X�Ƀ_���[�W��^����
		pBoss->HitBoss(20);
		// �X�R�A���Z
		pScore->AddScore(100);
		// �e������
		Uninit();
		return;
	}
}