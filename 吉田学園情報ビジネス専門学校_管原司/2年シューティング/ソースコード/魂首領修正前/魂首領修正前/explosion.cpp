//---------------------------------------------------
// Bullet
// Bullet.cpp
// Author:	�ǌ��i
//---------------------------------------------------

//---------------------------------------------------
//�C���N���[�h�t�@�C��
//---------------------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "input.h"
#include "inputkeyboard.h"
#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "sound.h"
//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;
//---------------------------------------------------
//�����֐�
//---------------------------------------------------
CExplosion * CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//CPlayer�N���X�̃|�C���^
	CExplosion * pExplosion;
	//�������m��
	pExplosion = new CExplosion;
	//������
	pExplosion->Init(pos, rot, sizeX, sizeY);
	return pExplosion;
}
//---------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------
CExplosion::CExplosion(int nPriority) : CScene2d(nPriority)
{
	m_nCountAnim = 0;
	m_nPatternAnim = 0;
	m_bUse = true;
}
//---------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------
CExplosion::~CExplosion()
{
}
//---------------------------------------------------
//������
//---------------------------------------------------
HRESULT CExplosion::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//������
	CScene2d::Init(pos, rot, sizeX, sizeY);
	//�����̏����ݒ�
	m_nCountAnim = 0;
	m_nPatternAnim = 0;
	m_bUse = true;
	SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	BindTexture(m_pTexture);
	SetObjType(CScene::OBJTYPE_EXPLOSION);
	return S_OK;
}
//---------------------------------------------------
//�I��
//---------------------------------------------------
void CExplosion::Uninit(void)
{
	//�I��
	CScene2d::Uninit();
}
//---------------------------------------------------
//�X�V
//---------------------------------------------------
void CExplosion::Update(void)
{
	//�X�V
	CScene2d::Update();
	//true�̏ꍇ
	if (m_bUse == true)
	{
		//�J�E���g�C���N�������g
		m_nCountAnim++;
		//�J�E���g��4�ȏ�ɂȂ����ꍇ
		if (m_nCountAnim > 4)
		{
			m_nCountAnim = 0;
			//�e�N�X�`���Z�b�g
			SetTexture(m_nPatternAnim * 0.125f, 0.0f, 0.125f, 1.0f);
			//�p�^�[���̃C���N�������g
			m_nPatternAnim++;
			//�p�^�[����8�ɂȂ����ꍇ
			if (m_nPatternAnim > 8)
			{
				m_bUse = false;
			}
		}
	}
	//false�̏ꍇ
	else
	{
		//�I��
		Uninit();
	}
}
//---------------------------------------------------
//�`��
//---------------------------------------------------
void CExplosion::Draw(void)
{
	//�`��
	CScene2d::Draw();
}
//--------------------------------------------------
//�e�N�X�`���̃��[�h
//--------------------------------------------------
HRESULT CExplosion::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/explosion000.png", &m_pTexture);
	return S_OK;
}
//-------------------------------------------------
//�e�N�X�`���̔j��
//-------------------------------------------------
void CExplosion::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}