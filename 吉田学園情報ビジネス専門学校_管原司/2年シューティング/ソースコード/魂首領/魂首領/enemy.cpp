//******************************************************************************
// �G [enemy.cpp]
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
#include "enemy.h"
#include "game.h"
#include "item.h"
#include "particle.h"
#include "particle_explosion.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define NORMAL_ENEMY_TEXTURE	("data/Texture/Enemy/enemy1.png")	// �ʏ�̓G
#define ENEMY_BLUE_TEXTURE		("data/Texture/Enemy/enemy2.png")	// �F�̓G
#define ENEMY_RED_TEXTURE		("data/Texture/Enemy/enemy3.png")	// �ԐF�̓G
#define BATTERY_TEXTURE			("data/Texture/Enemy/Wepon1.png")	// �Œ�C��
#define EXPLOSION_SIZE			(D3DXVECTOR3(3.0f,3.0f,0.0f))		// �����T�C�Y
#define COLOR					(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	// �F
#define DAMAGE_COLOR			(D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))	// �_���[�W��Ԃ̐F
#define DAMAGE_COUNT			(10)								// �_���[�W��Ԃ̃J�E���g
#define INIT_DAMAGE_COUNT		(0)									// �_���[�W�J�E���g��0
#define DAMAGE_COUNT_DEVIDE		(2)									// ���鐔
#define DAMAGE_COUNT_REMAINDER	(0)									// �]��
#define LIFE_MIN				(0)									// ���C�t�ŏ��l
//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
LPDIRECT3DTEXTURE9 CEnemy::m_apTexture[TEX_TYPE_MAX] = {};
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CEnemy::CEnemy(int nPriority) : CScene2d(nPriority)
{
	m_TexType		= TEX_TYPE_NONE;
	m_state			= STATE_NONE;
	m_nLife			= INIT_INT;
	m_nDamageCount	= INIT_INT;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CEnemy::~CEnemy()
{
}
//******************************************************************************
// �e�N�X�`���ǂݍ���
//******************************************************************************
HRESULT CEnemy::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, NORMAL_ENEMY_TEXTURE, &m_apTexture[TEX_TYPE_NORMAL]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_BLUE_TEXTURE, &m_apTexture[TEX_TYPE_BLUE]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_RED_TEXTURE, &m_apTexture[TEX_TYPE_RED]);
	D3DXCreateTextureFromFile(pDevice, BATTERY_TEXTURE, &m_apTexture[TEX_TYPE_SHIP_BATTERY]);
	return S_OK;
}
//******************************************************************************
// �e�N�X�`���j��
//******************************************************************************
void CEnemy::Unload(void)
{
	for (int nCnt = INIT_INT; nCnt < TEX_TYPE_MAX; nCnt++)
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
CEnemy * CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nLife, TEX_TYPE tex_type, CScene::OBJTYPE objtype)
{
	// CEnemy�N���X�̃|�C���^
	CEnemy * pEnemy;

	// �������m��
	pEnemy = new CEnemy;

	// ������
	pEnemy->Init();

	// �|�C���^��Ԃ�
	return pEnemy;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CEnemy::Init(void)
{
	// �ʏ��Ԃ�
	m_state = STATE_NORMAL;

	//������
	CScene2d::Init();

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CEnemy::Uninit(void)
{
	//�I��
	CScene2d::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CEnemy::Update(void)
{
	// �X�V
	CScene2d::Update();

	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// State���m�[�}���̏ꍇ
	if (m_state == STATE_NORMAL)
	{
		// �J���[�ݒ�
		SetRGBA(COLOR);
	}
	// �_���[�W��Ԃ̏ꍇ
	if (m_state == STATE_DAMAGE)
	{
		// �C���N�������g
		m_nDamageCount++;

		// �J���[�ݒ�Ԃɂ���
		SetRGBA(DAMAGE_COLOR);

		// 2���܂�0�̎�
		if (m_nDamageCount % DAMAGE_COUNT_DEVIDE == DAMAGE_COUNT_REMAINDER)
		{
			// �J���[�ݒ�
			SetRGBA(COLOR);
		}

		// �J�E���g��10�̏ꍇ
		if (m_nDamageCount == DAMAGE_COUNT)
		{
			// ��Ԃ�NORMAL�ɂ���
			m_state = STATE_NORMAL;

			// 0��
			m_nDamageCount = INIT_DAMAGE_COUNT;
		}
	}

	// ���C�t��0�ȉ��ɂȂ����ꍇ
	if (m_nLife <= LIFE_MIN)
	{
		// �����̐���
		CParticle_Explosion::CreateExplosionEffect(pos, EXPLOSION_SIZE,CParticle_Explosion::TYPE_ENEMY);

		// ���S��Ԃɐݒ�
		m_state = STATE_DEATH;

		// �I��
		Uninit();
		return;
	}
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CEnemy::Draw(void)
{
	//�`��
	CScene2d::Draw();
}
//******************************************************************************
// �q�b�g�����֐�
//******************************************************************************
void CEnemy::HitEnemy(int nDamage)
{
	// �_���[�W���Z
	m_nLife -= nDamage;

	// state���_���[�W��
	m_state = STATE_DAMAGE;
}
//******************************************************************************
// �G���̐ݒ�
//******************************************************************************
void CEnemy::SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nLife, TEX_TYPE tex_type, CScene::OBJTYPE objtype)
{
	// �ʒu���W�ݒ�
	SetPosition(pos);

	// �����ݒ�
	SetRot(rot);

	// �T�C�Y�ݒ�
	SetSize(size);

	// �J���[�ݒ�
	SetRGBA(COLOR);

	// ���C�t�ݒ�
	m_nLife = nLife;

	// �e�N�X�`���^�C�v���
	m_TexType = tex_type;

	// �e�N�X�`���ݒ�
	BindTexture(m_apTexture[m_TexType]);

	// �I�u�W�F�^�C�v�ݒ�
	SetObjType(objtype);
}
