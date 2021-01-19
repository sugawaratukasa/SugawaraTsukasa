//******************************************************************************
// �{�X [boss.cpp]
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
#include "bullet.h"
#include "enemy_traking_bullet.h"
#include "enemy_normal_bullet.h"
#include "enemy_diffusion_bullet.h"
#include "explosion.h"
#include "player.h"
#include "game.h"
#include "boss.h"
//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
LPDIRECT3DTEXTURE9 CBoss::m_apTexture[MAX_BOSS] = {};
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CBoss::CBoss(int nPriority) : CScene(nPriority)
{
	memset(m_apScene2D, 0, sizeof(m_apScene2D));
	m_pos					= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rightpos				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Leftpos				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size					= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move					= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife					= 0;
	m_nAttackCount			= 0;
	m_nAttackCount2			= 0;
	m_nDamageCount			= 0;
	m_nSetCount				= 0;
	m_State					= STATE_NONE;
	m_bMove					= false;
}
//******************************************************************************
//�f�X�g���N�^
//******************************************************************************
CBoss::~CBoss()
{
}
//******************************************************************************
// �e�N�X�`���ǂݍ���
//******************************************************************************
HRESULT CBoss::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/BossMain2.png", &m_apTexture[TYPE_MAIN]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/BossRight2.png", &m_apTexture[TYPE_RIGHT]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/BossLeft2.png", &m_apTexture[TYPE_LEFT]);
	return S_OK;
}
//******************************************************************************
// �e�N�X�`���j��
//******************************************************************************
void CBoss::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_BOSS; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}
//******************************************************************************
// �����֐�
//******************************************************************************
CBoss * CBoss::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �{�X�|�C���^
	CBoss * pBoss;

	// �������m��
	pBoss = new CBoss;

	// �ʒu���W���
	pBoss->m_pos = pos;

	// �T�C�Y���
	pBoss->m_size = size;

	// ������
	pBoss->Init();

	// �|�C���^��Ԃ�
	return pBoss;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CBoss::Init()
{
	// �̗�
	m_nLife = BOSS_LIFE;
	// ���
	m_State = STATE_MOVE;

	// �������m��
	m_apScene2D[TYPE_MAIN] = new CScene2d;
	m_apScene2D[TYPE_RIGHT] = new CScene2d;
	m_apScene2D[TYPE_LEFT] = new CScene2d;

	// �ʒu���W�̐ݒ�
	m_apScene2D[TYPE_MAIN]->SetPosition(m_pos);
	m_apScene2D[TYPE_RIGHT]->SetPosition(m_pos);
	m_apScene2D[TYPE_LEFT]->SetPosition(m_pos);

	// �T�C�Y�̐ݒ�
	m_apScene2D[TYPE_MAIN]->SetSize(m_size);
	m_apScene2D[TYPE_RIGHT]->SetSize(m_size);
	m_apScene2D[TYPE_LEFT]->SetSize(m_size);

	// RGBA�̐ݒ�
	m_apScene2D[TYPE_MAIN]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apScene2D[TYPE_RIGHT]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apScene2D[TYPE_LEFT]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// �e�N�X�`���̎󂯓n��
	m_apScene2D[TYPE_MAIN]->BindTexture(m_apTexture[TYPE_MAIN]);
	m_apScene2D[TYPE_RIGHT]->BindTexture(m_apTexture[TYPE_RIGHT]);
	m_apScene2D[TYPE_LEFT]->BindTexture(m_apTexture[TYPE_LEFT]);
	
	// �I�u�W�F�N�g�^�C�v�̐ݒ�
	m_apScene2D[TYPE_MAIN]->SetObjType(OBJTYPE_BOSS);
	m_apScene2D[TYPE_RIGHT]->SetObjType(OBJTYPE_BOSS);
	m_apScene2D[TYPE_LEFT]->SetObjType(OBJTYPE_BOSS);

	// ������
	m_apScene2D[TYPE_MAIN]->Init();
	m_apScene2D[TYPE_RIGHT]->Init();
	m_apScene2D[TYPE_LEFT]->Init();
	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CBoss::Uninit(void)
{
	//�I��
	Release();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CBoss::Update(void)
{
	if (m_nSetCount == 1)
	{
		// �X�V
		m_apScene2D[TYPE_MAIN]->Update();
		m_apScene2D[TYPE_RIGHT]->Update();
		m_apScene2D[TYPE_LEFT]->Update();

		// �{�X�̒��S
		m_pos = m_apScene2D[TYPE_MAIN]->GetPosition();
		// �{�X�̉E
		m_Rightpos = m_apScene2D[TYPE_RIGHT]->GetPosition();
		// �{�X�̍�
		m_Leftpos = m_apScene2D[TYPE_LEFT]->GetPosition();

		// ��ԏ���
		State();

		// �ʒu�X�V
		m_pos.x += m_move.x;
		m_pos.y += m_move.y;

		// ���W�ݒ�
		m_apScene2D[TYPE_MAIN]->SetPosition(m_pos);
		m_apScene2D[TYPE_RIGHT]->SetPosition(D3DXVECTOR3(m_pos.x + BOSS_RIGHT_SIZE.x, m_pos.y, m_pos.z));
		m_apScene2D[TYPE_LEFT]->SetPosition(D3DXVECTOR3(m_pos.x - BOSS_LEFT_SIZE.x, m_pos.y, m_pos.z));

	}
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CBoss::Draw(void)
{
}
//******************************************************************************
// �q�b�g����
//******************************************************************************
void CBoss::HitBoss(int nDamage)
{
	if (m_State != STATE_MOVE)
	{
		// �̗͌��Z
		m_nLife -= nDamage;
		// State��Damage��
		m_State = STATE_DAMAGE;
	}
}
//******************************************************************************
// �{�X�X�V�J�n
//******************************************************************************
void CBoss::SetBoss(int nSetCount)
{
	m_nSetCount = nSetCount;
}
//******************************************************************************
// �U�������֐�
//******************************************************************************
void CBoss::Attack(void)
{

	// �v���C���[�擾
	CPlayer * pPlayer = CGame::GetPlayer();

	// �v���C���[��bom���{�X��p�ɕύX
	pPlayer->SetBossBom(true);

	// ���C�t�������ȏ�̏ꍇ
	if (m_nLife >= BOSS_LIFE / 2)
	{
		// �C���N�������g
		m_nAttackCount++;

		// 60���܂�0�̏ꍇ
		if (m_nAttackCount % 60 == 0)
		{
			// ���E2���e����
			for (int nCount = 0; nCount < 2; nCount++)
			{
				// �E
				CEnemy_Normal_Bullet::Create(D3DXVECTOR3(m_Rightpos.x + BOSS_RIGHT_SIZE.x / 2, m_Rightpos.y + BOSS_RIGHT_SIZE.y / 2, m_Rightpos.z),
					D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)),
					ENEMY_NORMAL_BULLET_SIZE,
					D3DXVECTOR3(-2.0f - nCount, 6.0f, 0.0f),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					CBullet::TEX_TYPE_ENEMY_NORMAL);

				// ��
				CEnemy_Normal_Bullet::Create(D3DXVECTOR3(m_Leftpos.x + BOSS_LEFT_SIZE.x / 2, m_Leftpos.y + BOSS_LEFT_SIZE.y / 2, m_Leftpos.z),
					D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)),
					ENEMY_NORMAL_BULLET_SIZE,
					D3DXVECTOR3(2.0f + nCount, 6.0f, 0.0f),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					CBullet::TEX_TYPE_ENEMY_NORMAL);
			}
		}
		//100���܂�0�̏ꍇ
		if (m_nAttackCount % 100 == 0)
		{
			// 3��J��Ԃ�
			for (int nCount = 0; nCount < 3; nCount++)
			{
				// �_�������e����
				CEnemy_Traking_Bullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z),
					D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)),
					ENEMY_TRAKING_BULLET_SIZE,
					D3DXVECTOR3(6.0f + nCount, 6.0f + nCount, 0.0f),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					CBullet::TEX_TYPE_ENEMY_NORMAL);
			}
		}
		//�g�U�e
		if (m_nAttackCount % 250 == 0)
		{
			// �g�U�e����
			CEnemy_Diffusion_Bullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z),
				D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)),
				FIFFUSION_BULLET_SIZE,
				D3DXVECTOR3(0.0f, 2.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				CBullet::TEX_TYPE_ENEMY_NORMAL);
		}
	}
		// ���C�t�������ȉ��̏ꍇ
	if (m_nLife <= BOSS_LIFE / 2)
	{
		m_nAttackCount2++;
		//100���܂�0�̏ꍇ
		if (m_nAttackCount2 % 60 == 0)
		{
			for (int nCount = 0; nCount < 4; nCount++)
			{
				// �_�������e����
				CEnemy_Traking_Bullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z),
					D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)),
					ENEMY_TRAKING_BULLET_SIZE,
					D3DXVECTOR3(6.0f + nCount, 6.0f + nCount, 0.0f),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					CBullet::TEX_TYPE_ENEMY_NORMAL);
			}
		}

		// �J�E���g��100�ȏ�̏ꍇ
		if (m_nAttackCount2 >= 100)
		{
			// 3���܂�0�̎�
			if (m_nAttackCount2 % 3 == 0)
			{
				// ��]�e����
				CEnemy_Normal_Bullet::Create(D3DXVECTOR3(m_Rightpos.x + BOSS_LEFT_SIZE.x / 2, m_Rightpos.y + BOSS_LEFT_SIZE.y / 2, m_Rightpos.z),
					D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)),
					ENEMY_NORMAL_BULLET_SIZE,
					D3DXVECTOR3(cosf(D3DXToRadian(m_nAttackCount2 / 3 * (360 / 20)))*3.0f, sinf(D3DXToRadian(m_nAttackCount2 / 3 * (360 / 20)))*3.0f, 0.0f),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					CBullet::TEX_TYPE_ENEMY_NORMAL);

				// ��]�e����
				CEnemy_Normal_Bullet::Create(D3DXVECTOR3(m_Leftpos.x + BOSS_LEFT_SIZE.x / 2, m_Leftpos.y + BOSS_LEFT_SIZE.y / 2, m_Leftpos.z),
					D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)),
					ENEMY_NORMAL_BULLET_SIZE,
					D3DXVECTOR3(cosf(D3DXToRadian(m_nAttackCount2 / 3 * (360 / 20)))* -3.0f, sinf(D3DXToRadian(m_nAttackCount2 / 3 * (360 / 20)))* -3.0f, 0.0f),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					CBullet::TEX_TYPE_ENEMY_NORMAL);

			}
		}
	}
}
//******************************************************************************
// ��ԏ����֐�
//******************************************************************************
void CBoss::State(void)
{
	//�ŏ��̈ړ�
	if (m_State == STATE_MOVE)
	{
		m_move.y = 2.0f;
		if (m_pos.y == 200.0f)
		{
			m_move.y = 0;
			m_State = STATE_NORMAL;
		}
	}
	//�{�X���ړ�����������
	if (m_State != STATE_MOVE)
	{
		// �ړ�����
		Move();

		// �U������
		Attack();
	}
	// State���m�[�}���̏ꍇ
	if (m_State == STATE_NORMAL)
	{
		//�J���[��ʏ�ɂ���
		m_apScene2D[TYPE_MAIN]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_apScene2D[TYPE_RIGHT]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_apScene2D[TYPE_LEFT]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	//State��Damage�̏ꍇ
	if (m_State == STATE_DAMAGE)
	{
		//�_���[�W�J�E���g�̃C���N�������g
		m_nDamageCount++;

		// �Ԃ�����
		m_apScene2D[TYPE_MAIN]->SetRGBA(D3DCOLOR_RGBA(255, 0, 0, 255));
		m_apScene2D[TYPE_RIGHT]->SetRGBA(D3DCOLOR_RGBA(255, 0, 0, 255));
		m_apScene2D[TYPE_LEFT]->SetRGBA(D3DCOLOR_RGBA(255, 0, 0, 255));

		//�J�E���g��2���܂�0�̎�
		if (m_nDamageCount % 2 == 0)
		{
			//�J���[��ʏ�ɖ߂�
			m_apScene2D[TYPE_MAIN]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_apScene2D[TYPE_RIGHT]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_apScene2D[TYPE_LEFT]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}

		// �J�E���g��10�ɂȂ�����
		if (m_nDamageCount == 10)
		{
			// State���m�[�}����
			m_State = STATE_NORMAL;
			// �J�E���g��0�ɂȂ�����
			m_nDamageCount = 0;
		}
	}
	// ���C�t��0�ɂȂ����ꍇ
	if (m_nLife <= 0)
	{
		// ��������
		CExplosion::Create(m_pos, BOSS_MAIN_SIZE);
		CExplosion::Create(m_Rightpos, BOSS_LEFT_SIZE);
		CExplosion::Create(m_Leftpos, BOSS_RIGHT_SIZE);

		// ���S��Ԃ�
		m_State = STATE_DEAD;

		// ���S��Ԃ̏ꍇ
		if (m_State == STATE_DEAD)
		{
			// �t�F�[�h�J�n
			CSceneManager::StartFade(CSceneManager::MODE_RESULT);
			// �I��
			Uninit();
			return;
		}
	}
}
//******************************************************************************
// �ړ������֐�
//******************************************************************************
void CBoss::Move(void)
{
	// false�̏ꍇ
	if (m_bMove == false)
	{
		m_move.x = 3.0f;
	}
	//���ړ�
	if (m_Rightpos.x + BOSS_RIGHT_SIZE.x / 2 >= MAX_GAME_WIDTH)
	{
		m_move.x = -3.0f;
		m_bMove = true;
	}
	// �E�ړ�
	if (m_Leftpos.x - BOSS_LEFT_SIZE.x / 2 <= MIN_GAME_WIDTH)
	{
		m_move.x = 3.0f;
		m_bMove = true;
	}
}