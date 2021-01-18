//******************************************************************************
// �e [bullet.cpp]
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
//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
LPDIRECT3DTEXTURE9 CBullet::m_apTexture[TEX_TYPE_MAX] = {};

//******************************************************************************
// �e�N�X�`���ǂݍ��݊֐�
//******************************************************************************
HRESULT CBullet::Load(void)
{
	// �����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();

	// �e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/Playerbullet001.png", &m_apTexture[TEX_TYPE_NORMAL]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/PlayerBeam001.png", &m_apTexture[TEX_TYPE_BEAM]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/bom.png", &m_apTexture[TEX_TYPE_BOM]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/EnemyBullet.png", &m_apTexture[TEX_TYPE_ENEMY_NORMAL]);
	return S_OK;
}
//******************************************************************************
// �e�N�X�`���j���֐�
//******************************************************************************
void CBullet::Unload(void)
{
	// �e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < TEX_TYPE_MAX; nCnt++)
	{
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CBullet::CBullet(int nPriority) : CScene2d(nPriority)
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Textype = TEX_TYPE_NONE;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CBullet::~CBullet()
{
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CBullet::Init()
{
	// ������
	CScene2d::Init();

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CBullet::Uninit(void)
{
	// �I��
	CScene2d::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CBullet::Update(void)
{
	// �X�V
	CScene2d::Update();

	// ���W�̎擾
	D3DXVECTOR3 pos;
	pos = GetPosition();
	
	// �ʒu�X�V
	SetPosition(pos);

	// ��ʊO
	if (pos.x > MAX_GAME_WIDTH || pos.x < MIN_GAME_WIDTH || pos.y > SCREEN_HEIGHT || pos.y < 0)
	{
		//�I��
		Uninit();
		return;
	}
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CBullet::Draw(void)
{
	// �`��
	CScene2d::Draw();
}
//******************************************************************************
// �e�̏��ݒ�
//******************************************************************************
void CBullet::SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, TEX_TYPE textype, OBJTYPE objtype)
{
	// �ʒu���W�ݒ�
	SetPosition(pos);
	// �����ݒ�
	SetRot(rot);
	// �T�C�Y�ݒ�
	SetSize(size);
	// �J���[�ݒ�
	SetRGBA(col);
	// �e�N�X�`���^�C�v�ݒ�
	m_Textype = textype;
	// �e�N�X�`���ݒ�
	BindTexture(m_apTexture[m_Textype]);
	// �I�u�W�F�N�g�^�C�v�ݒ�
	SetObjType(objtype);
}