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
#include "explosion.h"
#include "enemy.h"
#include "game.h"
#include "item.h"
//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
LPDIRECT3DTEXTURE9 CEnemy::m_apTexture[TEX_TYPE_MAX] = {};
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CEnemy::CEnemy(int nPriority) : CScene2d(nPriority)
{
	m_TexType = TEX_TYPE_NONE;
	m_state = STATE_NONE;
	m_nLife = 0;

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
	D3DXCreateTextureFromFile(pDevice, "data/Texture/enemy1.png", &m_apTexture[TEX_TYPE_NORMAL]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/enemy2.png", &m_apTexture[TEX_TYPE_BLUE]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/enemy3.png", &m_apTexture[TEX_TYPE_RED]);
	return S_OK;
}
//******************************************************************************
// �e�N�X�`���j��
//******************************************************************************
void CEnemy::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_ENEMY_TEX; nCnt++)
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
	// �J���[�ݒ�
	SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// �e�N�X�`���ݒ�
	BindTexture(m_apTexture[m_TexType]);

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
		SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	// �_���[�W��Ԃ̏ꍇ
	if (m_state == STATE_DAMAGE)
	{
		// �C���N�������g
		m_nDamageCount++;
		// 2���܂�0�̎�
		if (m_nDamageCount % 2 == 0)
		{
			// �J���[�ݒ�
			SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		// ���܂�0�̎�
		if (m_nDamageCount % 1 == 0)
		{
			// �J���[�ݒ�Ԃɂ���
			SetRGBA(D3DCOLOR_RGBA(255, 0, 0, 255));
		}
		// �J�E���g��10�̏ꍇ
		if (m_nDamageCount == 10)
		{
			// ��Ԃ�NORMAL�ɂ���
			m_state = STATE_NORMAL;
			m_nDamageCount = 0;
		}
	}

	// ���C�t��0�ȉ��ɂȂ����ꍇ
	if (m_nLife <= 0)
	{
		// �����̐���
		CExplosion::Create(pos, EXPLOSION_SIZE);
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

	// ���C�t�ݒ�
	m_nLife = nLife;

	// �e�N�X�`���^�C�v���
	m_TexType = tex_type;

	// �I�u�W�F�^�C�v�ݒ�
	SetObjType(objtype);
}
