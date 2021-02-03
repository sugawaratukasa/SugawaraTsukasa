//******************************************************************************
// �e [normal_bullet.cpp]
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
#include "normal_enemy.h"
#include "player.h"
#include "normal_bullet.h"
#include "player_beam.h"
#include "boss.h"
#include "boss_left.h"
#include "boss_right.h"
#include "score.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define DEATH_COUNT			(15)	// ���S�J�E���g
#define ENEMY_DAMAGE		(5)		// �G�ɗ^����_���[�W
#define BOSS_MAIN_DAMAGE	(10)	// �{�X�̒��S�^����_���[�W
#define BOSS_DAMAGE			(5)		// �{�X�ɗ^����_���[�W
#define ADD_SCORE			(100)	// �X�R�A���Z�l
//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
bool CPlayer_Beam::m_bUseBeam = true;
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CPlayer_Beam::CPlayer_Beam(int nPriority) : CBullet(nPriority)
{
	m_move			= INIT_D3DXVECTOR3;
	m_nDeathCount	= INIT_INT;
	m_bHit			= false;
	m_bUseBeam		= true;
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
	if (m_bHit == true)
	{
		// �C���N�������g
		m_nDeathCount++;
		// �J�E���g��15�̎�
		if (m_nDeathCount == DEATH_COUNT)
		{
			// �I��
			Uninit();
			return;
		}
	}
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
	// �����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();

	// ���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �`��
	CBullet::Draw();

	// ���ɖ߂�
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
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

	// false�̏ꍇ
	if (m_bHit == false)
	{
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
						((CEnemy*)pScene)->HitEnemy(ENEMY_DAMAGE);

						// �X�R�A���Z
						pScore->AddScore(ADD_SCORE);

						// true��
						m_bHit = true;
					}
				}
			}
		} while (pScene != NULL);
	}
	// �{�X�̓����蔻��
	do
	{
		// �I�u�W�F�^�C�v���G�̏ꍇ
		pScene = GetScene(OBJTYPE_BOSS);
		if (pScene != NULL)
		{
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_BOSS)
			{
				// ���W�ƃT�C�Y�擾
				D3DXVECTOR3 BossPos = ((CBoss*)pScene)->GetPosition();
				D3DXVECTOR3 BossSize = ((CBoss*)pScene)->GetSize();

				// �����蔻��
				if (Collision(pos, BossPos, size, BossSize) == true)
				{
					// �G�Ƀ_���[�W��^����
					((CBoss*)pScene)->HitBoss(BOSS_MAIN_DAMAGE);

					// �X�R�A���Z
					pScore->AddScore(ADD_SCORE);

					// �e������
					Uninit();
					return;
				}
			}
		}
	} while (pScene != NULL);

	// �{�X�̓����蔻��
	do
	{
		// �I�u�W�F�^�C�v���G�̏ꍇ
		pScene = GetScene(OBJTYPE_BOSS_RIGHT);
		if (pScene != NULL)
		{
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_BOSS_RIGHT)
			{
				// ���W�ƃT�C�Y�擾
				D3DXVECTOR3 BossRightPos = ((CBoss_Right*)pScene)->GetPosition();
				D3DXVECTOR3 BossRightSize = ((CBoss_Right*)pScene)->GetSize();

				// �����蔻��
				if (Collision(pos, BossRightPos, size, BossRightSize) == true)
				{
					// �G�Ƀ_���[�W��^����
					((CBoss_Right*)pScene)->Hit(BOSS_DAMAGE);

					// �X�R�A���Z
					pScore->AddScore(ADD_SCORE);

					// �e������
					Uninit();
					return;
				}
			}
		}
	} while (pScene != NULL);

	// �{�X�̓����蔻��
	do
	{
		// �I�u�W�F�^�C�v���G�̏ꍇ
		pScene = GetScene(OBJTYPE_BOSS_LEFT);
		if (pScene != NULL)
		{
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_BOSS_LEFT)
			{
				// ���W�ƃT�C�Y�擾
				D3DXVECTOR3 BossLeftPos = ((CBoss_Left*)pScene)->GetPosition();
				D3DXVECTOR3 BossLeftSize = ((CBoss_Left*)pScene)->GetSize();

				// �����蔻��
				if (Collision(pos, BossLeftPos, size, BossLeftSize) == true)
				{
					// �G�Ƀ_���[�W��^����
					((CBoss_Left*)pScene)->Hit(BOSS_DAMAGE);
					// �X�R�A���Z
					pScore->AddScore(ADD_SCORE);
					// �e������
					Uninit();
					return;
				}
			}
		}
	} while (pScene != NULL);
}