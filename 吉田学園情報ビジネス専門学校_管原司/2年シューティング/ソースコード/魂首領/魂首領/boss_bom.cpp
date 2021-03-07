//******************************************************************************
// �{�X��p�̃{�� [boss_bom.h]
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
#include "player.h"
#include "enemy.h"
#include "normal_enemy.h"
#include "circle_bullet_enemy.h"
#include "bom.h"
#include "boss_bom.h"
#include "boss.h"
#include "boss_left.h"
#include "boss_right.h"
#include "score.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define COLOR				(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	// �F
#define ADD_SCORE			(100)								// ���Z�X�R�A
#define BOSS_MAIN_DAMAGE	(20)								// �{�X�ɒ��S�ɗ^����_���[�W
#define BOSS_DAMAGE			(10)								// �{�X�ɗ^����_���[�W
//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
bool CBoss_Bom::m_bUseBoss_Bom = true;
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CBoss_Bom::CBoss_Bom(int nPriority) : CBullet(nPriority)
{
	m_move			= INIT_D3DXVECTOR3;
	m_bUseBoss_Bom	= true;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CBoss_Bom::~CBoss_Bom()
{
}
//******************************************************************************
// �������֐�
//******************************************************************************
CBoss_Bom * CBoss_Bom::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXVECTOR3 move, CBullet::TEX_TYPE textype)
{
	// CNormal_Bullet�|�C���^
	CBoss_Bom * pBoss_Bom;

	// �������m��
	pBoss_Bom = new CBoss_Bom;

	// �e�̏��ݒ�
	pBoss_Bom->SetBullet(pos, rot, size, COLOR, textype, CScene::OBJTYPE_PLAYER_BULLET);

	// �ړ��ʑ��
	pBoss_Bom->m_move = move;

	// ������
	pBoss_Bom->Init();

	// �|�C���^��Ԃ�
	return pBoss_Bom;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CBoss_Bom::Init(void)
{
	// ������
	CBullet::Init();

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CBoss_Bom::Uninit(void)
{
	// �I��
	CBullet::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CBoss_Bom::Update(void)
{
	// �X�V
	CBullet::Update();;

	//�v���C���[�̎擾
	CPlayer * pPlayer = CGame::GetPlayer();

	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	// x���W���v���C���[�ɍ��킹��
	pos.x = pPlayer->GetPosition().x;

	// �q�b�g����
	HitBoss();

	// false�̏ꍇ
	if (m_bUseBoss_Bom == false)
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
void CBoss_Bom::Draw(void)
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
// �g�p��Ԑݒ�
//******************************************************************************
void CBoss_Bom::SetUseBoss_Bom(bool bUseBoss_Bom)
{
	m_bUseBoss_Bom = bUseBoss_Bom;
}
//******************************************************************************
// �{�X�̃q�b�g���菈��
//******************************************************************************
void CBoss_Bom::HitBoss(void)
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

	// �{�X�̈ʒu���W�ƃT�C�Y�擾
	D3DXVECTOR3 BossPos = pBoss->GetPosition();
	D3DXVECTOR3 BossSize = pBoss->GetSize();

	// CScene�^�̃|�C���^
	CScene *pScene = NULL;

	// �G�̒e�̔���
	do
	{
		// �I�u�W�F�^�C�v���G�̏ꍇ
		pScene = GetScene(OBJTYPE_ENEMY_BULLET);

		// NULL�`�F�b�N
		if (pScene != NULL)
		{
			// �I�u�W�F�^�C�v�擾
			OBJTYPE objType = pScene->GetObjType();
			// �I�u�W�F�N�g�^�C�v���G
			if (objType == OBJTYPE_ENEMY_BULLET)
			{
				// ���W�ƃT�C�Y�擾
				D3DXVECTOR3 Enemy_Bullet_Pos = ((CBullet*)pScene)->GetPosition();
				D3DXVECTOR3 Enemy_Bullet_Size = ((CBullet*)pScene)->GetSize();

				// �����蔻��
				if (Collision(pos, Enemy_Bullet_Pos, size, Enemy_Bullet_Size) == true)
				{
					// �G�Ƀ_���[�W��^����
					((CBullet*)pScene)->Uninit();
					//�X�R�A���Z
					pScore->AddScore(ADD_SCORE);
				}
			}
		}
	} while (pScene != NULL);

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
				D3DXVECTOR3 BossSize = ((CBoss*)pScene)->GetCollision_Size();

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