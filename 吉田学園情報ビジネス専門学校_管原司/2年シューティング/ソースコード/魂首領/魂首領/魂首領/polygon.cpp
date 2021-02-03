//******************************************************************************
// �|���S�� [polygon.cpp]
// Author : �ǌ��@�i
//******************************************************************************
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "sound.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "polygon.h"
//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
LPDIRECT3DTEXTURE9 CPolygon::m_apTexture[TEX_TYPE_MAX] = {};
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CPolygon::CPolygon(int nPriority) : CScene2d(nPriority)
{
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CPolygon::~CPolygon()
{
}
//******************************************************************************
// �e�N�X�`���ǂݍ���
//******************************************************************************
HRESULT CPolygon::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/UI/Title.png",&m_apTexture[TEX_TYPE_TITLE]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/UI/PressEnter.png",&m_apTexture[TEX_TYPE_PRESS_ENTER]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/UI/Tutrial.png",&m_apTexture[TEX_TYPE_TUTRIAL]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/UI/Ranking.png",&m_apTexture[TEX_TYPE_RANKING]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/UI/continue.png", &m_apTexture[TEX_TYPE_CONTINUE]);
	return S_OK;
}
//******************************************************************************
// �e�N�X�`���j��
//******************************************************************************
void CPolygon::Unload(void)
{
	for (int nCnt = 0; nCnt < TEX_TYPE_MAX; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_apTexture[nCnt] != NULL)
		{
			//�e�N�X�`�������[�X
			m_apTexture[nCnt]->Release();
			//m_pTexture��NULL��
			m_apTexture[nCnt] = NULL;
		}
	}
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CPolygon::Init()
{
	//�@������
	CScene2d::Init();
	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CPolygon::Uninit(void)
{
	//�@�I��
	CScene2d::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CPolygon::Update(void)
{
	//�@�X�V
	CScene2d::Update();
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CPolygon::Draw(void)
{
	//�@�`��
	CScene2d::Draw();
}
//******************************************************************************
// ���ݒ�
//******************************************************************************
void CPolygon::SetPolygon(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, TEX_TYPE textype)
{
	// �ʒu���W�ݒ�
	SetPosition(pos);

	// �T�C�Y�ݒ�
	SetSize(size);

	// �J���[�ݒ�
	SetRGBA(col);

	m_TexType = textype;

	BindTexture(m_apTexture[m_TexType]);
}